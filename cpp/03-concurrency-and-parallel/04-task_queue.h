#pragma once

#include <atomic>
#include <cassert>
#include <functional>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

#include "03-blocking_queue.h"

/**
 * @brief 固定大小线程池
 * 1. 单参构造，指定线程数量
 * 2. 支持优雅退出，调用 Shutdown() 之前的已经 Push() 的任务全部完成后才退出；
 *    但调用 AddTask() 之后、Push() 之前的任务可能不被执行
 */

class TaskPool {
 public:
  using TaskType = std::function<void()>;

  explicit TaskPool(size_t thread_num) {
    for (size_t i = 0; i < thread_num; ++i) {
      threads_.emplace_back(std::thread([this] { WorkerThreadFunction(); }));
    }
  }

  ~TaskPool() {
    std::cout << "~TaskPool() Shutting down..." << '\n';
    Shutdown();
  }

  TaskPool(const TaskPool&) = delete;
  TaskPool(TaskPool&&) = delete;
  TaskPool& operator=(const TaskPool&) = delete;
  TaskPool& operator=(TaskPool&&) = delete;

  void WorkerThreadFunction() {
    TaskType task;
    while (true) {
      // 当退出时，Pop() 要能收到通知，及时返回，不要一直等待
      auto success = task_queue_.Pop(task, [this] { return !running_.load(); });
      if (!success) {
        break;
      }

      // std::cout << "Thread " << std::this_thread::get_id() << " get the task!" << '\n'
      try {
        task();
      } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
      } catch (...) {
        std::cerr << "Exception caught while running task()!" << '\n';
      }
    }
  }

  /**
   * 这里可能存在竞争: Push() 执行之前，running_ 被修改为 false
   *
   * Case 1:
   *   1. 线程 A 添加任务，发现 running == true
   *   2. 线程 B 调用 Shutdown()，设置 running = false，唤醒所有工作线程
   *   3. 工作线程 D、E、F 发现队列为空，退出
   *   4. 线程 A 继续 Push()，但是没有工作线程处理，导致 Shutdown 之后 task_queue_ 不为空
   *
   * Case 2:
   *   1. 线程 A 添加任务，发现 running == true
   *   2. 线程 B 调用 Shutdown()，设置 running = false，唤醒所有工作线程
   *   3. 线程 A 继续 Push
   *   4. 工作线程 D、E、F 中的某一个处理刚插入队列的任务
   *
   * 要解决这个问题，可以额外增加一个 mutex 成员，每次 AddTask()、Shutdown() 时加锁保护；
   * 权衡后果和开销，不专门处理这种情况
   */
  template <typename X>
  void AddTask(X&& task) {
    if (running_.load()) {
      task_queue_.Push(std::forward<X>(task));
    }
  }

  void Shutdown() {
    running_.store(false);
    task_queue_.NotifyAll();  // 如果不通知，有一定概率 Pop() 一直等待条件变量，没被唤醒，无法正常退出
    for (auto& thread : threads_) {
      if (thread.joinable()) {
        thread.join();
      }
    }
    // assert(task_queue_.Size() == 0); // 断言可能失败：见 AddTask() 注释 Case 1
  }

 private:
  BlockingQueue<TaskType> task_queue_;
  std::vector<std::thread> threads_;
  std::atomic_bool running_{true};
};
