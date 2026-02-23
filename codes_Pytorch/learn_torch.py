#!/usr/bin/env python3

import torch

x = torch.tensor([[1, 1.3], [0, 9]], requires_grad=True)
print(x.shape)
y = torch.empty(3, 3).fill_(1)
print(y.squeeze())
