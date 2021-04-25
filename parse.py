#!/bin/python3
import struct
import numpy as np

# Read data file in .py model as byte-string
with open('data/archive/data/94779429638048', 'rb') as f:
    t = f.read()

# format into 4 byte-string
weight_data_b = [t[4*i:4*i+4] for i in range(len(t)//4)]

# for every element in list convert 4 bytes to float
weight_data_f = [struct.unpack('f', el)[0] for el in weight_data_b]

# convert to numpy array and reshape to same dimension as in Pytorch
# self.conv1 = nn.Conv2d(1, 32, 3, 1)
conv1_weight = np.array(weight_data_f).reshape(3, 32, 3, 1)


print(conv1_weight)