#pragma once

#include <atomic>
#include <condition_variable>
#include <deque>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>

/**
 * @brief 线程安全的阻塞队列
 *
 */

template <typename T>
class BlockingQueue {
 public:
  /**
   * @brief 添加任务到队列（线程安全）
   * @note 若在 Pop() 停止条件满足后调用 Push()，任务可能无法被处理
   */
  template <typename X>
  void Push(X&& x) {
    {
      std::unique_lock<std::mutex> lock(mutex_);
      queue_.push_back(std::forward<X>(x));
    }
    cv_.notify_one();
  }

  // 默认无停止条件的版本，永远等待队列非空
  bool Pop(T& item) {
    return Pop(item, [] { return false; });
  }

  /**
   * @brief 带有额外停止条件的 Pop()，可以避免线程一直 wait 阻塞无法正常退出
   * 注意：通知方设置停止条件后，需要调用 NotifyAll() 通知
   *
   * \tparam StopCondition 退出条件可调用对象：退出条件满足返回 true，否则 false
   * \param item[out] 从队列中取出的元素，仅在返回值为 true 时有效
   * \param stop[in] 退出条件可调用对象：退出条件满足返回 true，否则 false
   * \return true 若队列非空，取出元素返回 true，无论停止条件是否满足
   * \return false 若队列为空且停止条件满足
   */
  template <typename StopCondition>
  bool Pop(T& item, StopCondition stop) {
    std::unique_lock<std::mutex> lock(mutex_);
    // 带谓词版本的 wait()，可以避免唤醒丢失和虚假唤醒问题
    cv_.wait(lock, [this, &stop] { return !queue_.empty() || stop(); });

    // 当队列为空且停止条件满足时，返回 false
    if (queue_.empty()) {
      return false;
    }

    // 队列中有元素时，取出并返回 true
    item = std::move(queue_.front());
    queue_.pop_front();
    return true;
  }

  std::deque<T> PopAll() {
    std::deque<T> queue;
    {
      std::unique_lock<std::mutex> lock(mutex_);
      queue.swap(queue_);
    }
    return queue;
  }

  void NotifyAll() {
    cv_.notify_all();
  }

  size_t Size() const {
    std::unique_lock<std::mutex> lock(mutex_);
    return queue_.size();
  }

 private:
  mutable std::mutex mutex_;
  std::condition_variable cv_;
  std::deque<T> queue_;
};
