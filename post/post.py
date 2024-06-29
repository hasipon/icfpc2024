import sys
import requests
import time

print("start")
tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"
for letter in tbl:
    msg = '''B. S%#(/} B''' + letter

    print(msg)
    res = requests.post("https://boundvariable.space/communicate", headers={"Authorization":"Bearer 92af6ee1-e632-462c-8baa-0d26799620d6"}, data=msg)
    assert res.ok
    print(res.text)
    result = ''.join(tbl[ord(x)-33] for x in res.text[1:])
    print("response = " + result)
    time.sleep(2.5)

