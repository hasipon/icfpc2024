import requests
import time
import glob
import os

tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"


def communicate(msg:str):
    res = requests.post("https://boundvariable.space/communicate",
                        headers={"Authorization": "Bearer 92af6ee1-e632-462c-8baa-0d26799620d6"}, data=msg)
    print(res.ok)
    time.sleep(3)
    return ''.join(tbl[ord(x) - 33] for x in res.text[1:])


def main():
    for prob_no in range(1, 22):
        for icfp_file in glob.glob('lambdaman/' + str(prob_no) + '-*.icfp'):
            with open(icfp_file) as f:
                line = f.readline()
            icfp_msg = line.strip()
            if not icfp_msg:
                continue

            txt_file = icfp_file[:-4] + "txt"
            if os.path.isfile(txt_file):
                continue

            a = ''.join(chr(tbl.index(x) + 33) for x in f"solve lambdaman{prob_no}")
            b = ''.join(chr(tbl.index(x) + 33) for x in f"echo")

            assert a in icfp_msg, f"{a} not found in {icfp_file}"
            echo_msg = icfp_msg.replace(a, b)
            moves = communicate(echo_msg).splitlines()[0]
            print("saving", txt_file, moves)
            with open(txt_file, "w") as f:
                f.write(moves)


if __name__ == '__main__':
    main()
