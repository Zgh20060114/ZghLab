- namespace里的内容顶格写,在结尾}//end of namespace xx
- 匿名命名空间: 防止本文件里的只供内部使用的辅助函数,工具类,结构体或常量等等被其他文件调用,是static的现代替代
- 尽量用const常量代替宏定义常量
- **指向常量的指针**: const在*之前, `const int * ptr`, `int const * ptr`, 该常量不能变,其他随意.
- **常量指针**: const在*之后, `int * const ptr`, 该指针指向的地址不能变,其他随意
- 指向常量的指针才能指向常量
- 数组名arr退化成了数组第一个元素的地址, `int * ptr = arr`.
- arr 和 &arr的值是一样的,但是含义不同
- &arr没有退化,是对整个数组取地址, `int (*ptr)[5] = &arr`, ptr是一个**数组指针**, ptr是一个指向有5个int元素数组的指针
- 指针数组就是元素是指针的数组
- 用**函数指针**实现回调,`std::function`和`lambda`实现回调的底层实现就是函数指针, 函数名也是一个地址, `返回类型 (*ptr)(参数类型) = func;`
- typedef 的核心作用是“给现有的数据类型起一个别名”.
- 指针函数就是返回值是指针的函数.
- 局部变量的地址,函数调用完会被销毁, 这个地址就是野指针.
- c++中的栈上放的是编译器管理的内容,堆上放的就是程序员手动管理的内容.现代 C++ 的RAII,智能指针,stl容器等等,本质上都是在想办法“让编译器尽可能多地接管堆内存的管理权”，从而解放程序员。
- `int * ptr = new int(100); free(ptr)`
- `int * ptr = (int *)malloc(sizeof(int)); *ptr = 100; delete ptr; ptr = nullptr;(安全回收)`
- `int * ptr = new int[5](); delete[] ptr;`
- `int * ptr = new int[5]{1,2,3,4,5}; delete[] ptr;`
- 在c++中使用的c风格字符串是const常量, `const char * ptr = "hello";`
> [!NOTE]
> c++的输出流运算符对char *有默认重载效果,所以`std::cout<< ptr;` 没有输出指针的地址而是输出了hello.
- 引用本质就是一个受限制的指针(常量指针const pointer)
> [!NOTE]
> 只要参数没有带 &（引用）或 *（指针），C++ 就会在背后默默地为实参做一次完整的拷贝.
- 传参方式:当形参是内置类型(int,float, char等等)或者小型结构体(std::pair,std::optional等等),直接传值,使用引用反而开销更大;当参数是大型对象(std::vector,std::string等等)或者自定义复杂类,并且不需要修改,用const &; 当参数需要修改时用&; 当参数可是为空时用指针*.
- 引用作为函数返回值
> [!NOTE]
> 在现代 C++ 中，直接按值返回函数中创建的临时大对象（如std::string）即可. 编译器会通过 **RVO/NRVO 机制(解决"函数内部创建了新对象并返回，返回时避免拷贝"问题)** 和移动语义（Move Semantics）帮你消除拷贝开销(是的,没有优化时return会触发一次拷贝构造函数,但仅对于return局部变量才会优化)。只有当你明确需要“修改原对象”或“链式调用”或返回正常大变量时，还是要使用返回引用.  (函数返回引用值一定不能是局部变量)
> [!NOTE]
> C++ 标准规定，**对引用取地址**，等价于对引用绑定的变量本体取地址 
- 类型转换: `static_cast`(基本数据类型的转化,父类和子类之间指针(或引用)类型的转化) `dynamic_cast`(父类和子类之间的转换) `const_cast`(常量转化成非常量,基本不用) `reinterpret_cast`(任意指针(或引用)类型的转换,万能转换)
- 函数重载: c++中不允许通过返回值类型的不同来重载函数, 通过参数的类型,个数,顺序进行重载.
- `extern "C"{...}`, 在c++中的c代码按照c的方式编译.
> [!NOTE]
> 一个完整的linux操作系统 = linux内核 + linux环境/用户空间(user space)(系统配置文件,各种基础命令,系统包管理器,图形化界面等), 这个user space 即linux环境. 在已经有linux内核的安卓设备上运行的tiny container只需要把debain的linux环境打包搬到安卓设备上来,然后通过proot(pseudo root假根)技术欺骗linux环境的路径.    
- 函数默认参数要放到最后面, 默认参数的值要写到函数声明里,不要写在函数定义中.
- 当不想再头文件函数声明时暴露参数默认值,可以用函数重载.
- 函数重载时谨慎使用函数默认参数,可能会引起二义性.
- 任何数字和指针都可以隐式转换为bool值. 空指针就是false.
- 空指针: 指针的值是0(0=nullptr)(指针里存的地址是0x00000000特殊地址,访问这个指针指向的内容会中断),意思为这个指针还没有指向有意义的对象.
- nullptr是std::nullptr_t 类型的.
- 在Linux下编写并编译一个C/C++程序时,操作系统在加载这个程序到内存中运行时，会按照这套区域分布来为它分配内存空间。 ![c++程序在linux下的内存布局](assets_CPP_WD/2026-07-12-11-59-01.png)
> [!NOTE]
> `void *` 一种特殊的指针类型,又称通用指针/无类型指针,可以指向任何类型的数据, 大多数类型的指针都能转换成void *.
- c++中c风格字符串写法: `char str[] = "hello"`, `const char * pstr = "hello"`
- 大驼峰,小驼峰,分词下划线,词首下划线.
- struct-public-inline, class-private-inline
- 构造函数可以重载.
- 构造函数列表初始化才是真正的初始化,而不是赋值(赋值无法面对const成员变量),`  Point(int x, int y) : _x(x), _y(y) {}`.
- 一个类所占空间大小 = 类中数据成员变量类型大小之和(但有时由于**内存对齐机制**的原因不等于)
- 为什么存在内存对齐:cpu对内存的读取不是连续的,是分块读取(块的大小只能是1,2,4,8,16...字节),如果成员类型大小之和超出块的大小,那么其中一些数据需要分多次读取再计算进行拼接, 所以内存对齐以浪费空间为代价来换取读取数据的便利性.64位系统默认读取的块大小为8字节.
- 内存对齐的规则: 类的大小是占空间最大的数据类型大小的整数倍; 类的大小还和数据成员的声明顺序有关, 建议:从大到小降序排列(编译器不会自动优化,会严格按照声明顺序在内存排列)
- `#pragma pack(push, n)`, `#pragma pack(pop)`,手动干预struct/class的内存对齐的大小:成员变量的对齐边界取 n 和成员自身大小中的较小值.
- 指针的大小是8字节.
> [!NOTE]
> 如果你发现自己必须手写析构函数，这其实是一个“设计警告”：说明你的代码可能不够现代。
> [!NOTE]
> 在现代 C++ 中，“五法则”是用来理解底层原理的，而“零法则”才是用来写代码的.尽量用智能指针把底层资源包装起来，让你的业务类永远停留在“什么都不写”的舒适区. 
> [!NOTE]
> 需要管理资源/需要指针时, 要么0个,要么5个,追求0个, 无奈5个(不得不写时就把5个写完追求极致性能).[05法则用法](./05法则.md)
> [!NOTE]
> 3法则是c++98的过时规矩, 05法则是现代c++的进化规矩.
- 析构函数清理成变量量申请的堆空间.
- 拷贝构造函数: `类名(const 类名 &rhs){}`
- rhs: right head side; lhs: left head side.
- 不写拷贝构造函数的拷贝是浅拷贝, 浅拷贝只会把复制的指针和原指针指向同一块地址, 引发double free.
- 函数值传递时,会把实参的值拷贝给形参. 所以函数值传递类对象时会调用拷贝构造函数.
> [!WARNING]
> `类名(const 类名 &rhs)`, 如果不是&,就变成了值传递, 然后拷贝构造函数无限调用,程序崩溃; 如果不是const, 就只能接收左值,不能接收右值了.
- 能取地址的是左值, 不能取地址的是右值.
- 右值: 匿名变量(没有名字的变量),字面量. 右值的生命周期只在当前行.
- 非const引用只能绑定左值,不能绑定右值; const引用既可以接收右值也可以接受左值.
- const引用形参的优点: 不拷贝, 防修改, 左值右值都兼容.
- 区分调用的是拷贝构造函数还是拷贝赋值运算符函数:
  - 拷贝构造函数: 从无到有,创建新对象lhs.
  - 拷贝赋值运算符函数: 覆盖已有,lhs已经存在(所以就不存在对象的构造).
