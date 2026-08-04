#include "interface.hpp"
#include "realize_impl.hpp"

Interface::Interface() : pImpl(std::make_unique<RealizeImpl>()) {}

Interface::~Interface() = default; // 需要定义，因为 unique_ptr 析构需要完整类型

void Interface::setValue(int val) { pImpl->setValue(val); }

int Interface::getValue() const { return pImpl->getValue(); }

void Interface::print() const { pImpl->print(); }
