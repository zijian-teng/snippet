#include <atomic>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "03-blocking_queue.h"
#include "04-task_queue.h"

void TestCase0_NotifyAll() {
  std::atomic_bool b{false};
  std::mutex m;
  std::condition_variable cv;

  std::thread t{[&] {
    std::unique_lock<std::mutex> l(m);
    // cv.wait(l);  // 可能唤醒丢失

    cv.wait(l, [&b] { return b.load(); });
    std::cout << "waken up!" << '\n';
  }};

  b.store(true);
  // cv.notify_all(); // 是不是必须的？！！？！可能只是巧合偶尔能退出，虚假唤醒？
  t.join();
}

void TestCase1_BlockingQueue() {
  BlockingQueue<std::unique_ptr<int>> queue;
  auto p = std::make_unique<int>(3);
  queue.Push(std::move(p));
  std::unique_ptr<int> q;
  if (queue.Pop(q)) {
    std::cout << *q << '\n';
  }
}

void TestCase2_TaskPoolTest() {
  TaskPool task_pool(2);
  task_pool.AddTask([] {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "hello 1" << '\n';
  });
  task_pool.AddTask([] {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "hello 2" << '\n';
  });
  task_pool.AddTask([] {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "hello 3" << '\n';
  });
  task_pool.AddTask([] {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "hello 4" << '\n';
  });
  task_pool.AddTask([] {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "hello 5" << '\n';
  });
  // std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
  // TestCase0_NotifyAll();

  try {
    TestCase1_BlockingQueue();
    TestCase2_TaskPoolTest();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  return 0;
}