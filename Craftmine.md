- `std::string_view `是`std::string` 的指针+长度，不是真正的字符串对象，是字符串对象的只读视图
- size_max在<cstdint>头文件里
- space+ca fix_available
file(
  GLOB SRC
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
- 写上GLOB才能使用通配符匹。更推荐inline配
- inline允许多个定义但是必须是同一实体(内联由编译器自行决定，我不关心)；static每个调用的文件都有一个副本。更推荐inline
- constexpr 编译期常量，必须在编译期确定并且全局唯一
- modify 修饰,装饰
- command 命令
- common 普通的，常见的，共用的
- 枚举也可以声明变量
- inl文件存放模板实现代码和公用的一些函数inline
- 非静态成员函数的值无法在编译期确定，所以不能用`constexpr`,只有静态成员变量(static)才行
- guiw 小写
- gUiw 大写
- 用函数返回变量，抛弃extern写法
- ++i更好欧
- leader+sr \r
- unit 单元
- uniform 统一的，一致的，均匀的
- `std::tuple` 将任意不同类型的多个值打包成一个对象，是`std::pair` 的增强版，pair只能打包两个
- `std::move(first,last,value)` 将容器内和value相等的所有元素移动到容器尾部，返回第一个带删除元素的迭代器
- column 列，roman罗马的柱子，竖直的
- 优先类内就地初始化，构造函数初始化列表会覆盖类内就地初始化。当有传参时用构造函数初始化列表，要不然就冗余了
- `std::array` 提供了`data()` 方法，返回容器内首元素的地址（首指针），可以像数组一样使用
- 需要析构函数删除的是动态分配的内存，那用智能指针完全代替new/delete也不能完全淘汰析构函数，因为还有非内存类系统资源
- unique_ptr对象的`reset` 方法接管传参的裸指针
- 仅需要访问一个对象，无需管理它的内存，用裸指针或者引用就够了，没必要用智能指针（无管理，不智能）
- 容器要求里面的元素具有可赋值的能力，而引用不能重新绑定
- 一个裸指针对象要不要在析构函数里取决于传入的是new动态分配的指针，还是已经有归属权的指针（不会混着传入，要不然就写成两个类各司其职）
- 在unix系统中，每个进程启动时，内核会默认打开三个标准文件描述符，分别是：
  - fd = 0, stdin_fileno, 标准输入
  - fd = 1, stdout_fileno，标准输出
  - fd = 2, stderr_fileno, 标准错误
- `int getchar()` 返回的是int类型的ascii码
- 两个hpp文件相互include
- 头文件循环依赖的解决办法：其中一个头文件声明和实现分离(hpp和cpp)，然后在头文件里前向声明
- cmake -Dxxx
- exclude 排除，不包括
- EXCLUDE_FROM_ALL 减少未改变构建开销，隔离不需要的目标
- CMAKE_EXTERN_COMPILE_COMMANDS 不要少s
- define
  - #define PI 3.14 替换
  - #define DEBUG 定义有无

  - ```cpp
    #ifdef ENABLE_TRACING
    #define START_TRACE(traceFile) Trace::start(traceFile)
    #else
    #define START_TRACE(name)  // 空，不起作用
    #endif
    ```
  - 用`#define ENABLE_TRACING` 或者在cmake里用`add_definenations(-DENABLE_TRACING)`

- `target_precompile_headers(glCraft PRIVATE src/glCraft.hpp)` 预编译头文件，防止重复include,提高编译速度
- 使用`explicit`显式构造函数的原因是：防止有非目标类型的参数传入，非目标类型的参数被编译器隐式转换成正确的参数类型然后传入构造函数。
- glad 加载opengl函数
- glfw 创建窗口，处理键鼠输入，管理上下文
- glm 图形学数学库

- ctrl+a 增大数字
- ctrl+x 减小数字
- minecaft中`chunk = 16*16*256个block`, 渲染出所有方块电脑内存会崩溃的,所以只渲染玩家附近的一个chunk
- vertices 是vertex的复数
- persistence 持久化 
- crosshair 准星
- assert是运行时断言,static_assert是编译期断言
- std::is_same_v 编译期类型比较工具
- decltype 返回变量或者表达式的类型(不会执行表达式,只做结果的分析)
- vendor 第三方供应商,依赖
