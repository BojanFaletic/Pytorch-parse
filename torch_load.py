import torch


model = torch.load('mnist_cnn.pt', map_location=torch.device('cpu'))

print(model['conv1.weight'])