- 拷贝赋值运算符函数: `类名 &operator=(const 类名& rhs)`, 本质是`p2.operator=(p1);`.
- `this`: 常量指针,`类名 *const ptr`,指向调用者本身.`return *this;`返回对象本身.
- this指针保存在寄存器中,不在内存中,所以无法取到this指针的地址.
- 对象调用成员函数时,编译器会把对象的地址传递给成员函数隐藏的this形参(第一个参数).
- 类成员变量的初始化顺序是声明的顺序.
> [!WARNING]
> 初始化列表中的书写顺序，永远与类中声明的顺序保持一致！
- c++类中有**4种特殊成员变量**💡💡:常量成员变量,引用成员变量,类对象成员变量,静态成员变量. 它们的初始化与普通成员变量有所不同.
  - 常量成员变量: `const int _a = 1;`这只是类内默认初始化,想改变默认初始化值必须在构造函数的列表初始化中完成. 一个含有const成员变量的类对象不能进行简单的赋值运算`p1=p2;`(编译器会自动删除该类的默认拷贝赋值运算符函数),必要时需要自己写出拷贝赋值运算符函数.
  - 引用成员变量: `int & _ref = num;`这也只是类内默认初始化, 想改变默认初始化值也必须在构造函数的列表初始化中完成.`(编译器会自动删除该类的默认拷贝赋值运算符函数),必要时需要自己写出拷贝赋值运算符函数
  - 类对象成员变量: 要么用花括号来类内默认初始化`Point _p1{1, 2};`,要么用拷贝构造函数`Point _p1=Point(1,2);`, 要么类构造函数初始化列表初始化`Line(): _p1(1,2){}`
  - static静态成员变量: 不属于任何一个类对象,被该类的所有对象共享, 存储在全局变量/静态变量区,并不占据对象的内存存储空间. 初始化必须放到**类外**:`int Computer::_static_price = 0;`, 语法上可以通过类对象调用,但是更推荐通过类名作用域限定符调用.
> [!WARNING]
> 类内默认初始化类对象用()是错误的:`Point _p1(1,2);`❌❌,要用{}.
- `=delete` :删除函数(可用于任何函数); `=default` :请编译器按照默认规则帮我生成这个函数(只能用于类中的6个特殊成员函数).
- c++类中有**2种特殊成员函数**💡💡: static静态成员函数,const常量成员函数.
  - static静态成员函数不属于任何一个类对象,语法上可以通过类对象调用,但是更推荐通过类名作用域限定符调用.
  - static静态成员函数因此没有this指针.因此**static静态成员函数不能直接调用非静态成员函数和非静态成员变量**,只能直接调用静态成员函数和静态成员变量.但是能触发类的6个特殊成员函数,能通过类对象传参间接调用非静态成员函数和非静态成员变量.
  - const常量成员函数: `xx func() const {}`,不能修改类的成员变量.编译器会自动给const常量成员函数的this指针变成双重const限定指针(因此可以重载).(不能修改类成员变量意味着还要防止类成员变量通过返回值被修改的可能)因此:**如果返回值是类成员变量的引用或指针，它必须携带 const 限定符**，以防止外部通过返回值修改对象内部状态。
- 类的const对象只能调用类的const成员函数; 类的非const对象可以调用const版本成员函数,但是优先调用非const版本成员函数.
- 变量初始化使用{}而不是()的优点(就是所谓的"统一初始化",一个花括号统一了c++98时期各种类型的各种初始化方式):
  - {}禁止数据隐式窄化转换
  - `T obj();` 有二义性,误解为函数声明.
- 一个自定义类能使用new delete创建回收堆对象,说明类内(默认)提供了operator new和operator delete运算符重载函数.
- 一个类只能生成堆对象,不能生成栈对象: 把析构函数设为private; 一个类只能生成栈对象,不能生成堆对象: 把operator new和operator delete函数设为private.
- 单例模式: 这个类只能有一个实例对象.
- static是怎么延长函数中临时变量生命周期的: 把临时变量的储存位置从栈上挪到全局/静态存储区(**地址永不变**). static变量只初始化一次,后续调用直接跳过初始化. 
> [!NOTE]
> `static auto stc_ptr = std::make_unique<Point>(1, 2);`这个stc_ptr是在全局/静态存储区,stc_ptr指向的对象在堆上.
- 现代c++单例模式规范写法及调用:
<details>
<summary>点击查看代码</summary>

```cpp
#include <iostream>
#include <string>

