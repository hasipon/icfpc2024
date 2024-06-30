import requests
import time
import glob
import os

tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"


def communicate(msg:str):
    res = requests.post("https://boundvariable.space/communicate",
                        headers={"Authorization": "Bearer 92af6ee1-e632-462c-8baa-0d26799620d6"}, data=msg)
    print(res.ok)
    print(''.join(tbl[ord(x) - 33] for x in res.text[1:]))
    time.sleep(1)


def encode_v1(prob_no:int, moves:str) -> str:
    msg = f'solve lambdaman{prob_no} {moves}'
    return 'S' + ''.join(chr(tbl.index(x) + 33) for x in msg)


def encode_v2(prob_no:int, moves:str) -> str:
    def convint(n:int) -> str:
        r = ""
        while n > 0:
            r = chr(n % 94 + 33) + r
            n //= 94
        return r

    header = "solve lambdaman" + str(prob_no) + " "
    enc = 0
    for c in moves[::-1]:
        enc *= 4
        if c == 'R':
            enc += 0
        elif c == 'D':
            enc += 1
        elif c == 'L':
            enc += 2
        elif c == 'U':
            enc += 3
    data = convint(enc)
    length = convint(len(moves) - 1)
    msg = '''B. S''' + ''.join(chr(tbl.index(x)+33) for x in header) + ''' B$ B$ B$ Lf B$ Lx B$ vx vx Lp Ln B$ B$ vf B$ vp vp vn Lr Ld Ln B. B$ Lm ? B= vm I! SL ? B= vm I" S> ? B= vm I# SF SO B% vd I% ? B> vn I! B$ B$ vr B/ vd I% B- vn I" S I''' + data + " I" + length
    return msg


def main():
    for prob_no in range(1, 22):
        for file in glob.glob('lambdaman/' + str(prob_no) + '-*.txt'):
            with open(file) as f:
                line = f.readline()
            moves = line.strip()
            if not moves:
                continue

            icfp_file = file[:-3] + "icfp"
            best_size = 1 << 30
            if os.path.isfile(icfp_file):
                with open(icfp_file) as f:
                    best_size = len(f.readline())

            v1 = encode_v1(prob_no, moves)
            if len(v1) < best_size:
                bset_size = len(v1)
                with open(icfp_file, "w") as f:
                    f.write(v1)

            v2 = encode_v2(prob_no, moves)
            if len(v2) < best_size:
                bset_size = len(v2)
                with open(icfp_file, "w") as f:
                    f.write(v2)


if __name__ == '__main__':
    main()