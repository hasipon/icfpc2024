import sys
sys.set_int_max_str_digits(1000000)

tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"

a = sys.stdin.readline().rstrip('\n').split(' ')

def to_int(s):
	r = 0
	for c in s:
		r *= 94
		r += ord(c) - 33
	return r

def to_str(s):
	return ''.join(tbl[ord(x)-33] for x in s)

prog = []

def g(t):
	if t[0] == '|':
		return g(t[1]) + g(t[2])
	if t[0] == 'v':
		return [int(t[1:])]
	if t[0] == '(':
		assert t[:3] == '(!v'
		assert t[-1:] == ')'
		return [-int(t[3:-1])]

def func(t):
	if t[0] == '&':
		func(t[1])
		func(t[2])
	elif t[0] == '|':
		print(g(t[1]) + g(t[2]))
	else:
		print(g(t))

class Parser:
	def __init__(self, a):
		self.a = a
		self.pos = 0

	def main(self):
		if self.a[self.pos][0] == 'B':
			op = self.a[self.pos][1:]
			self.pos += 1
			v1 = self.main()
			v2 = self.main()
			if op == '$':
				return (v1, v2)
			if isinstance(v1, str) and isinstance(v2, str) and op:
				pass#return f'({v1}{op}{v2})'
			return (op, v1, v2)
		elif self.a[self.pos][0] == 'U':
			op = self.a[self.pos][1:]
			self.pos += 1
			v1 = self.main()
			if isinstance(v1, str) and op:
				return f'({op}{v1})'
			return (op, v1)
		elif self.a[self.pos][0] == 'L':
			idx = to_int(self.a[self.pos][1:])
			self.pos += 1
			v = self.main()
			return (f'λv{idx}.', v)
		elif self.a[self.pos][0] == 'v':
			idx = to_int(self.a[self.pos][1:])
			r = f'v{to_int(self.a[self.pos][1:])}'
			self.pos += 1
			return f'v{idx}'
		elif self.a[self.pos][0] == 'I':
			r = to_int(self.a[self.pos][1:])
			self.pos += 1
			return f'{r}'
		elif self.a[self.pos][0] == 'S':
			r = to_str(self.a[self.pos][1:])
			self.pos += 1
			return f'"{r}"'
		elif self.a[self.pos] == '?':
			self.pos += 1
			f = self.main()
			v1 = self.main()
			v2 = self.main()
			func(f)
			return ("if", f, v1, v2)
		else:
			print('>>>', self.a[self.pos])

prog = Parser(a).main()

def print_prog(bb, d):
	if isinstance(bb, str):
		print(' '*d, bb)
	else:
		print_prog(bb[0], d)
		for x in bb[1:]:
			print_prog(x, d+1)


#print_prog(prog, 0)
