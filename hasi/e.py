import sys
import requests
tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"
msg = sys.stdin.readline().rstrip('\n')
print('S' + ''.join(chr(tbl.index(x)+33) for x in msg))
