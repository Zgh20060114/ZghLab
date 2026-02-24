#!/usr/bin/env python3

import torch

x = torch.tensor([1, 1.3], requires_grad=True)
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
