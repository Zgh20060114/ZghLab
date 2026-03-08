import torch
import matplotlib.pyplot as plt

# 1. 定义生成数据的函数
def synthetic_data(w, b, num_examples):
    """生成y=Xw+b+噪声"""
    X = torch.normal(0, 1, (num_examples, len(w)))
    y = torch.matmul(X, w) + b
    y += torch.normal(0, 0.01, y.shape)
    return X, y.reshape((-1, 1))

# 2. 生成数据
true_w = torch.tensor([2, -3.4])
true_b = 4.2
features, labels = synthetic_data(true_w, true_b, 1000)

# 3. 可视化设置（解决中文显示问题，可选）
plt.rcParams['font.sans-serif'] = ['SimHei']  # 中文显示
plt.rcParams['axes.unicode_minus'] = False    # 负号显示

# -------------------------- 可视化1：单特征 vs 标签（散点图） --------------------------
# 子图1：第一个特征（X[:,0]）与标签的关系
plt.figure(figsize=(12, 5))

plt.subplot(1, 2, 1)
# 转换为numpy（matplotlib不直接支持torch张量）
plt.scatter(features[:, 0].numpy(), labels.numpy(), alpha=0.5)
plt.xlabel('特征1 (X1)')
plt.ylabel('标签 (y)')
plt.title(f'特征1 vs 标签（真实权重w1={true_w[0]}）')
plt.grid(alpha=0.3)

# 子图2：第二个特征（X[:,1]）与标签的关系
plt.subplot(1, 2, 2)
plt.scatter(features[:, 1].numpy(), labels.numpy(), alpha=0.5, color='orange')
plt.xlabel('特征2 (X2)')
plt.ylabel('标签 (y)')
plt.title(f'特征2 vs 标签（真实权重w2={true_w[1]}）')
plt.grid(alpha=0.3)

plt.tight_layout()  # 调整子图间距
plt.show()
