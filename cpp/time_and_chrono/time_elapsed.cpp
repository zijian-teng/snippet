#include <chrono>
#include <iostream>
#include <thread>

int main() {
  auto start{std::chrono::steady_clock::now()};
  // do something...
  using namespace std::literals::chrono_literals;
  std::this_thread::sleep_for(3ms);
  auto end{std::chrono::steady_clock::now()};

  // C++20 不再需要 count()
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

关于 duration 的具体类型：https://cppinsights.io/s/2d172d5d
auto start = steady_clock::now();
auto end = steady_clock::now();
auto d = end - start;
auto dn = duration_cast<nanoseconds>(end - start);
auto du = duration_cast<microseconds>(end - start);
auto dm = duration_cast<milliseconds>(end - start);
auto ds = duration_cast<seconds>(end - start);
duration<double> dd = end - start;

time_point<steady_clock, duration<long, std::ratio<1, 1000000000> > > start = steady_clock::now();
time_point<steady_clock, duration<long, std::ratio<1, 1000000000> > > end = steady_clock::now();
duration<long, std::ratio<1, 1000000000> > d = end - start;
duration<long, std::ratio<1, 1000000000> > dn = duration_cast<duration<long, std::ratio<1, 1000000000> > >(end - start);
duration<long, std::ratio<1, 1000000> > du = duration_cast<duration<long, std::ratio<1, 1000000> > >(end - start);
duration<long, std::ratio<1, 1000> > dm = duration_cast<duration<long, std::ratio<1, 1000> > >(end - start);
duration<long, std::ratio<1, 1> > ds = duration_cast<duration<long, std::ratio<1, 1> > >(end - start);
duration<double, std::ratio<1, 1> > dd = duration<double, std::ratio<1, 1> >(end - start);

end - start 自动推导类型，和 time_point 相同，即 nanoseconds：
  duration<long, std::ratio<1, 1000000000>>
std::chrono::nanoseconds 类型：
  duration<long, std::ratio<1, 1000000000> >
std::chrono::microseconds 类型：
  duration<long, std::ratio<1, 1000000> >
std::chrono::milliseconds 类型：
  duration<long, std::ratio<1, 1000> >
std::chrono::seconds 类型：
  duration<long, std::ratio<1, 1> >
duration<double> 类型：
  duration<double, std::ratio<1, 1> >


system_clock, steady_clock, high_resolution_clock 时钟的区别？

*/