class Logger {
public:
    // 1. 获取单例实例的唯一入口
    static Logger& getInstance() {
        static Logger instance; // C++11 保证线程安全且只初始化一次
        return instance;
    }

    // 2. 业务方法
    void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }

    // 3. 禁止拷贝和移动，确保全局唯一性
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

private:
    // 4. 私有构造函数，防止外部直接创建
    Logger() {
        std::cout << "Logger instance created." << std::endl;
    }

    // 5. 析构函数（可选，用于释放资源）
    ~Logger() {
        std::cout << "Logger instance destroyed." << std::endl;
    }
};
//调用
    Logger& logger = Logger::getInstance();
    logger.log("Application started");
//或
    Logger::getInstance().log("Processing data...");
// 当单例实例需要灵活的配置时,不能在getInstance初始化,写一个init():
    void init(const std::string& logPath, int level) {
        logPath_ = logPath;
        level_ = level;
        std::cout << "Logger configured: path=" << logPath_
                  << ", level=" << level_ << std::endl;
    }
```
</details>

- `<string>`标准库提供了一个`basic_string`类模板,string类的本质其实是`basic_string`类模板关于char类型的实例化.
- `std::string::iterator it = str.begain();`
- ![std::string操作](assets_CPP_WD/2026-07-22-14-41-12.png)
- basic_string还进行了运算符重载,支持使用==、>、< 等符号来比较两个字符串的内容.
- 迭代器可以看作是指针,迭代器可以像指针一样:`*it`,`++it`, `it1==it2`.....
- `std::vector`: 自动调整自身大小; 允许任意位置插入和删除元素; 有直接访问某个元素的能力.
> [!WARNING]
> 由于类在编译期进行内存对齐,所以成员变量声明时不能使用auto自动推导, 一般使用`std::vector<int> vec{1, 2};`进行声明, 只有成员函数内部局部变量和成员函数返回值可以用auto.
> [!NOTE]
> C++17 起，auto 配合列表初始化已成为标准实践, ` auto vec = std::vector<int>{1, 2, 3};`
- shrink 缩小
- std::vector有两个属性:`size`和`capacity`, `reserve`提前预留出capacity大小的空间, 适合已经清楚大小,较大的情况.
- ![std::vector操作](assets_CPP_WD/2026-07-23-11-47-33.png)
- ![stream](assets_CPP_WD/2026-07-23-16-51-14.png)
- ![stream继承图](assets_CPP_WD/2026-07-23-16-51-56.png)
- stream分类: 标准i/o, 文件i/o, 串i/o(向/从字符串中写入/读取数据)
- stream的四种状态`googbit`(正常状态),`eofbit`(结束状态(提前按下ctrl+d或者文件结束)),`failbit`(可恢复错误状态),`badbit`(不可恢复错误状态):
![stream的四种状态](assets_CPP_WD/2026-07-23-17-18-33.png)
- stream流状态判断函数: `xxstream.good()`,`xxstream.eof()`,`xxstream.fail()`,`xxstream.bad()`,都是`bool xxx() const`形式.
- 标准i/o流的三个实例:`std::cin`,`std::cout`,`std::cerr`.(是唯一对象,所以可以取地址)
- `std::cin >>`以空白字符(空格,换行,制表等)为分隔符.
- 从failbit状态恢复做法:
<details>
<summary>点击查看代码</summary>

```cpp
  if (!std::cin.good()) {
  std::cin.clear(); //恢复流的状态
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //清除缓冲区的内容
  }
