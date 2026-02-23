#!/usr/bin/env python3

import torch

x = torch.tensor([1, 1.3], requires_grad=True)
print(x.shape)
y = torch.empty(3, 1, 3, 2).fill_(1)
print(y.squeeze().shape)
print(x == y)
print(x.sum(dim=0))
z = torch.Size([12])
print(z)
