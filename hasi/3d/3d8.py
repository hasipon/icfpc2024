def solve(a):
    x = 2
    c = a
    s = 0
    while True:
        if c == 0:
            if s == a:
                return x
            x += 1
            s = 0
            c = a
        else:
            s = s * x + c % x
            c //= x


def main():
    for a in range(2, 21):
        print(f'A = {a} :', solve(a))
    for a in [3123, 1233321]:
        print(f'A = {a} :', solve(a))


main()