```
</details>

- **逗号表达式**:逗号表达式整体的返回值就是最后一个表达式的返回值, belike: `while(std::cin>>num, !std::cin.eof())`.
- `if(std::cin)`和`if(std::cin.good())`效果一样.
- 标准输入/输出流存在输入/输出缓冲区.
- 缓冲区存在三种缓冲机制:
  - 全缓冲: 缓冲区填满才执行io操作, 对磁盘文件的读写.
  - 行缓冲: 当遇到换行符enter后/强制刷新缓冲区后/行缓冲区(默认1024字节)满后/程序结束后,执行io操作, `std::cin`.
  - 不缓冲: 遇到数据就执行io操作, `std::cerr`.
- `std::cout`输出到终端时是行缓冲,输出到文件时是全缓冲.`std::endl`插入换行符,然后强制刷新缓冲区(`\n`+`std::flush`).
- `std::endl`和`std::flush`在任何模式下都强制刷新缓冲区; 换行符`\n`在行缓冲模式下自动刷新缓冲区.
- 用来自`<string>`头文件的`std::getline()`代替`ifs.getline()`.
- `ifs.tellg()`获取游标位置, `if.seekg(offset)`移动offset字节长度相对与文件开头, `ifs.read(data,length)`读取指定长度.
- 连续写入文件: `std::ofstream ofs("log.txt", std::ios::app);`,以追加模式打开文件,并自动定位到文件末尾.
