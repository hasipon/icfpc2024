from math import sin, trunc

def div(x, y):
    v = abs(x) // abs(y)
    if x < 0:
        v = -v
    if y < 0:
        v = -v
    return v

max_n = 0
for A in range(-1570000000, 1571000000, 1000000):
    ans = trunc(sin(A / 1_000_000_000) * 1_000_000_000)

    factor = 1000

    a = A * factor
    b = 1
    v = A * factor

    n = 2
    while True:
        a *= -A * A
        b *= n * (n + 1) * 1_000_000_000**2
        n += 2
        dv = div(a, b)
        if dv == 0:
            break
        v += dv
        # print(n, dv)

    v = div(v, factor)

    if ans-v != 0:
        print(f'A = {A}', ans, v, ans-v)
    max_n = max(max_n, n)

print(max_n)
