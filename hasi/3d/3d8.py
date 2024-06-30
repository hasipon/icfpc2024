def solve(a):
    x = 2
    while True:
        c = a
        s = 0
        while True:
            if c == 0:
                if s == a:
                    return x
                break
            else:
                c, r = divmod(c, x)
                s = s * x + r
        x += 1


def main():
    for a in range(2, 21):
        print(f'A = {a} :', solve(a))
    for a in [3123, 1233321]:
        print(f'A = {a} :', solve(a))


main()
