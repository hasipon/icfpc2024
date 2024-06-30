
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

for i in range(16, 17):
    header = "solve lambdaman" + str(i) + " "
    min = ""
    min_file = ""
    min_method = ""
    for file in glob.glob('lambdaman/' + str(i) + '-*.hand'):
        f = open(file, "r")
        problem_size = f.readline().replace("\n", "").replace("\r", "")
        step_size = f.readline().replace("\n", "").replace("\r", "")
        body = f.readline().replace("\n", "").replace("\r", "")
        f.close()
        
        def update(msg, method):            
            global min
            global min_file
            global min_method
            if min == "" or len(msg) < len(min):
                min = msg
                min_method = method
                min_file = file

        #等分圧縮モード
        enc = 0
        data = ['R', 'D', 'L', 'U']
        keys = "L>FO"

        for c in body:
            enc *= 8
            if c in data:
                enc += data.index(c) * 2
            else:
                enc += data.index(c.upper()) * 2 + 1

        msg = ''''''
        msg = msg.format(
            data = convint(enc),
            header = ''.join(chr(tbl.index(x)+33) for x in header),
            keys = keys
        )
        update(
            msg,
            "対等圧縮"
        )

    print(min_file)
    print(min_method)
    print(min)
    res = requests.post("https://boundvariable.space/communicate", headers={"Authorization":"Bearer 92af6ee1-e632-462c-8baa-0d26799620d6"}, data=min)
    assert res.ok
    result = ''.join(tbl[ord(x)-33] for x in res.text[1:])
    print(result)
    time.sleep(3)
