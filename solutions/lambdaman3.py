
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

header = "echo "
txt = '''
    B. S{header}
    B~
        B~
            B~ La B~ va va
			Lr Li Lj
                ? B> vi I!
				    B. 
					    B$ B$ B$ vr
						    vr 
							B- vi I"
							B% 
							    B+ 
                                    B+ 
                                        vj
										B* 
                                            B%
                                                B% 
                                                    B/
                                                        B* vi vi 
                                                        I9 
                                                    IG
                                                I#
											I#
									I"
								I%
					    BT I' BD B* vj I' SLLLLLL>>>>>>FFFFFFOOOOO
					S
	    I)~~
		I!
'''

txt = re.sub("[\n\r \s]+", " ", txt).strip()
msg = txt.format(
	header = ''.join(chr(tbl.index(x)+33) for x in header)
)

res = requests.post("https://boundvariable.space/communicate", headers={"Authorization":"Bearer 92af6ee1-e632-462c-8baa-0d26799620d6"}, data=msg)
assert res.ok
print("\n\n" + res.text)
result = ''.join(tbl[ord(x)-33] for x in res.text[1:])
print(result)
f = open("result.txt", "w")
line = f.write(result)
f.close()
time.sleep(3)

for i in range(10, 11):
    header = "solve lambdaman" + str(i) + " "
    msg = txt.format(
        header = ''.join(chr(tbl.index(x)+33) for x in header)
    )
	
    print(len(msg))
    print(msg)
	
    res = requests.post("https://boundvariable.space/communicate", headers={"Authorization":"Bearer 92af6ee1-e632-462c-8baa-0d26799620d6"}, data=msg)
    assert res.ok
    result = ''.join(tbl[ord(x)-33] for x in res.text[1:])
    print("\n" + res.text)
    result = ''.join(tbl[ord(x)-33] for x in res.text[1:])
    print(result)
    time.sleep(3)
