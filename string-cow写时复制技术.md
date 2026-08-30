~~~ cpp 
#include <iostream>
#include <cstring>
#include <cassert>

class MyStringCOW {
public:
    // 1. 默认构造
    MyStringCOW() : _start(nullptr), _finish(nullptr), _end(nullptr) {
        _initEmpty();
    }

    // 2. C字符串构造
    MyStringCOW(const char* str) : _start(nullptr), _finish(nullptr), _end(nullptr) {
        if (str) {
            size_t len = strlen(str);
            _allocate(len, len);
            memcpy(_start, str, len);
            _finish = _start + len;
        } else {
            _initEmpty();
        }
    }

    // 3. 拷贝构造（浅拷贝，引用计数 +1）
    MyStringCOW(const MyStringCOW& rhs) {
        _start = rhs._start;
        _finish = rhs._finish;
        _end = rhs._end;
        if (_start) {
            ++REF_COUNT(_start);
        }
    }

    // 4. 赋值运算符（处理旧数据，浅拷贝新数据）
    MyStringCOW& operator=(const MyStringCOW& rhs) {
        if (this != &rhs) {
            // 释放当前对象持有的资源
            _release();
            // 接管 rhs 的资源
            _start = rhs._start;
            _finish = rhs._finish;
            _end = rhs._end;
            if (_start) {
                ++REF_COUNT(_start);
            }
        }
        return *this;
    }

    // 5. 析构函数（引用计数 -1，为 0 时释放）
    ~MyStringCOW() {
        _release();
    }

    // 6. 获取长度
    size_t size() const {
        return _start ? (_finish - _start) : 0;
    }

    // 7. 获取 C 风格字符串（只读）
    const char* c_str() const {
        return _start ? _start : "";
    }

    // 8. 核心写操作：触发写时拷贝（分离 Detach）
    char& operator[](size_t pos) {
        assert(pos < size() && "Index out of range!");
        _mutate(); // 触发 COW
        return _start[pos];
    }

    // 9. 尾部追加字符（触发 COW 及可能的扩容）
    void push_back(char ch) {
        if (_finish == _end) {
            // 空间不够，需要扩容
            size_t oldSize = size();
            size_t newCap = oldSize == 0 ? 1 : oldSize * 2;
            char* newMem = new char[newCap + 4];
            *(int*)newMem = 1;
            char* newData = newMem + 4;
            if (_start) {
                memcpy(newData, _start, oldSize);
                _release(); // 释放旧内存
            }
            _start = newData;
            _finish = newData + oldSize;
            _end = newData + newCap;
        } else {
            _mutate(); // 空间够，但如果是共享内存，仍需分离
        }
        *_finish = ch;
        ++_finish;
    }

    // 打印调试信息
    void debug() const {
        std::cout << "Data: \"" << c_str() << "\", Size: " << size();
        if (_start) {
            std::cout << ", RefCount: " << REF_COUNT(_start);
        } else {
            std::cout << ", RefCount: 0";
        }
        std::cout << std::endl;
    }

private:
    char* _start;   // 有效字符起始
    char* _finish;  // 有效字符结束
    char* _end;     // 堆内存结束

    // 内存布局：[4字节引用计数][有效字符区][空闲区]
    #define REF_COUNT(p) (*(int*)((char*)p - 4))

    // 初始化空字符串
    void _initEmpty() {
        // 空字符串也分配一块带引用计数的内存，避免空指针判断
        char* mem = new char[4 + 1];
        *(int*)mem = 1;
        mem[4] = '\0';
        _start = mem + 4;
        _finish = _start;
        _end = _start + 1;
    }

    // 分配内存
    void _allocate(size_t len, size_t cap) {
        char* mem = new char[cap + 4];
        *(int*)mem = 1;
        _start = mem + 4;
        _finish = _start + len;
        _end = _start + cap;
    }

    // 释放内存
    void _release() {
        if (_start && --REF_COUNT(_start) == 0) {
            delete[] (_start - 4);
        }
        _start = _finish = _end = nullptr;
    }

    // 核心分离函数：确保当前对象独占内存后再写
    void _mutate() {
        if (_start && REF_COUNT(_start) > 1) {
            size_t len = size();
            size_t cap = len; // 分离时按当前长度分配，或按原容量分配均可
            if (_end) cap = _end - _start; // 保留原容量
            
            char* newMem = new char[cap + 4];
            *(int*)newMem = 1;
            char* newData = newMem + 4;
            memcpy(newData, _start, len);
            
            // 原内存引用计数减 1
            if (--REF_COUNT(_start) == 0) {
                delete[] (_start - 4);
            }
            
            _start = newData;
            _finish = newData + len;
            _end = newData + cap;
        }
    }
};

// 测试代码
int main() {
    MyStringCOW s1("Hello");
    std::cout << "=== 初始状态 ===" << std::endl;
    s1.debug();

    MyStringCOW s2 = s1; // 浅拷贝
    std::cout << "\n=== s2 = s1 后 ===" << std::endl;
    s1.debug();
    s2.debug();

    std::cout << "\n=== 触发 COW：修改 s2 ===" << std::endl;
    s2[0] = 'h'; // 触发写时拷贝
    s1.debug();
    s2.debug();

    std::cout << "\n=== 触发 COW：s2 push_back ===" << std::endl;
    s2.push_back('!');
    s1.debug();
    s2.debug();

    return 0;
}
~~~
