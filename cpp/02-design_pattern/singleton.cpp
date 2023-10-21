#include <iostream>

class Singleton final {
 public:
  static Singleton& getInstance() {
    static Singleton instance;
    return instance;
  }

  // 删除拷贝、移动操作
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(Singleton&&) = delete;
  // 默认的析构函数
  ~Singleton() = default;

  void some_methods() {
    std::cout << "Zijian: Hello Singleton!\n";
  }

 private:
  //  构造必须是 private 或删除的！
  Singleton() = default;
};

int main() {
  // 1. 可以直接调用方法
  Singleton::getInstance().some_methods();

  // 2. 如果需要频繁使用单例对象，也可以保存一个引用
  auto& inst = Singleton::getInstance();
  inst.some_methods();
}