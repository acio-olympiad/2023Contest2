import random

def gen(N, Q, maxa, maxk, callback=print):
    callback(f"{N} {Q}")
    callback(" ".join(str(random.randint(-maxa, maxa)) for _ in range(N)))
    if Q == 1:
        if maxk == 2:
            callback(2)
        else:
            callback(random.randint(1, min(maxk,N)))
    else:
        callback(" ".join(str(i) for i in range(1, Q+1)))

CASES = {
    "sub1": [
        [100, 1, 10, 1]
    ] * 20 + [
        [100000, 1, 10000, 1]
    ] * 5,
    "sub2": [
        [100, 1, 10, 2]
    ] * 20 + [
        [100000, 1, 10000, 2]
    ] * 5,
    "sub3": [
        [100, 1, 10, 50]
    ] * 30 + [
        [100000, 1, 10000, 50]
    ] * 2,
    "sub4": [
        [10000, 1, 100, 10000],
    ] * 10 + [
        [100000, 1, 10000, 100000], 
    ] * 5,
    "sub5": [
        [100000, 100000, 10000, 100000]
    ] * 5
}

for name, c in CASES.items():
    for i, args in enumerate(c):
        fullname = f"{name}-{i}.in"
        with open(fullname, "w") as f:
            def callback(*args):
                f.write(" ".join([str(a) for a in args]) + "\n")
            gen(*args, callback=callback)
        print("Wrote", fullname)
