#include <functional>
#include <vector>

struct Data {
  int i;
  int j;
};

class Listener {
 public:
  Listener() = default;
  Listener& operator=(const Listener&) = default;
  Listener& operator=(Listener&&) = default;
  Listener(Listener&&) = default;
  Listener(const Listener&) = default;
  virtual ~Listener() = default;
  virtual void OnNotified() = 0;
  // 如果需要传递数据，可以在 OnNotified 接口中增加参数
  // virtual void OnNotified(const Data&) = 0;
};

class ConcreteListener : public Listener {
 public:
  void OnNotified() override {
  }
};

class Subject {
 public:
  void RegisterListener(Listener& o) {
    listeners_.push_back(o);
  }

 private:
  void NotifyListeners() {
    for (Listener& o : listeners_) {
      o.OnNotified();
    }
  }

  // 注意：vector 不能停直接保存引用，可以用 reference_wrapper
  std::vector<std::reference_wrapper<Listener>> listeners_;
};

int main() {
  Subject s;
  ConcreteListener listener;
  s.RegisterListener(listener);
}