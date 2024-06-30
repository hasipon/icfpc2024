
import sys
import requests
import time
import glob
import re

print("start")
tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"

def convint(n):
	r = ""
	while n > 0:
		r = chr(n % 94 + 33) + r
		n //= 94
	return r

for i in range(1, 22):
    header = "solve lambdaman" + str(i) + " "
    min = ""
    min_file = ""
    min_method = ""
    for file in glob.glob('lambdaman/' + str(i) + '-*.rand'):
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
        rand_start = int(rand_setting[0])
        rand_segment = int(rand_setting[1])
        rand_base_a = int(rand_setting[2])
        rand_base_m = int(rand_setting[3])
        rand_b = int(rand_setting[4])

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

        enc = 0
        for c in reversed(body):
            enc *= max
            enc += c - 1

        if dir_interval == 1:
            multiply = ""
        else:
            multiply = "B* I" + convint(dir_interval)

        msg = '''
B. S{header}
B~ B~ B~ 
    B~ 
        La B~ va va
        Lr Ld Li Lc
            ? B= vd I!
                S
                ? B< vi I{rand_segment}
                    B.
                        BT I{dir_len} BD {multiply} B% vc I{dir_seq_len} S{dir_seq}
                        B~ B~ B~ B~ vr vr vd B- vi I" 
                            B%
                                B+
                                    B* I{rand_base_a} B* B% vd I{max} vc
                                    I{rand_b}
                                I{rand_base_m}
                    B~ B~ B~ B~ vr vr B/ vd I{max} I! vc
    I{data} I! I{rand_start}
'''
        msg = msg.format(
            data = convint(enc),
            header = ''.join(chr(tbl.index(x)+33) for x in header),
            max = convint(max),
            dir_seq = ''.join(chr(tbl.index(x)+33) for x in dir_seq),
            dir_len = convint(dir_len),
            dir_interval = convint(dir_interval),
            dir_seq_len = convint(len(dir_seq)),
            rand_start = convint(rand_start),
            rand_segment = convint(rand_segment),
            rand_base_a = convint(rand_base_a),
            rand_base_m = convint(rand_base_m),
            rand_b = convint(rand_b),
            multiply = multiply,
        )
        msg = re.sub("[\n\r \s]+", " ", msg).strip()
        update(
            msg,
            "ランダム圧縮"
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
