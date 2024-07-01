
import sys
import requests
import time
import glob
import re
import math

print("start")
tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"

def convint(n):
	r = ""
	while n > 0:
		r = chr(n % 94 + 33) + r
		n //= 94
	return r

for i in range(11, 20):
    header = "solve lambdaman" + str(i) + " "
    min = ""
    min_file = ""
    min_method = ""
    for file in glob.glob('lambdaman/' + str(i) + '-*.rand2'):
        f = open(file, "r")
        dir_setting = f.readline().replace("\n", "").replace("\r", "").split()
        rand_setting = f.readline().replace("\n", "").replace("\r", "").split()
        body = []
        for line in f:
            body.append(int(line))
        f.close()
        
        dir_seq = dir_setting[0]
        dir_len = int(dir_setting[1])
        dir_interval = int(dir_setting[2])
        rand_segment = int(rand_setting[0])
        rand_mod = int(rand_setting[1])
        rand_offset = int(rand_setting[2])

        def update(msg, method):            
            global min
            global min_file
            global min_method
            if min == "" or len(msg) < len(min):
                min = msg
                min_method = method
                min_file = file

        max = 0
        for c in body:
            if c > max:
                max = c
        max += 1

        enc = 0
        if body[len(body) - 1] == 0:
            enc = 1
        for c in reversed(body):
            enc *= max
            enc += c
             

        if dir_interval == 1:
            multiply = ""
        else:
            multiply = "B* I" + convint(dir_interval)

        msg = '''
B. S{header}
B~ B~ 
    B~ 
        La B~ va va
        Lr Ld Li
            ? B= vd I!
                S
                    B.
                        BT I{dir_len} BD {multiply} B% B/ B* vi B% B* vi vi I{rand_mod} B+ B% vd I{max} I{rand_offset} I{dir_seq_len} S{dir_seq}
                        B~ B~ B~ vr vr 
                            ? B= B% vi I{rand_segment} I!
                                B/ vd I{max}
                                vd
                            B+ vi I"
    I{data} I"
'''
        msg = msg.format(
            data = convint(enc),
            header = ''.join(chr(tbl.index(x)+33) for x in header),
            max = convint(max),
            dir_seq = ''.join(chr(tbl.index(x)+33) for x in dir_seq),
            dir_len = convint(dir_len),
            dir_interval = convint(dir_interval),
            dir_seq_len = convint(math.floor((len(dir_seq) - dir_len) / dir_interval) + 1),
            rand_segment = convint(rand_segment),
            rand_mod = convint(rand_mod),
            rand_offset = convint(rand_offset),
            multiply = multiply,
        )
        msg = re.sub("[\n\r \s]+", " ", msg).strip()
        update(
            msg,
            "平方さいちゅう圧縮"
        )

    if min != "":
        print(min_file)
        print(min_method)
        print(min)
        res = requests.post("https://boundvariable.space/communicate", headers={"Authorization":"Bearer 92af6ee1-e632-462c-8baa-0d26799620d6"}, data=min)
        assert res.ok
        print(res.text)
        result = ''.join(tbl[ord(x)-33] for x in res.text[1:])
        print(result)
        time.sleep(3)
