import sys
import requests

print("start")
tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"
msg = '''B. S%#(/} B$ B$ B$ Lf B$ Lp Ln B$ B$ vf B$ vp vp vn Lp Ln B$ B$ vf B$ vp vp vn Lr Ld Ln B. ? B= B% vd I% I! SL ? B= B% vd I% I" S> ? B= B% vd I% I# SF SO ? B> vn I! B$ B$ vr B/ vd I% B- vn I" S I* I#*'''

print(msg)
res = requests.post("https://boundvariable.space/communicate", headers={"Authorization":"Bearer 92af6ee1-e632-462c-8baa-0d26799620d6"}, data=msg)
assert res.ok
print(res.text)
result = ''.join(tbl[ord(x)-33] for x in res.text[1:])
print("response = " + result)


 