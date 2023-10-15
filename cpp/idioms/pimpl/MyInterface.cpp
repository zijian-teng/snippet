#include "MyInterface.h"

#include <iostream>
#include <memory>

// Impl 类定义和实现也可以放到单独的文件中
struct MyInterface::Impl {
  void method1() {
    std::cout << "MyInterface::Impl::method1\n";
  }
  void method2() {
    std::cout << "MyInterface::Impl::method2\n";
  }
};

// 即便可以直接类内初始化，也不适用于 PIMPL，因为类内看不到 Impl 定义
MyInterface::MyInterface() : p_impl_(std::make_unique<Impl>()) {
}
MyInterface::~MyInterface() = default;

// wrapper 函数只负责转发，不应有逻辑，所有的逻辑放到 Impl 中
void MyInterface::method1() {
  p_impl_->method1();
}
void MyInterface::method2() {
  p_impl_->method2();
}
