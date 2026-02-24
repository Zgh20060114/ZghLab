## **PyTorch Tensor 核心方法大全**

根据 PyTorch 官方文档和实际应用场景，Tensor 的方法可以分为以下十大类：

### **一、创建方法**

| 方法 | 描述 | 示例 |
|:---|:---|:---|
| `torch.tensor()` | 从数据创建张量 | `torch.tensor([[1,2],[3,4]])` |
| `torch.zeros()` | 全零张量 | `torch.zeros(3,3)` |
| `torch.ones()` | 全一张量 | `torch.ones(2,2)` |
| `torch.eye()` | 单位矩阵 | `torch.eye(3)` |
| `torch.rand()` | 均匀分布 [0,1) | `torch.rand(3,3)` |
| `torch.randn()` | 标准正态分布 | `torch.randn(3,3)` |
| `torch.arange()` | 等差数列 | `torch.arange(0,10,2)` |
| `torch.linspace()` | 线性间隔 | `torch.linspace(0,1,5)` |
| `torch.full()` | 填充值 | `torch.full((3,3), 7)` |
| `torch.empty()` | 未初始化 | `torch.empty(3,3)` |

### **二、属性方法**

| 方法 | 描述 | 示例 |
|:---|:---|:---|
| `.shape` 或 `.size()` | 张量形状 | `x.shape` |
| `.dtype` | 数据类型 | `x.dtype` |
| `.device` | 所在设备 | `x.device` |
| `.layout` | 内存布局 | `x.layout` |
| `.ndim` | 维度数量 | `x.ndim` |
| `.numel()` | 元素总数 | `x.numel()` |
| `.T` | 转置（2D） | `x.T` |

### **三、类型转换**

| 方法 | 描述 | 示例 |
|:---|:---|:---|
| `.to()` | 通用转换 | `x.to(torch.float32)` |
| `.float()` / `.int()` | 转浮点/整型 | `x.float()` |
| `.double()` / `.long()` | 转双精度/长整型 | `x.double()` |
| `.half()` / `.short()` | 转半精度/短整型 | `x.half()` |
| `.byte()` / `.bool()` | 转字节/布尔 | `x.bool()` |
| `.type()` | 指定类型 | `x.type(torch.FloatTensor)` |
| `.cpu()` | 转CPU | `x.cpu()` |
| `.cuda()` | 转GPU | `x.cuda()` |

### **四、形状操作**

| 方法 | 描述 | 示例 |
|:---|:---|:---|
| `.view()` | 重塑（共享内存） | `x.view(-1, 4)` |
| `.reshape()` | 重塑（可能复制） | `x.reshape(3, 4)` |
| `.resize_()` | 原地改变形状 | `x.resize_(3, 4)` |
| `.transpose()` | 交换维度 | `x.transpose(0,1)` |
| `.permute()` | 重排维度 | `x.permute(2,0,1)` |
| `.squeeze()` | 压缩维度1 | `x.squeeze()` |
| `.unsqueeze()` | 扩展维度 | `x.unsqueeze(0)` |
| `.flatten()` | 展平 | `x.flatten()` |
| `.cat()` / `torch.cat()` | 拼接 | `torch.cat([x,y], dim=0)` |
| `.stack()` | 堆叠 | `torch.stack([x,y], dim=0)` |
| `.chunk()` | 分块 | `x.chunk(3, dim=0)` |
| `.split()` | 分割 | `x.split(2, dim=0)` |

### **五、数学运算**

#### **基础运算**
| 方法 | 描述 | 示例 |
|:---|:---|:---|
| `+` `-` `*` `/` | 四则运算 | `x + y` |
| `torch.add()` | 加法 | `torch.add(x, y)` |
| `torch.sub()` | 减法 | `torch.sub(x, y)` |
| `torch.mul()` | 乘法 | `torch.mul(x, y)` |
| `torch.div()` | 除法 | `torch.div(x, y)` |
| `.add_()` | 原地加法 | `x.add_(y)` |

#### **矩阵运算**
| 方法 | 描述 | 示例 |
|:---|:---|:---|
| `@` 或 `torch.matmul()` | 矩阵乘法 | `x @ y` |
| `torch.mm()` | 2D矩阵乘法 | `torch.mm(x, y)` |
| `torch.bmm()` | 批量矩阵乘法 | `torch.bmm(x, y)` |
| `.dot()` | 点积 | `x.dot(y)` |
| `.mv()` | 矩阵-向量乘 | `x.mv(v)` |
| `.inverse()` | 矩阵求逆 | `x.inverse()` |
| `.pinverse()` | 伪逆 | `x.pinverse()` |
| `.det()` | 行列式 | `x.det()` |
| `.trace()` | 迹 | `x.trace()` |

### **六、统计方法**

