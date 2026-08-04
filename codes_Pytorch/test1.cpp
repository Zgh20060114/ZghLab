#include <iostream>
//
// class C {
// public:
//   void cPrint() const { std::cout << "C::cPrint()" << std::endl; }
// };
//
// class A {
// private:
//   C *c_ptr = new C();
//
// public:
//   C *operator->() { return c_ptr; } // 返回 C*，即原生指针
//   C &operator*() { return *c_ptr; } // 返回 C*，即原生指针
//   ~A() { delete c_ptr; }
// };
//
// class B {
// private:
//   A *a_ptr = new A();
//
// public:
//   A *operator->() { return a_ptr; } // 返回 A*，即原生指针
//   ~B() { delete a_ptr; }
// };
//
// int main() {
//   // B b;         // B 的类外对象 b
//   // b->cPrint(); // ✅ 可以运行！输出: C::cPrint()
//   A a;
//   a->cPrint();
//   (*a).cPrint();
//   return 0;
// }

class Line {
public:
  int a;
  void print() { std::cout << b << std::endl; }
  class Point {
  public:
    int b;
  };
};
