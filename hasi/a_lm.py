import sys
import requests
tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"

def convint(n):
	r = ""
	while n > 0:
		r = chr(n % 94 + 33) + r
		n //= 94
	return r

msg = sys.stdin.readline().rstrip('\n')
x, y, z = msg.split(' ')
msg1 = 'S' + ''.join(chr(tbl.index(x)+33) for x in f'{x} {y} ')
prog = 'B$ B$ L" B$ L# B$ v" B$ v# v# L# B$ v" B$ v# v# LA LB ? B= B% vB I& I! S ? B= B% vB I& I" B. SF B$ vA B/ vB I& ? B= B% vB I& I# B. SL B$ vA B/ vB I& ? B= B% vB I& I$ B. SO B$ vA B/ vB I& B. S> B$ vA B/ vB I&'
enc = 0
for c in z[::-1]:
	enc *= 5
	if c == 'L':
		enc += 1
	elif c == 'R':
		enc += 2
	elif c == 'U':
		enc += 3
	elif c == 'D':
		enc += 4
msg = f'B. {msg1} {prog} I{convint(enc)}'
print(msg)
res = requests.post("https://boundvariable.space/communicate", headers={"Authorization":"Bearer 92af6ee1-e632-462c-8baa-0d26799620d6"}, data=msg)
assert res.ok
print(res.text)
print(''.join(tbl[ord(x)-33] for x in res.text[1:]))
