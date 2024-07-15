import sys
import requests
tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"
msg = sys.stdin.readline().rstrip('\n')
msg = 'S' + ''.join(chr(tbl.index(x)+33) for x in msg)
print(msg)
res = requests.post("http://localhost:8000/communicate", headers={"Authorization":"Bearer 00000000-0000-0000-0000-000000000000"}, data=msg)
assert res.ok
print(res.text)
print(''.join(tbl[ord(x)-33] for x in res.text[1:]))