| 方法 | 描述 | 示例 |
|:---|:---|:---|
| `.sum()` | 求和 | `x.sum(dim=0)` |
| `.mean()` | 均值 | `x.mean(dim=1)` |
| `.std()` | 标准差 | `x.std()` |
| `.var()` | 方差 | `x.var()` |
| `.max()` | 最大值 | `x.max(dim=0)` |
| `.min()` | 最小值 | `x.min()` |
| `.argmax()` | 最大值索引 | `x.argmax(dim=1)` |
| `.argmin()` | 最小值索引 | `x.argmin()` |
| `.median()` | 中位数 | `x.median()` |
| `.mode()` | 众数 | `x.mode()` |
| `.prod()` | 累积 | `x.prod()` |
| `.cumsum()` | 累积和 | `x.cumsum(dim=0)` |
| `.cumprod()` | 累积积 | `x.cumprod(dim=0)` |
| `.norm()` | 范数 | `x.norm(p=2)` |
| `.dist()` | 距离 | `x.dist(y, p=2)` |

### **七、比较操作**

| 方法 | 描述 | 示例 |
|:---|:---|:---|
| `>` `<` `>=` `<=` | 比较运算 | `x > 0` |
| `==` `!=` | 相等比较 | `x == y` |
| `.eq()` | 相等 | `x.eq(y)` |
| `.ne()` | 不等 | `x.ne(y)` |
| `.gt()` | 大于 | `x.gt(0)` |
| `.lt()` | 小于 | `x.lt(0)` |
| `.ge()` | 大于等于 | `x.ge(0)` |
| `.le()` | 小于等于 | `x.le(0)` |
| `.all()` | 全部真 | `x.all()` |
| `.any()` | 任一真 | `x.any()` |
| `.where()` | 条件选择 | `torch.where(x>0, x, y)` |

### **八、索引和切片**

| 方法 | 描述 | 示例 |
|:---|:---|:---|
| `[ ]` | 索引切片 | `x[0, 1:3]` |
| `.index_select()` | 索引选择 | `x.index_select(0, idx)` |
| `.masked_select()` | 掩码选择 | `x.masked_select(mask)` |
| `.take()` | 按索引取值 | `x.take(indices)` |
| `.gather()` | 按索引收集 | `x.gather(dim, index)` |
| `.scatter()` | 按索引散射 | `x.scatter(dim, index, src)` |
| `.nonzero()` | 非零索引 | `x.nonzero()` |
| `.where()` | 条件索引 | `torch.where(condition)` |

### **九、归约和累积**

| 方法 | 描述 | 示例 |
|:---|:---|:---|
| `.allclose()` | 是否接近 | `x.allclose(y)` |
| `.isclose()` | 逐元素接近 | `x.isclose(y)` |
| `.equal()` | 完全相等 | `x.equal(y)` |
| `.isfinite()` | 是否有穷 | `x.isfinite()` |
| `.isinf()` | 是否无穷 | `x.isinf()` |
| `.isnan()` | 是否NaN | `x.isnan()` |
| `.unique()` | 唯一值 | `x.unique()` |

### **十、高级操作**

| 方法 | 描述 | 示例 |
|:---|:---|:---|
| `.clone()` | 深拷贝 | `x.clone()` |
| `.detach()` | 分离计算图 | `x.detach()` |
| `.requires_grad_()` | 设置梯度 | `x.requires_grad_()` |
| `.grad` | 梯度值 | `x.grad` |
| `.backward()` | 反向传播 | `x.backward()` |
| `.numpy()` | 转NumPy | `x.numpy()` |
| `.from_numpy()` | NumPy转Tensor | `torch.from_numpy(np_array)` |
| `.item()` | 单元素转标量 | `x.item()` |
| `.tolist()` | 转列表 | `x.tolist()` |
| `.expand()` | 扩展维度 | `x.expand(3,2,4)` |
| `.repeat()` | 重复 | `x.repeat(2,2)` |
| `.roll()` | 循环移位 | `x.roll(1, dims=0)` |
| `.rot90()` | 旋转90度 | `x.rot90(k=1, dims=(0,1))` |
| `.flip()` | 翻转 | `x.flip(dims=(0,))` |

### **实用技巧**

```python
# 查看所有可用方法
print([method for method in dir(torch.Tensor) if not method.startswith('_')])

# 查看方法帮助
help(torch.Tensor.view)

# 检查是否有原地版本
# 带下划线后缀的是原地操作
x.add_(y)  # 原地加法
```

- __带下划线后缀的是原地操作__

### **常用方法速查表**

| 类别 | 最常用方法 |
|:---|:---|
| **创建** | `tensor()`, `zeros()`, `ones()`, `rand()`, `arange()` |
| **属性** | `.shape`, `.dtype`, `.device` |
| **转换** | `.to()`, `.cpu()`, `.cuda()`, `.numpy()` |
| **形状** | `.view()`, `.reshape()`, `.squeeze()`, `.unsqueeze()` |
| **数学** | `.sum()`, `.mean()`, `.max()`, `.min()` |
| **矩阵** | `@`, `.matmul()`, `.t()` |
| **梯度** | `.requires_grad_()`, `.backward()`, `.detach()` |
