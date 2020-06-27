import numpy as np
m = np.array([[1,2,3],[4,5,6],[7,8,9]])
c = np.array([2,1,2])
z = m / c

print(z)

z = m * c[:, np.newaxis]
print(z)