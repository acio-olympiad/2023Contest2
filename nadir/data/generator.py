import numpy as np

rng = np.random.default_rng(54973221)

def gen_queries(N, Q):
    if Q == 1:
        return np.array([N])
    return np.sort(rng.choice(np.arange(1, N+1), size=Q, replace=False))

def gen_cartesian(N):
    if N == 0:
        return np.array([])
    if N == 1:
        return np.array([1])
    split = rng.integers(1, N+1)
    left = gen_cartesian(split-1)
    right = gen_cartesian(N-split)
    assert len(left) + len(right) > 0

    inner_max = np.concatenate([left, right]).max()
    middle = np.array([inner_max + 1])

    return np.concatenate([left, middle, right])

def gen_purerandom(N, maxa):
    return rng.integers(1, maxa, size=N)

def gen_wavy(N, freqs, amps, phases):
    freqs = np.array(freqs)
    amps = np.array(amps)
    phases = np.array(phases)
    x = np.arange(N)
    waves = amps[:, np.newaxis] * np.sin(2*np.pi * ((1/N) * freqs[:, np.newaxis] * x[np.newaxis, :] + phases[:, np.newaxis]))
    res = waves.sum(axis=0)
    return (res - res.min()).round()

CASES = {
    "sub1": [
        [gen_cartesian, 99996, 1, []],
        [gen_cartesian, 99996, 1, []],
        [gen_wavy, 99996, 1, [[1], [1e8], [0.25]]],
        [gen_wavy, 99996, 1, [[1, 10], [1e8, 5e7], [0.25, 0]]],
        [gen_wavy, 99996, 1, [[1, 10], [1e8, 1e7], [0.25, 0]]],
        [gen_wavy, 99996, 1, [[1, 10, 100], [2e8, 1e7, 2e6], [0, 0, 0]]],
        [gen_wavy, 99996, 1, [[1, 10, 100], [2e8, 1e7, 2e6], [0.25, 0, 0]]],
        [gen_wavy, 99996, 1, [[1, 10, 100], [2e8, 1e7, 2e6], [0.5, 0, 0]]],
        [gen_wavy, 99996, 1, [[1, 10, 100], [2e8, 1e7, 2e6], [0.75, 0, 0]]],
        [gen_wavy, 99996, 1, [[1, 10, 100, 1000], [1e8, 1e7, 1e6, 2e5], [0.25, 0, 0, 0]]],
        [gen_purerandom, 99996, 1, [1e9]],
        [gen_purerandom, 99996, 1, [1e9]],
        [gen_purerandom, 99996, 1, [1e9]],
        [gen_purerandom, 99996, 1, [1e9]],
        [gen_purerandom, 99996, 1, [1e9]],
        [gen_cartesian, 100000, 1, []],
    ],
    "sub2": [
        [gen_purerandom, 99996, 90000, [10]],
        [gen_purerandom, 99996, 90000, [10]],
        [gen_purerandom, 99996, 90000, [10]],
        [gen_purerandom, 99996, 90000, [10]],
        [gen_purerandom, 99996, 90000, [10]],
        [gen_purerandom, 99996, 90000, [10]],
        [gen_purerandom, 99996, 90000, [10]],
        [gen_purerandom, 99996, 90000, [10]],
        [gen_purerandom, 100000, 100000, [10]],
    ],
    "sub3": [
        [gen_cartesian, 99996, 90000, []],
        [gen_cartesian, 99996, 90000, []],
        [gen_wavy, 99996, 90000, [[1], [1e8], [0.25]]],
        [gen_wavy, 99996, 90000, [[1, 10], [1e8, 5e7], [0.25, 0]]],
        [gen_wavy, 99996, 90000, [[1, 10], [1e8, 1e7], [0.25, 0]]],
        [gen_wavy, 99996, 99996, [[1, 10, 100], [2e8, 1e7, 2e6], [0, 0, 0]]],
        [gen_wavy, 99996, 99996, [[1, 10, 100], [2e8, 1e7, 2e6], [0.25, 0, 0]]],
        [gen_wavy, 99996, 99996, [[1, 10, 100], [2e8, 1e7, 2e6], [0.5, 0, 0]]],
        [gen_wavy, 99996, 99996, [[1, 10, 100], [2e8, 1e7, 2e6], [0.75, 0, 0]]],
        [gen_wavy, 99996, 99996, [[1, 10, 100, 1000], [1e8, 1e7, 1e6, 2e5], [0.25, 0, 0, 0]]],
        [gen_purerandom, 99996, 90000, [1e9]],
        [gen_purerandom, 99996, 90000, [1e9]],
        [gen_purerandom, 99996, 90000, [1e9]],
        [gen_purerandom, 99996, 90000, [1e9]],
        [gen_purerandom, 99996, 90000, [1e9]],
        [gen_cartesian, 100000, 100000, []],
    ]
}

def write_to_file(f, seq, qu):
    f.write(f"{len(seq)} {len(qu)}\n")
    f.write(" ".join([str(int(x)) for x in seq]) + "\n")
    f.write(" ".join([str(int(x)) for x in qu]) + "\n")

def generate():
    for name, cs in CASES.items():
        for i, (f, N, Q, args) in enumerate(cs):
            fullname = f"{name}-{f.__name__}-{i}.in"
            seq = f(N, *args)
            qu = gen_queries(N, Q)
            assert len(set(qu)) == len(qu)
            with open(fullname, "w") as f:
                write_to_file(f, seq, qu)
            print(f"Wrote {fullname}")

if __name__ == "__main__":
    generate()
