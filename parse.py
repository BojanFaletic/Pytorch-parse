import pickle

with open('data/archive/data.pkl', 'rb') as f:
    t = pickle.load(f)

print(t)