import sys
import requests
import time
import glob
print("start")
tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"

def convint(n):
	r = ""
	while n > 0:
		r = chr(n % 94 + 33) + r
		n //= 94
	return r

for i in range(1, 22):
    min = ""
    
    for file in glob.glob('lambdaman/' + str(i) + '-*.txt'):
        f = open(file, "r")
        line = f.readline()
        f.close()
        if min == "" or len(line) < len(min):
            min = line
            min_file = file

    print(min_file)
    line = min
    header = "solve lambdaman" + str(i) + " "
    enc = 0
    for c in line[::-1]:
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
    length = convint(len(line) - 1)
    msg = '''B. S''' + ''.join(chr(tbl.index(x)+33) for x in header) + ''' B$ B$ B$ Lf B$ Lx B$ vx vx Lp Ln B$ B$ vf B$ vp vp vn Lr Ld Ln B. B$ Lm ? B= vm I! SL ? B= vm I" S> ? B= vm I# SF SO B% vd I% ? B> vn I! B$ B$ vr B/ vd I% B- vn I" S I''' + data + " I" + length

    print(msg)
    res = requests.post("https://boundvariable.space/communicate", headers={"Authorization":"Bearer 92af6ee1-e632-462c-8baa-0d26799620d6"}, data=msg)
    assert res.ok
    result = ''.join(tbl[ord(x)-33] for x in res.text[1:])
    print(str(i) + "\n" + result)
    time.sleep(3)
