- 缩进表示将语句分成代码块
- `if-elif-else `
- `print(f"{name} is {age} years old")`
- 读取输入 name = input("enter name :")
- 不像c++,python的空语句会报错,用`pass`
- python 无显式声明变量直接使用
#### Number
- `round()` 四舍五入
- `range()` 生成整数迭代对象
- python的数字类型: bool, int , double, 复数
- c++中的`true/false `是bool类型的值,但在python中`True/False`是数字1/0
- python的整数是动态长度,不会像c++一样有溢出的风险
- python里的双精度浮点数相当于c++里的double,python没有单精度和长双精度
- py中默认的`x/y`是返回浮点数,`x//y` 是返回整数(向下取整);c++的`x/y`返回值是整数还是浮点数取决于xy的类型
- `x**y` 阶乘
- py和cpp都用`& |`表示按位与/或,py用`and or not` 表示逻辑,c++用`&& ||`
- py的`abs`和cpp的`std::abs`适用于整数和浮点数,不要用c风格的abs和fabs
- int(a) 转换
#### String
- python的字符串可以用单引号,双引号,三引号(单引号和双引号作用一样于不跨行的字符串,三引号可多行);
- cpp的单引号是char,双引号才是string
###### string idndex
- python在索引区间这方面特别喜欢左闭右开
- str[-2] 倒数第二个, str[-3:] 倒数第三个到最后,str[-3:0]返回空字符串
###### string operator
- 字符窜的连接: "hello"+s
- 字符串的长度: len(s)
- 字符串成员测试: `test = 'e' in s`, `test = "he" not in s`
- 字符串复制: `replication = s * 5`
###### string method
- 删除字符串前/后空格:`s.strip()` (只能)
- 大小写转换:`s.upper()`, `s.lower() ` (全部)
- 替换字符串内容: `s = "hello world" s.replace("hello","hallo") `
- s.endswith(suffix)     # 检查字符串是否以suffix结尾
- s.find(t)              # t在s中首次出现的位置（索引）
- s.index(t)             # t在s中首次出现的位置（索引）
- s.isalpha()            # 检查字符是否都是字母
- s.isdigit()            # 检查字符是否都是数字
- s.islower()            # 检查字符是否都是小写
- s.isupper()            # 检查字符是否都是大写
- s.join(slist)          # 使用s作为分隔符连接字符串列表slist
- s.rfind(t)             # 从字符串末尾开始搜索t的位置
- s.rindex(t)            # 从字符串末尾开始搜索t的位置
- s.split([delim])       # 使用分隔符delim将字符串拆分为子字符串列表
- s.startswith(prefix)   # 检查字符串是否以prefix开头
- 字符串一旦创建后是无法修改的,修改字符串都是新建的,`s[1]='o'` 是错的
- 将任何值转化成字符串:`str(3)`
- py查看变量类型:`print(type(s).__name__)`,`print(type(s))`,``
- 字节串,引号前+b:`data = b"Hello World\r\n" `
- 原始字符串,引号前+r:`data = r"hello\nworld"`,作用是让反斜杠\仅作为普通字符生效,反斜杠\不再触发转译字符功能
