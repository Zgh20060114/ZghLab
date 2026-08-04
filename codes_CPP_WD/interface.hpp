#pragma once
#include <memory>

// 前向声明实现类，不暴露任何实现细节
class RealizeImpl;

class Interface {
public:
  // 构造与析构（必须定义，因为 unique_ptr 需要完整类型）
  Interface();
  ~Interface();

  // 含unique_ptr禁止拷贝（但允许移动）
  Interface(const Interface &) = delete;
  Interface &operator=(const Interface &) = delete;
  Interface(Interface &&) noexcept = default;
  Interface &operator=(Interface &&) noexcept = default;

  // 公有接口
  void setValue(int val);
  int getValue() const;
  void print() const;

private:
  std::unique_ptr<RealizeImpl> pImpl; // 指向实现对象的指针
};
