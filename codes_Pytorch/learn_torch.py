#!/usr/bin/env python3

from numpy import std
import torch
from torch.utils import data
from torch import nn

x = torch.tensor([1, 1.3], requires_grad=True)
print(x)
print(x.shape)
y = torch.empty(3, 2).fill_(1)
print(y.squeeze().shape)
print(x == y)
print(x.sum(dim=0))
z = torch.Size([12])
print(z)
a = torch.tensor([[1], [2], [3]])
print(a + x)

b = [0, 1, 2, 3, 4]
d, e = b[1:3], b[3:5]
print(d, e)
print(b[1:3])
print(x[1:2])
c = y.numpy()
print(torch.tensor(c))
f = x.clone()
print(x * f)

g = torch.ones([6]) / 6
print(g)
h = torch.distributions.multinomial.Multinomial(8, g).sample([2])
print(h)

# print(torch.tensor([[1, 2], [3, 4]]))
# for i in range(4):
#     print(i)


# def generator(n: int):
#     while n >= 0:
#         yield n - 1
#         n -= 1
#
#
# x = generator(10)
# for i in x:
#     print(i)

# data.TensorDataset()
# net = nn.Sequential(nn.Linear(2, 1))
# net[0].weight.data.normal_(0, 0.01)
# net[0].bias.data.fill_(0)
# print(net[0])
# loss = nn.MSELoss()
# optim = torch.optim.SGD(net.parameters(True), lr=0.1)
#
# net.apply()
# torch.nn.functional.nll_loss()
# nn.CrossEntropyLoss(reduction="none")

# x[1] = 2
# print(x)


# x.backward()
def init_weight(m):
    nn.init.normal(m.weight, mean=0.0, std=0.1)
    nn.init.normal(m.bias, std=0.1)
    nn.init.constant(m.bias, 0.0)
    nn.init.dirac


nn.MSELoss(reduction="mean")
