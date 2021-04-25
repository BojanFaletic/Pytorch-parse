''' Simple conv2d implementation this is simplest version possible.
    Input and kernel is size 3x3.
'''

###############################################################################
''' Hello world in convolution. This is example of basic conv2d '''

# r = torch.rand(1,1,3,3)
# c1 = nn.Conv2d(1,2,(3,3))
kernel = 3

r = [[0.1912, 0.0273, 0.0495],
     [0.4607, 0.2961, 0.1504],
     [0.0339, 0.8246, 0.8690]]


c1_weight = [[-0.1692,  0.2687, -0.2912],
             [0.0439,  0.1569, -0.2579],
             [-0.0684,  0.1400, -0.3261]]

c1_bias = -0.1940

# Convolution
accumulate = c1_bias
for i in range(kernel):
    for j in range(kernel):
        accumulate += r[i][j] * c1_weight[i][j]

print('Simple convolution, this is same as in Pytorch:', accumulate)
###############################################################################


###############################################################################
''' Example where single input is converted to 2 output channels '''

# c1 = nn.Conv2d(1,2,(3,3))
# r = torch.rand(1,1,3,3)
kernel = 3
out_features = 2

r = [[0.4927, 0.1539, 0.7258],
     [0.9000, 0.8926, 0.9953],
     [0.3363, 0.4109, 0.2867]]

c1_weight = [[[0.2758,  0.0727,  0.0982],
              [-0.0086, -0.3061, -0.2400],
              [-0.3296, -0.1635,  0.1889]],

             [[0.0780,  0.2829,  0.2063],
              [-0.0116, -0.0559,  0.2552],
              [-0.2825, -0.0954, -0.3282]]]

c1_bias = [0.2748, 0.1182]

# Output channel detect 2 features on input
accumulate = c1_bias
for feature_idx in range(out_features):
    for i in range(kernel):
        for j in range(kernel):
            accumulate[feature_idx] += c1_weight[feature_idx][i][j] * r[i][j]

print('We detect 2 features:', accumulate)
###############################################################################


###############################################################################
''' Example where 2 input channels are converted to 3 features.
    Chanels can be viewed as RGB color planes or some abstract feature space
'''

# c1 = nn.Conv2d(2,2,(3,3))
# r = torch.rand(1,2,3,3)

kernel = 3
out_features = 3
in_features = 2

r = [[[0.1640, 0.2650, 0.0147],
      [0.4403, 0.5057, 0.2043],
      [0.2392, 0.6689, 0.3018]],

     [[0.6309, 0.8518, 0.9327],
      [0.7837, 0.5857, 0.9766],
      [0.3562, 0.7806, 0.6823]]]

c1_weight = [[[[-0.0158, -0.2133,  0.1029],
              [-0.1312,  0.1872, -0.1012],
              [-0.0848, -0.0846,  0.1795]],

             [[-0.1521,  0.0673, -0.0375],
              [0.1148, -0.1660,  0.0733],
              [0.1111, -0.0197,  0.1394]]],


             [[[-0.1514,  0.2357, -0.1074],
               [-0.2286,  0.1029, -0.2348],
               [-0.1491, -0.0617,  0.1390]],

              [[0.1365,  0.2238, -0.1385],
               [-0.0650, -0.2207,  0.2235],
               [-0.0346, -0.2099,  0.1070]]],


             [[[0.1342,  0.0360, -0.0561],
               [-0.2130,  0.0027, -0.1087],
               [0.1696, -0.1471,  0.0033]],

             [[-0.1362, -0.1953,  0.1336],
              [0.1471,  0.0974,  0.0702],
              [-0.0703,  0.1363, -0.0687]]]]

c1_bias = [0.1892, 0.0328, 0.1596]

# Convolution (2 input, 3 output, 3x3 kernel)
accumulate = c1_bias
for out_f in range(out_features):
    for in_f in range(in_features):
        for i in range(kernel):
            for j in range(kernel):
                accumulate[out_f] += \
                   c1_weight[out_f][in_f][i][j] * r[in_f][i][j]

print('2 color planes, with 3 features:', accumulate)
