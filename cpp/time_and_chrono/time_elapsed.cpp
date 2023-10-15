#include <chrono>
#include <iostream>
#include <thread>

int main() {
  // system_clock, steady_clock, high_resolution_clock 时钟的区别？
  auto start{std::chrono::steady_clock::now()};
  // do something...
  using namespace std::literals::chrono_literals;
  std::this_thread::sleep_for(3ms);
  auto end{std::chrono::steady_clock::now()};

  // C++20 不再需要 count()
  // end - start 的 类型是什么？
  // duration 和 duration_cast 有什么区别？
  std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "ns\n";
  std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us\n";
  std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
  std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "s\n";
  std::cout << "Time elapsed: " << std::chrono::duration<double>(end - start).count() << "s\n";
}

/*
时间库的使用：
- 程序执行耗时
- 获取当前时间的 time_point
- this_thread::sleep_for
- duration_cast 的使用
- 时间字面量所属的命名空间：std::literals::chrono_literals
*/
