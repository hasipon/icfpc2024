import sys
from collections import defaultdict


def div(x, y):
    v = abs(x) // abs(y)
    if x < 0:
        v = -v
    if y < 0:
        v = -v
    return v


def mod(x, y):
    return x - y * div(x, y)


class Main:
    def __init__(self):
        data = [line.rstrip().split() for line in sys.stdin.readlines()]
        a_value = int(data[0][0])
        b_value = int(data[0][1])
        data = data[1:]

        field = {}
        for i, a in enumerate(data):
            for j, x in enumerate(a):
                try:
                    if x in {'.', '<', '>', '^', 'v', '+', '-', '*', '/', '%', '@', '=', '#', 'S', 'A', 'B'}:
                        if x == 'A':
                            field[i, j] = a_value
                        elif x == 'B':
                            field[i, j] = b_value
                        elif x != '.':
                            field[i, j] = x
                    else:
                        n = int(x)
                        assert -99 <= n <= 99
                        field[i, j] = n
                except:
                    print(f'error token {repr(x)}')
                    raise

        self.history = [field]
        self.print_field()

    def print_field(self):
        print(f'[t = {len(self.history)}]')
        f = self.history[-1]
        min_i = min(i for i, j in f)
        max_i = max(i for i, j in f)
        min_j = min(j for i, j in f)
        max_j = max(j for i, j in f)
        for i in range(min_i, max_i + 1):
            for j in range(min_j, max_j + 1):
                print(f.get((i, j), '.'), end=' ')
            print()
        print()

    def reduction(self):
        f = self.history[-1]
        update = defaultdict(list)
        warp = []
        for pos, cmd in f.items():
            i, j = pos
            if cmd == '<':
                if (i, j + 1) in f:
                    update[i, j + 1].append(None)
                    update[i, j - 1].append(f[i, j + 1])
            elif cmd == '>':
                if (i, j - 1) in f:
                    update[i, j - 1].append(None)
                    update[i, j + 1].append(f[i, j - 1])
            elif cmd == '^':
                if (i + 1, j) in f:
                    update[i + 1, j].append(None)
                    update[i - 1, j].append(f[i + 1, j])
            elif cmd == 'v':
                if (i - 1, j) in f:
                    update[i - 1, j].append(None)
                    update[i + 1, j].append(f[i - 1, j])
            elif cmd == '+':
                if isinstance(f.get((i, j - 1)), int) and isinstance(f.get((i - 1, j)), int):
                    update[i, j - 1].append(None)
                    update[i - 1, j].append(None)
                    v = f[i, j - 1] + f[i - 1, j]
                    update[i + 1, j].append(v)
                    update[i, j + 1].append(v)
            elif cmd == '-':
                if isinstance(f.get((i, j - 1)), int) and isinstance(f.get((i - 1, j)), int):
                    update[i, j - 1].append(None)
                    update[i - 1, j].append(None)
                    v = f[i, j - 1] - f[i - 1, j]
                    update[i + 1, j].append(v)
                    update[i, j + 1].append(v)
            elif cmd == '*':
                if isinstance(f.get((i, j - 1)), int) and isinstance(f.get((i - 1, j)), int):
                    update[i, j - 1].append(None)
                    update[i - 1, j].append(None)
                    v = f[i, j - 1] * f[i - 1, j]
                    update[i + 1, j].append(v)
                    update[i, j + 1].append(v)
            elif cmd == '/':
                if isinstance(f.get((i, j - 1)), int) and isinstance(f.get((i - 1, j)), int):
                    if f[i - 1, j] == 0:
                        continue
                    update[i, j - 1].append(None)
                    update[i - 1, j].append(None)
                    v = div(f[i, j - 1], f[i - 1, j])
                    update[i + 1, j].append(v)
                    update[i, j + 1].append(v)
            elif cmd == '%':
                if isinstance(f.get((i, j - 1)), int) and isinstance(f.get((i - 1, j)), int):
                    if f[i - 1, j] == 0:
                        continue
                    update[i, j - 1].append(None)
                    update[i - 1, j].append(None)
                    v = mod(f[i, j - 1], f[i - 1, j])
                    update[i + 1, j].append(v)
                    update[i, j + 1].append(v)
            elif cmd == '@':
                if (i - 1, j) in f:
                    dx = f.get((i, j - 1))
                    dy = f.get((i, j + 1))
                    dt = f.get((i + 1, j))
                    assert isinstance(dx, int) and isinstance(dy, int) and isinstance(dt, int)
                    assert dt > 0
                    warp.append((i - dy, j - dx, dt, f[i - 1, j]))
            elif cmd == '=':
                if (i, j - 1) in f and (i - 1, j) in f and f[i - 1, j] == f[i, j - 1]:
                    update[i, j - 1].append(None)
                    update[i - 1, j].append(None)
                    update[i + 1, j].append(f[i, j - 1])
                    update[i, j + 1].append(f[i - 1, j])
            elif cmd == '#':
                if (i, j - 1) in f and (i - 1, j) in f and f[i - 1, j] != f[i, j - 1]:
                    update[i, j - 1].append(None)
                    update[i - 1, j].append(None)
                    update[i + 1, j].append(f[i, j - 1])
                    update[i, j + 1].append(f[i - 1, j])

        new_f = f.copy()
        submitted = []
        for pos, values in update.items():
            d = False
            v = None
            for x in values:
                if x is None:
                    d = True
                else:
                    if v is not None:
                        raise Exception(f'conflict {pos} {v} {x}')
                    v = x
            if v is not None:
                if new_f.get(pos) == 'S':
                    submitted.append(v)
                new_f[pos] = v
            elif d:
                del new_f[pos]

        if len(submitted) >= 2:
            raise Exception(f'multiple submissions {submitted}')

        if len(submitted) == 1:
            print('result =', submitted[0])
            return True

        if warp:
            dts = {x[2] for x in warp}
            if len(dts) != 1:
                raise Exception(f'multiple dts {dts}')
            dt = dts.pop()
            if dt >= len(self.history):
                raise Exception(f'invalid dt {dt} {len(self.history)}')
            self.history = self.history[:-dt]
            for i, j, _, v in warp:
                self.history[-1][i, j] = v
        else:
            self.history.append(new_f)

        self.print_field()
        return False


m = Main()
for _ in range(10000):
    if m.reduction():
        break
