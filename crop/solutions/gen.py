import random

N = 10000
Q = 1
print(N, Q)
print(" ".join(str(random.randint(-9, 9)) for _ in range(N)))
if Q == 1:
    print(random.randint(1, min(50,N)))
else:
    print(" ".join(str(i) for i in range(1, Q+1)))

