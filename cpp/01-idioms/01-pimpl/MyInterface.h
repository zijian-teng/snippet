#include <memory>

//! @todo 可以和 Singleton 结合，但注意不要滥用 Singleton

class MyInterface {
 public:
  // 使用 unique_ptr 的关键，此处的析构函数只能声明，不能实现！
  MyInterface();
  ~MyInterface();
  MyInterface(const MyInterface&) = delete;
  MyInterface(MyInterface&&) = delete;
  MyInterface& operator=(const MyInterface&) = delete;
  MyInterface& operator=(MyInterface&&) = delete;

  void method1();
  void method2();

 private:
  struct Impl;
  // 从语义上来说，unique_ptr 比 shared_ptr 更合适，且此处无法直接类内初始化
  std::unique_ptr<Impl> p_impl_;
};
