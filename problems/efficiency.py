import sys
import requests
import time

print("start")
tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"
for i in range(1, 14):
    msg = "get efficiency" + str(i)
    msg = 'S' + ''.join(chr(tbl.index(x)+33) for x in msg)
    print(msg)
    res = requests.post("https://boundvariable.space/communicate", headers={"Authorization":"Bearer 92af6ee1-e632-462c-8baa-0d26799620d6"}, data=msg)
    assert res.ok
    result = res.text[1:]
    print(str(i) + "\n" + result)
    f = open("efficiency/" + str(i) + ".txt", "w")
    f.write(result)
    f.close()
    time.sleep(3)
