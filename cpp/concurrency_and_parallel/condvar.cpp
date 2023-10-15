#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex m;
std::condition_variable condVar;
bool dataReady{false};

void waitForWork() {
  std::cout << "waiting...\n";

  // 接收方通常需要频繁地对 mutex 进行加锁和解锁，因此需要 unique_lock
  std::unique_lock<std::mutex> lck{m};

  // 此处必须传入谓词！防止丢失唤醒（notify 先于 wait 发生）及虚假唤醒（POSIX 和 Windows API 都存在该问题）
  condVar.wait(lck, [] { return dataReady; });
  std::cout << "Running...\n";
}

void setDataReady() {
  // 发送方只调用一次 lock 和 unlock，用 lock_guard 就足够了
  {
    std::lock_guard<std::mutex> lck{m};
    dataReady = true;
  }
  std::cout << "Data ready!\n";
  condVar.notify_one();
}

int main() {
  std::thread t1{waitForWork};
  std::thread t2{setDataReady};

  t1.join();
  t2.join();
}