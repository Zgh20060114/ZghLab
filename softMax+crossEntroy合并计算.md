**将 Softmax 和交叉熵损失“合并计算”，而非分开计算，可以解决数值溢出/下溢导致的稳定性问题**——关键是利用 `log(exp(x)) = x` 的数学性质，抵消指数运算，避免中间步骤出现 `inf`/`NaN`。

下面用「问题根源→解决方案→数学推导→实际意义」四层，把这个“聪明的技巧”讲得通俗易懂：

### 一、先搞懂：分开算 Softmax+交叉熵为什么会出问题？
Softmax 的公式是：
$$ \hat{y}_i = \frac{\exp(o_i)}{\sum_{k} \exp(o_k)} $$
交叉熵损失是：
$$ L = -\sum y_i \log(\hat{y}_i) $$

如果**先算 Softmax 得到 $\hat{y}$，再算交叉熵**，会遇到两个数值稳定性问题：
1. **指数上溢**：如果 $o_i$ 很大（比如 1000），$\exp(o_i)$ 会超出浮点数范围，变成 `inf`；
2. **指数下溢**：如果 $o_i$ 很小（比如 -1000），$\exp(o_i)$ 会趋近于 0，变成 `0`，后续取 `log(0)` 会得到 `-inf`，最终导致损失/梯度变成 `NaN`。

这就是文字中说的“数值稳定性问题”——分开计算时，指数运算很容易让中间结果超出浮点范围，导致计算失效。

### 二、核心解决方案：合并 Softmax+交叉熵，抵消指数运算
聪明的做法是：**不先算 Softmax 的概率，而是把 Softmax 代入交叉熵公式，合并后化简，避开直接计算 $\exp$**。

#### 步骤1：Softmax 数值稳定版（先减最大值）
为了避免 $\exp(o_i)$ 溢出，先给所有 $o_k$ 减去最大值 $\max(o_k)$（这是数值计算的通用技巧，不改变 Softmax 结果）：
$$ \hat{y}_i = \frac{\exp(o_i - \max(o_k))}{\sum_{k} \exp(o_k - \max(o_k))} $$
减最大值后，$o_i - \max(o_k) \leq 0$，$\exp$ 的结果最大为 $\exp(0)=1$，彻底避免上溢。

#### 步骤2：代入交叉熵，合并化简
把稳定版 Softmax 代入交叉熵公式：
$$
\begin{align*}
L &= -\sum y_i \log\left( \frac{\exp(o_i - \max(o_k))}{\sum_{k} \exp(o_k - \max(o_k))} \right) \\
&= -\sum y_i \left[ \log(\exp(o_i - \max(o_k))) - \log\left( \sum_{k} \exp(o_k - \max(o_k)) \right) \right] \\
&= -\sum y_i \left[ (o_i - \max(o_k)) - \log\left( \sum_{k} \exp(o_k - \max(o_k)) \right) \right]
\end{align*}
$$

#### 关键抵消：$\log(\exp(x)) = x$
上面的推导中，$\log(\exp(o_i - \max(o_k)))$ 直接抵消成 $o_i - \max(o_k)$——**我们再也不用计算 $\exp(o_i - \max(o_k))$ 这个中间值，而是直接用 $o_i - \max(o_k)$**，彻底避开了指数运算的溢出/下溢问题。

这就是文字中“避免计算 $\exp(o_j − \max(o_k))$，而可以直接使用 $o_j − \max(o_k)$，因为 $\log(\exp(·))$ 被抵消了”的核心含义。

### 三、“LogSumExp 技巧”是什么？
上面化简后的损失公式中，还有一项 $\log\left( \sum_{k} \exp(o_k - \max(o_k)) \right)$——这就是“LogSumExp 技巧”：
- 直接算 $\log(\sum \exp(x_k))$ 容易溢出（比如 $x_k$ 大时）；
- 先算 $\log(\sum \exp(x_k - \max(x_k)))$，再加上 $\max(x_k)$（等价变换），就能避免溢出；
- 对应到我们的公式里，$x_k = o_k$，所以这一项本质是 LogSumExp 技巧的应用。

### 四、实际意义：PyTorch 里的 `nn.CrossEntropyLoss` 就是这么做的
你在代码中用的 `nn.CrossEntropyLoss()`，底层逻辑正是如此：
1. 输入不需要传 Softmax 后的概率，直接传模型的原始输出（`logits`，即 $o_i$）；
2. 内部自动完成“减最大值→合并 Softmax+交叉熵→抵消指数”的计算；
3. 既保证了数值稳定性，又避免了手动计算 Softmax 带来的 `inf`/`NaN`。

#### 对比：手动分开算 vs 框架合并算
```python
import torch
import torch.nn.functional as F

logits = torch.tensor([[1000.0, 2000.0]])  # 大数值，直接算exp会溢出
y = torch.tensor([1])

# 错误：先算Softmax（溢出成inf），再算交叉熵
y_hat = F.softmax(logits, dim=1)  # tensor([[0., inf]]) → 溢出
loss_bad = F.nll_loss(torch.log(y_hat), y)  # 结果是nan

# 正确：用CrossEntropyLoss合并计算（无溢出）
loss_good = F.cross_entropy(logits, y)  # 正常输出数值，无nan/inf
print(loss_good)  # 合理的损失值
```

### 五、为什么还要保留传统 Softmax？
文字中提到“我们也希望保留传统的 softmax 函数，以备我们需要评估通过模型输出的概率”——原因是：
- 训练时：用合并计算的方式保证稳定性，不需要 Softmax 概率；
- 推理/评估时：需要知道模型对每个类别的预测概率（比如“这个样本是猫的概率90%”），这时候才需要单独计算 Softmax（此时可以用稳定版 Softmax，先减最大值再算 exp）。

### 总结
这段文字的核心可以浓缩为3句话：
1. 分开算 Softmax+交叉熵容易因指数运算溢出/下溢，导致 `inf`/`NaN`；
2. 合并计算时，利用 $\log(\exp(x))=x$ 抵消指数，直接用模型原始输出（logits）计算损失，解决数值稳定性问题；
3. 训练用合并计算（保证稳定），推理用单独的 Softmax（获取概率）——这就是 PyTorch `CrossEntropyLoss` 的底层逻辑，也是“LogSumExp 技巧”的应用。

简单记：**合并计算 = 绕开容易出问题的指数运算，既算对损失，又不溢出**。
