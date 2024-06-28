tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"

with open('c.txt') as f:
	a = f.read().rstrip('\n').split(' ')

def to_int(s):
	r = 0
	for c in s:
		r *= 94
		r += ord(c) - 33
	return r

def to_str(s):
	return ''.join(tbl[ord(x)-33] for x in s)

for x in a:
	if x == '?':
		print('if')
	elif x == 'T':
		print('true')
	elif x == 'F':
		print('false')
	elif x == 'U-':
		print('neg')
	elif x == 'U!':
		print('not')
	elif x == 'U#':
		print('atoi')
	elif x == 'U$':
		print('itoa')
	elif x[0] == 'B':
		print('app', x[1:])
	elif x[0] == 'L':
		print('abs', to_int(x[1:]))
	elif x[0] == 'v':
		print('var', to_int(x[1:]))
	elif x[0] == 'I':
		print(to_int(x[1:]))
	elif x[0] == 'S':
		print('"'+to_str(x[1:])+'"')
	else:
		print('>>', x)

def icfp_atoi(n):
	r = ""
	while n > 0:
		r = tbl[n % 94] + r
		n //= 94
	return r

# 311 * 124753942619 + 2
# = 38798476154511
print(icfp_atoi(15818151))
print(icfp_atoi(38798476154511))
