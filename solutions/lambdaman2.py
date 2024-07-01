
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


header = "solve lambdaman10 "
txt = '''B. S{header} B$ Lz B. B$ B$ B$ vz I$9]Lx ImS IYL B$ B$ B$ vz I%FaUY ILd Itr7O Ls Lm Lf B$ B$ Ly B$ vy vy Lr Lx ? B= vx vf S B. BT I" BD B% vx I% SL>OF B$ B$ vr vr B% B* vx vm I-jqaj vs'''
msg = txt.format(
	header = ''.join(chr(tbl.index(x)+33) for x in header)
)



print(msg)
res = requests.post("https://boundvariable.space/communicate", headers={"Authorization":"Bearer 92af6ee1-e632-462c-8baa-0d26799620d6"}, data=msg)
assert res.ok
result = ''.join(tbl[ord(x)-33] for x in res.text[1:])
print("\n" + result)
time.sleep(3)

for i in range(1, 21+1):
    header = "solve lambdaman" + str(i) + " "
    msg = txt.format(
        header = ''.join(chr(tbl.index(x)+33) for x in header)
    )

    print(msg)
    res = requests.post("https://boundvariable.space/communicate", headers={"Authorization":"Bearer 92af6ee1-e632-462c-8baa-0d26799620d6"}, data=msg)
    assert res.ok
    result = ''.join(tbl[ord(x)-33] for x in res.text[1:])
    print(str(i) + "\n" + result)
    time.sleep(3)
