''' Simple conv2d implementation this is simplest version possible.
    Input and kernel is size 3x3.
'''

################################################################################
''' Hello world in convolution. This is example of basic conv2d '''

# r = torch.rand(1,1,3,3)
# c1 = nn.Conv2d(1,2,(3,3),1)
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
################################################################################


################################################################################
''' Example where single input is converted to 2 output channels '''

# c1 = nn.Conv2d(1,2,(3,3),1)
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
################################################################################