- tensor张量:任意维度的数组的统称
  - 零维张量:标量
  - 一维张量:向量
  - 二维张量:矩阵
  - 高维张量
- 指示函数:判断元素是否属于这个集合的函数,属于则返回1,不属于则返回0
- 卷积神经网络cnn:提取空间特征,网络结构数据
- 循环神经网络rnn:时间,文本等序列数据
- dl的关键组件:
  - 数据data
  - 模型model
  - 目标函数objective function,又被称为损失函数loss function
  - 调整模型参数,最小化损失函数的的优化算法algorithm(通常使用梯度下降算法gradient descent)
- 离线学习(不与环境交互):
  - 监督学习:
    - 回归
    - 分类
    - 标签
    - 搜索
    - 推荐
    - 序列
  - 无监督学习:
    - 聚类
    - 主成分分析
    - 因果关系和概率图模型
    - 生成对抗性网络

- cuda:并行计算平台和编程规范,`sudo pacman -S cuda`,安装实现了cuda规范的系统库
- cuda toolkit: 提供开发,编译cuda程序的工具库,其中提供的nvcc用于编译cuda程序
- cuDNN: cuda toolkit的一个扩展库,专门为深度神经网络
- pytorch安装的时候已经把这些依赖库附加了,会优先使用自己带的,所以只用安装pytorch就够了
- pip3 指定python3
- PyTorch 无法构建不规则多维数组
- `x = torch.tensor(标量/元组/列表等类型数组) `
- `x.dtype`:内部储存元素的数据类型
- 方差: $\sigma^2 = \frac{1}{N} \sum_{i=1}^N(x_i-\mu)^2$ 
- 标准差: $\sigma = \sqrt{\sigma^2}$
#### tensor
- tensor创建方法:

| 方法                | 描述                | 示例                  |
|---------------------|---------------------|-----------------------|
| `torch.tensor()`    | 从数据创建张量      | `torch.tensor([[1,2],[3,4]])` |
| `torch.zeros()`     | 全零张量            | `torch.zeros(3,3)`    |
| `torch.ones()`      | 全一张量            | `torch.ones(2,2)`     |
| `torch.eye()`       | 单位矩阵            | `torch.eye(3)`        |
| `torch.rand()`      | 均匀分布 [0,1)      | `torch.rand(3,3)`     |
| `torch.randn()`     | 标准正态分布        | `torch.randn(3,3)`    |
| `torch.arange()`    | 等差数列            | `torch.arange(0,10,2)`|
| `torch.linspace()`  | 线性间隔            | `torch.linspace(0,1,5)`|
| `torch.full()`      | 填充指定值          | `torch.full((3,3), 7)`|
| `torch.empty()`     | 未初始化空张量      | `torch.empty(3,3)`   |
- torch.Tensor 对象
  - .dtype: 元素数据类型 (float32, int64, etc.)
  - .shape: 张量形状 (torch.Size)
  - .device: 存储设备 (CPU/GPU)
  - .layout: 内存布局 (strided/sparse)
  - .data: 实际存储的数据缓冲区
  - .grad: 梯度信息（如果开启）
- [tensor操作](./torch_tensor.md)
- `x.squeeze()` 把1x的维度去掉,简化shape
- 高维tensor的shape只有后两位是行列数,前面的都是分组数
- `z = torch.Size([2,3])` 一个tensor形状对象,不是tensor
- `x.numel()` 元素个数
- `x.reshape(-1,4)`,通过-1来调用此自动计算出维度的功能

- 形状不同的tensor依靠广播机制(不足的进行复制行/列)进行按元素操作
- `索引是x[1,3],切片是x[1:3] `
- 和python数组索引一样,第一个元素的索引是0,最后一个元素的索引是-1,切片左闭右开
- `x[1:3,:], x[:]`其中:表示全部
- `torch.zeros(2, 3) `,创建全0元素tensor
- `x.zero_()` 将x就地元素变0
- `y = torch.zero_like(x)`, 创建与x的shape相同的全0元素tensor
- `X+=Y 或 X[:] = X + Y` 加等或者切片,就地运算,节省内存
- `A = X.numpy()  B = torch.tensor(A) a.item() float(a) int(a)` , 格式转化
- `os.mkdir(dir_path)`只能创建单层目录,`os.makedirs(dir_path, exist_ok=True)`, 创建多层目录,目录存在时不报错,不存在时创建
- pandas的Series一列数据,DataFrame多列数据
- 缺失值处理方式:插值法/删除法, pands的`pd.fillna(xx)`会识别数据中的`NaN`或者`NA`(本质是np.nan), 填写指定的内容
- dummy 假的,虚拟的,傀儡,哑巴
- `pd.get_dummies()` 对数据进行独热编码,进行分类后进行0/1编码
- `X = torch.tensor(inputs.to_numpy(dtype=float))` pandas读取的csv数据是Series/DateFrame表格类型的,不能直接转tensor
- 向量叉乘(仅三维):
  - 代数公式: $\vec{a} \times \vec{b} = (a_2b_3 - a_3b_2)\mathbf{i} + (a_3b_1 - a_1b_3)\mathbf{j} + (a_1b_2 - a_2b_1)\mathbf{k}$ (得到的是向量)
  - 几何公式: $|\vec{a} \times \vec{b}| = |\vec{a}| |\vec{b}| \sin\theta$
- 向量点乘(维度均可):
  - 代数公式: $\vec{a} \cdot \vec{b} = a_1b_1 + a_2b_2 + a_3b_3$（对应坐标相乘后相加）(得到是标量)
  - 几何公式: $\vec{a} \cdot \vec{b} = |\vec{a}| |\vec{b}| \cos\theta$
- 矩阵按元素乘法成为哈达玛积(不是点乘哈)
- `sum_A = A.sum(axis=1, keepdims=True)` 求和的时候保持轴数不便
