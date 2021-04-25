import numpy as np

''' Simple conv2d implementation this is simplest version possible.
    Input and kernel is size 3x3.
'''

# r = torch.rand(1,1,1,1)
# c1 = nn.Conv2d(1,2,(3,3),1)

r = np.array([[0.1912, 0.0273, 0.0495],
              [0.4607, 0.2961, 0.1504],
              [0.0339, 0.8246, 0.8690]])


c1_weight = np.array([[-0.1692,  0.2687, -0.2912],
                      [0.0439,  0.1569, -0.2579],
                      [-0.0684,  0.1400, -0.3261]])

c1_bias = np.array([-0.1940])

# Convolution
accumulate = c1_bias
for i in range(c1_weight.shape[0]):
    for j in range(c1_weight.shape[1]):
        accumulate += r[i, j] * c1_weight[i, j]

print('Simple convolution, this is same as in Pytorch:', accumulate)
