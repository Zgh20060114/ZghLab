#!/usr/bin/env python3

from numpy import printoptions, std
import torch
from torch.utils import data
from torch import nn

# x = torch.tensor([1, 1.3], requires_grad=True)
# print(x)
# print(x.shape)
# y = torch.empty(3, 2).fill_(1)
# print(y.squeeze().shape)
# print(x == y)
# print(x.sum(dim=0))
# z = torch.Size([12])
# print(z)
# a = torch.tensor([[1], [2], [3]])
# print(a + x)
#
# b = [0, 1, 2, 3, 4]
# d, e = b[1:3], b[3:5]
# print(d, e)
# print(b[1:3])
# print(x[1:2])
# c = y.numpy()
# print(torch.tensor(c))
# f = x.clone()
# print(x * f)
#
# g = torch.ones([6]) / 6
# print(g)
# h = torch.distributions.multinomial.Multinomial(8, g).sample([2])
# print(h)
#
# # print(torch.tensor([[1, 2], [3, 4]]))
# # for i in range(4):
# #     print(i)
#
#
# # def generator(n: int):
# #     while n >= 0:
# #         yield n - 1
# #         n -= 1
# #
# #
# # x = generator(10)
# # for i in x:
# #     print(i)
#
# # data.TensorDataset()
# # net = nn.Sequential(nn.Linear(2, 1))
# # net[0].weight.data.normal_(0, 0.01)
# # net[0].bias.data.fill_(0)
# # print(net[0])
# # loss = nn.MSELoss()
# # optim = torch.optim.SGD(net.parameters(True), lr=0.1)
# #
# # net.apply()
# # torch.nn.functional.nll_loss()
# # nn.CrossEntropyLoss(reduction="none")
#
# # x[1] = 2
# # print(x)
#
#
# # x.backward()
# def init_weight(m):
#     nn.init.normal(m.weight, mean=0.0, std=0.1)
#     nn.init.normal(m.bias, std=0.1)
#     nn.init.constant(m.bias, 0.0)
#     nn.init.dirac
#
#
# nn.MSELoss(reduction="mean")
# net = nn.Sequential(nn.Linear(2, 2), nn.ReLU(), nn.Linear(2, 1))
# # net[0].bias.data.fill_(0)
# # print(net[0].bias)
# print(*[(name, param.data) for name, param in net.named_parameters()])
# print(net[0].state_dict())
#
# print(torch.any(x))
#
# # print(torch.zero_(torch.tensor([1, 1])))
#
# print(
#     torch.randn(
#         2,
#     )
# )


class MyLinear(nn.Module):
    def __init__(self, in_units, units):
        super().__init__()
        self.weight = nn.Parameter(torch.randn(in_units, units))
        self.bias = nn.Parameter(
            torch.randn(
                units,
            )
        )

    def forward(self, X):
        linear = torch.matmul(X, self.weight) + self.bias.data
        return nn.functional.relu(linear)


linear = MyLinear(2, 2)
print(linear.weight.data)
in_unit = torch.randn(1, 2)
out = linear(in_unit)
out.sum().backward()
print(linear.weight.grad)
print(torch.cpu.is_available())
print(torch.cuda.device_count())
tensor_cuda = torch.tensor([1, 2], device="cuda")
print(tensor_cuda)
tensor_cpu = tensor_cuda.cpu()
print(tensor_cpu.device)
tensor_cuda1 = tensor_cpu.cuda(0)
print(tensor_cuda1.cuda(0) is tensor_cuda1)
# linear.to("cuda")

print(in_unit.max())
nn.MaxPool2d(3)
linear.train()
nn.Conv3d()
