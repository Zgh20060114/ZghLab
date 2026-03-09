#!/usr/bin/env python3
import torch
import matplotlib

matplotlib.use("Qt5Agg")
import matplotlib.pyplot as plt


def synthetic_data(w, b, num_examples):
    """生成y=Xw+b+噪声"""
    X = torch.normal(0, 1, (num_examples, len(w)))
    y = torch.matmul(X, w) + b
    y += torch.normal(0, 0.01, y.shape)
    return X, y.reshape((-1, 1))


true_w = torch.tensor([2, -3.4])
true_b = 4.2
features, labels = synthetic_data(true_w, true_b, 1000)

print(len(features))
# TODO:

plt.rcParams["font.sans-serif"] = ["FZHei-B01"]  # 中文显示
plt.rcParams["axes.unicode_minus"] = False  # 负号显示

plt.figure(figsize=(12, 5))

plt.subplot(1, 2, 1)
plt.scatter(features[:, 0].numpy(), labels.numpy(), alpha=0.5)
plt.xlabel("特征1 (X1)")
plt.ylabel("标签 (y)")
plt.title(f"特征1 vs 标签（真实权重w1={true_w[0]}）")
plt.grid(alpha=0.3)

plt.subplot(1, 2, 2)
plt.scatter(features[:, 1].numpy(), labels.numpy(), alpha=0.5, color="orange")
plt.xlabel("特征2 (X2)")
plt.ylabel("标签 (y)")
plt.title(f"特征2 vs 标签（真实权重w2={true_w[1]}）")
plt.grid(alpha=0.3)

plt.tight_layout()  # 调整子图间距
plt.show()


# import matplotlib.font_manager as fm
#
# # 列出所有带 wenquanyi 或 micro 的字体
# fonts = [
#     f.name
#     for f in fm.fontManager.ttflist
#     if "wen" in f.name.lower() or "micro" in f.name.lower()
# ]
# print("Matplotlib 能找到的相关字体：")
# for f in sorted(set(fonts)):
#     print(f" - {f}")
#
# # 也可以看看所有中文字体
# chinese_fonts = [
#     f.name
#     for f in fm.fontManager.ttflist
#     if any(c in f.name for c in ["Hei", "Kai", "Song", "Mono"])
# ]
# print("\n中文字体列表：")
# for f in sorted(set(chinese_fonts))[:20]:  # 只打前20个
#     print(f" - {f}")
