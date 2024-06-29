import sys
import requests
tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"
msg = 'B. S3/,6%},!-"$!-!.[} B$ L" B$ v" B$ v" B$ v" SLLLLLLLLLLLLLLLLLLLLLLLLL L" B. v" v"'
print(msg)
res = requests.post("https://boundvariable.space/communicate", headers={"Authorization":"Bearer 92af6ee1-e632-462c-8baa-0d26799620d6"}, data=msg)
assert res.ok
print(res.text)
print(''.join(tbl[ord(x)-33] for x in res.text[1:]))
