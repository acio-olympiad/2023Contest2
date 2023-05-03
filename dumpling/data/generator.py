import numpy as np

def bursts(M):
    lofreq = np.arange(M) % 8 == 0
    hifreq = np.arange(M) % 4 == 0
    switch = np.arange(M) % 800 < 400
    return np.where(switch, lofreq, hifreq).astype(int)

def smoothchange(M):
    x = np.arange(M+1)
    amp = np.diff(np.round(1/4 * x + 400/(80*np.pi) *np.sin(2*np.pi/400*x)))
    return amp

def sawtoothbowlsize(M, B):
    x = np.arange(M+1)
    tot = np.clip(np.round(400/np.pi*np.arcsin(np.sin(np.pi/1600 * x))) + B, 5, 20)
    assert tot[0] == B
    amp = np.diff(tot)
    return amp

def zeros(M, B):
    return np.zeros(M)

CASES = {
    "sub1": [
        [1000, 1, 100000, 1, 5, bursts, zeros],
        [1000, 1, 100000, 1, 20, smoothchange, zeros],
    ],
    "sub2": [
        [1000, 20, 100000, 2, 5, bursts, zeros],
        [1000, 20, 100000, 2, 20, smoothchange, zeros],
        [1000, 50, 100000, 2, 10, bursts, zeros],
        [1000, 50, 100000, 2, 10, smoothchange, zeros],
    ],
    "sub3": [
        [1000, 20, 100000, 3, 5, bursts, zeros],
        [1000, 20, 100000, 3, 20, smoothchange, zeros],
        [1000, 20, 100000, 3, 10, bursts, sawtoothbowlsize],
        [1000, 20, 100000, 3, 6, smoothchange, sawtoothbowlsize],
        [1000, 50, 100000, 3, 15, bursts, zeros],
        [1000, 50, 100000, 3, 20, smoothchange, zeros],
        [1000, 50, 100000, 3, 14, bursts, sawtoothbowlsize],
        [1000, 50, 100000, 3, 8, smoothchange, sawtoothbowlsize],
    ],
}

def do_case(N, K, M, S, B, agen, bgen, callback=print, name="test.in"):
    a = agen(M).astype(int)
    b = bgen(M, B).astype(int)
    assert ((0 <= a) & (a <= 1)).all()
    assert ((-1 <= b) & (b <= 1)).all()
    assert len(a) == M == len(b)

    callback(N, K, M, S, B)
    for x, y in zip(a, b):
        callback(x, y)
    
for n, c in CASES.items():
    for i, args in enumerate(c):
        fn = f"{n}-{i}-{args[-2].__name__}-{args[-1].__name__}.in"
        with open(fn, "w") as f:
            def callback(*args):
                f.write(" ".join([str(a) for a in args]) + "\n")
            do_case(*args, name=fn, callback=callback)
        print(f"Written {fn}")
