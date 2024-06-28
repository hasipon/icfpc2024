import sys

import gradio as gr
import requests


def encode(plain_text):
    tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"
    msg = plain_text.rstrip('\n')
    msg = 'S' + ''.join(chr(tbl.index(x) + 33) for x in msg)
    return msg


def decode(encrypted_text):
    tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"
    msg = encrypted_text.rstrip('\n')
    msg = ''.join(tbl[ord(x) - 33] for x in msg[1:])
    return msg


def submit(plain_text):
    encrypted_text = encode(plain_text)
    print(encrypted_text)
    res = requests.post("https://boundvariable.space/communicate",
                        headers={"Authorization": "Bearer 92af6ee1-e632-462c-8baa-0d26799620d6"}, data=encrypted_text)
    return decode(res.text)


encode_ui = gr.Interface(
    fn=encode,
    inputs=["text"],
    outputs=["text"],
)
decode_ui = gr.Interface(
    fn=decode,
    inputs=["text"],
    outputs=["text"],
)
submit_ui = gr.Interface(
    fn=submit,
    inputs=["text"],
    outputs=["text"],
)

gr.TabbedInterface(
    [encode_ui, decode_ui, submit_ui], ["encode", "decode", "submit"]
).launch(server_port=8080, server_name='0.0.0.0')
