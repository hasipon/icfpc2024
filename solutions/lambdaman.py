
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
    for file in glob.glob('lambdaman/' + str(i) + '-*.txt'):
        f = open(file, "r")
        line = f.readline()
        f.close()
        line = line.replace("\n", "").replace("\r", "")
        
        def update(msg, method):            
            global min
            global min_file
            global min_method
            if min == "" or len(msg) < len(min):
                min = msg
                min_method = method
                min_file = file

        update("S" + ''.join(chr(tbl.index(x)+33) for x in (header + line)), "生データ")
        #1文字モード
        enc = 0
        if line[0] != 'R': 
            data = ['R', 'D', 'L', 'U']
            keys = "L>FO"
        else:
            data = ['D', 'R', 'L', 'U']
            keys = ">LFO"

        for c in line:
            enc *= 4
            enc += data.index(c)
        
        msg = '''B$ B$ La B$ va va Lr Ld ? B> vd I! B. B$ B$ vr vr B/ vd I% BT I" BD B% vd I% S{keys} S{header} I{data}'''
        msg = msg.format(
            data = convint(enc),
            header = ''.join(chr(tbl.index(x)+33) for x in header),
            keys = keys
        )
        update(
            msg,
            "1文字圧縮"
        )
        # 2文字モード    
        if line[0] != 'R': 
            data = ['R', 'D', 'L', 'U']
            keys = "LL>>FFOO"
        else:
            data = ['D', 'R', 'L', 'U']
            keys = ">>LLFFOO"
        
        enc = 0
        i = 0
        valid = True
        for c in line:
            if i  % 2 == 1:
                if prev != c:
                    valid = False
                    break
                enc *= 4
                enc += data.index(c)
            i += 1
            prev = c
                
        if valid:
            data = convint(enc)
            msg = '''B$ B$ La B$ va va Lr Ld ? B> vd I! B. B$ B$ vr vr B/ vd I% BT I# BD B* I# B% vd I% S{keys} S{header} I{data}'''
            msg = msg.format(
                data = convint(enc),
                header = ''.join(chr(tbl.index(x)+33) for x in header),
                keys = keys
            )
            update(
                msg,
                "2文字圧縮"
            )
            print("2文字圧縮" + str(max) + ":" + str(len(msg)))

        # 8文字モード    
        if line[0] != 'R': 
            data = ['R', 'D', 'L', 'U']
            keys = "LLLLLLLL>>>>>>>>FFFFFFFFOOOOOOOO"
        else:
            data = ['D', 'R', 'L', 'U']
            keys = ">>>>>>>>LLLLLLLLFFFFFFFFOOOOOOOO"
        
        enc = 0
        i = 0
        valid = True
        for c in line:
            if i  % 2 == 1:
                if prev != c:
                    valid = False
                    break
                enc *= 4
                enc += data.index(c)
            i += 1
            prev = c

        #ランレングス圧縮
        if valid:
            for max in [2, 3, 4, 5]:
                enc = 0
                if line[0] != 'R': 
                    data = ['R', 'D', 'L', 'U']
                    target = ['L', '>', 'F', 'O']

                else:
                    data = ['D', 'R', 'L', 'U']
                    target = ['>', 'L', 'F', 'O']

                keys = ""
                for c in target:
                    for _ in range(0, max):
                        keys += c + c

                rank = 2 ** (max - 1)
                i = 0
                while i < len(line):
                    repeat = 0
                    c = line[i]
                    i += 2
                    for _ in range(0, max - 1):
                        if i < len(line) and c == line[i]:
                            repeat += 1
                            i += 2
                        else:
                            break

                    enc *= 4 * rank
                    enc += data.index(c) + repeat * 4

                msg = '''B$ B$ La B$ va va Lr Ld ? B> vd I! B. B$ B$ vr vr B/ vd I{mod_full} BT B+ B* I# B% B/ vd I% I{mod_len} I" BD B* B% vd I% I{len} S{keys} S{header} I{data}'''
                msg = msg.format(
                    header = ''.join(chr(tbl.index(x)+33) for x in header),
                    mod_full = convint(4 * rank),
                    mod_len = convint(rank),
                    len = convint(max) * 2,
                    data = convint(enc),
                    keys = keys
                )
                update(
                    msg,
                    "2文字ランレングス圧縮" + str(max)
                )
                print("2文字ランレングス圧縮" + str(max) + ":" + str(len(msg)))
        else:
            for max in [2, 3, 4, 5]:
                enc = 0
                if line[0] != 'R': 
                    data = ['R', 'D', 'L', 'U']
                    target = ['L', '>', 'F', 'O']

                else:
                    data = ['D', 'R', 'L', 'U']
                    target = ['>', 'L', 'F', 'O']

                keys = ""
                for c in target:
                    for _ in range(0, max):
                        keys += c

                rank = 2 ** (max - 1)
                i = 0
                while i < len(line):
                    repeat = 0
                    c = line[i]
                    i += 1
                    for _ in range(0, max - 1):
                        if i < len(line) and c == line[i]:
                            repeat += 1
                            i += 1
                        else:
                            break

                    enc *= 4 * rank
                    enc += data.index(c) + repeat * 4

                msg = '''B$ B$ La B$ va va Lr Ld ? B> vd I! B. B$ B$ vr vr B/ vd I{mod_full} BT B+ B% B/ vd I% I{mod_len} I" BD B* B% vd I% I{len} S{keys} S{header} I{data}'''
                msg = msg.format(
                    header = ''.join(chr(tbl.index(x)+33) for x in header),
                    mod_full = convint(4 * rank),
                    mod_len = convint(rank),
                    len = convint(max),
                    data = convint(enc),
                    keys = keys
                )
                update(
                    msg,
                    "ランレングス圧縮" + str(max)
                )
                print("ランレングス圧縮" + str(max) + ":" + str(len(msg)))


    print(min_file)
    print(min_method)
    print(min)
    res = requests.post("https://boundvariable.space/communicate", headers={"Authorization":"Bearer 92af6ee1-e632-462c-8baa-0d26799620d6"}, data=min)
    assert res.ok
    result = ''.join(tbl[ord(x)-33] for x in res.text[1:])
    print(result)
    time.sleep(3)
