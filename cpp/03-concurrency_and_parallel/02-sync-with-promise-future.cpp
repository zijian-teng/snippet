#include <future>
#include <iostream>
#include <thread>

void waitForWork(std::future<void> fut) {
  std::cout << "Waiting...\n";
  fut.wait();
  std::cout << "Running...\n";
}

void setDataReady(std::promise<void> prom) {
  prom.set_value();
  std::cout << "Data ready!\n";
}

int main() {
  std::promise<void> ready_promise;
  std::future<void> fut = ready_promise.get_future();

  // 即使先发送通知，也不会出现丢失唤醒的问题
  std::thread t2{setDataReady, std::move(ready_promise)};
  using namespace std::literals::chrono_literals;
  std::this_thread::sleep_for(1ms);

  std::thread t1{waitForWork, std::move(fut)};

  t1.join();
  t2.join();
}

/*
和上一个使用条件变量的例子相比，promise-future
优势：
- 更安全：不需要 mutex、不存在丢失唤醒和虚假唤醒的问题，也不需要临界区或额外的条件判断

劣势：
- 一个诺值（promise/packaged_task/async）只能发送一次通知

*/