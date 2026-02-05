## python fundamental
- 缩进表示将语句分成代码块
- `if-elif-else `
- `print(f"{name} is {age} years old")`
- `print("asdf",end=xxx)`,
- 读取输入 name = input("enter name :")
- 不像c++,python的空语句会报错,用`pass`; 占位时`pass`和`...`功能相同,`...`除了占位的功能外还有空值语义
- python 无显式声明变量直接使用
- 三元运算: 结果1 if 条件 else 结果2
- del 删除变量/元素
- int 和 str 没法比较
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
- int(a) 转换,失败会报错ValueError; c++的转换:抛弃c风格,用 static_cast<int>(a); const_cast<int>(a)仅适合去除指针/引用变量的const属性;dynamic_cast向下转换,继承转换
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
- 格式化字符窜f-string: f'{变量:格式说明符}'
#### List
- `name = ["sd","fg","kl"]`
- 注明类型: `name: list[Any]`
###### list operator
- append
- insert
- + 连接两个list
- len(name)
- in /not in 
- 复制 name*4
- list 就不是为数学计算设计的,是为了通用数据储存和操作的
- `for na in name:`
- 返回第一个出现的索引:`name.index("sd") `
- remove/del, 删除元素
- reverse 反转
###### list sort 
- 就地排序
  - `name.sort() ` 原地修改, 仅list可用
  - `name.sort(reverse=True) ` 生成新的的, 可迭代对象均可使用
- na = sorted(name)
#### File manager
- `with open('input.txt', 'rt') as f_read, open('output.txt', 'wt') as f_write:`
- t文本模式,b二进制模式,r只读模式,r只写模式
- with是python中专门为资源管理设计的,自动可靠的释放资源,不用手动的`file.close()`
- `read/write`
- 按行迭代:`for line in file:`
- `with open('outfile', 'wt') as out:
    print('Hello World', file=out)`, 使用print输出到文件中相较于`file.write("hello world\n") `的好处就是自动添加换行符\n
- `next(file)` 调用一次迭代一次
#### Function
- `def fuc(n): `
- 可校验参数类型: `def fuc(n:int|double):`
- 文档字符串必须放在函数/类/模块的第一行
- 捕获并处理异常
```python
try:
  xxx
except xxx:
  xxx
```
- raise:抛出异常
## working with data && data struct
- 空值类型 :`name = None`, 为一个后续会赋值的变量提前占位
#### tuple
- `tup = ("sd",1,1.1,1)` ,元组,列表都是有序可重复的数据结构;但是list是可变数据结构,而tuple则是只读的不可修改,但是可以根据当前元组元素构造新的元组
- 既然都有了list,那tuple设计出来的目的是什么呢: 核心目的是"不可变的",不可变就防止数据篡改,可做字典键/集合元素(只有不可变元素才能被hash)
- 也可省略()
- `tup = ("sd",) `
- `t1,t2,t3,t4 = tup`,除了用索引外
- tuple是不可变的,所以就没有append
#### dictionary
- `dic = {"as": 1, "qw": "11", "qw": "12"} `
- 底层hash,与cpp的std::unordered_map实现一致,无序,可修改,重复的会覆盖
- list(dic),字典转化成列表,获得所有的键
- `for di in dic:` 迭代获取的是键,不能使用`for k,v in dic`
- `dic.keys() `,获得实时自动跟随变化的键
- 获得键值对:`for k,v in dic.items(): `
- item 项,物品,元素
- `dic.get("ass", None): `, 找不到有默认值
- 不可变的类型可做dictionary's key,如元组
- 无append,直接写键幅值即可
#### set
- 无序,不可重复(会自动去重)
- add
## format 格式化
- `f"{数据:[对齐符][占宽数字][整数格式编码]}" `
  - 占宽数字：指定数据在n个字符的固定区域内展示（不足补空格，超出则按实际长度显示）；
  - 对齐符：>（右对齐）、<（左对齐）、^（居中对齐），未指定时默认右对齐（数字）/左对齐（字符串）。
  - ![格式编码](assets_DabeazPython/2026-02-03-22-37-17.png)
- `'{name:>10s} {shares:10d} {price:10.2f}'.format(name='IBM', shares=100, price=91.1)`
- ` s = {
      'name': 'IBM',
      'shares': 100,
      'price': 91.1
  }
  '{name:>10s} {shares:10d} {price:10.2f}'.format_map(s)`, 相当于是format的字典(映射)特供版
## sequence datatype 序列式数据类型
- string
- list
- tuple
- `a = [0,1,2,3,4,5,6,7,8]  a[2:4] = [10,11,12]  # [0,1,10,11,12,4,5,6,7,8]` ,重新分配的切片不必与原来长度相同
- `range(start,stop,step)`, `range(10,0,-1) ` 只能生成整数序列
- `for n,s in enumerate(se,start): ` 生成counter and iteration 
- `ts = zip(tup, se) ` 接收可迭代对象(如:list,string,tuple...)返回的是zip迭代器类型,只能迭代一次;如需多次使用,使用`list(ts),tuple(ts) `等
