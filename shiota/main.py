import sys

import gradio as gr


def encode(plain_text):
    tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"
    msg = plain_text
    msg = 'S' + ''.join(chr(tbl.index(x) + 33) for x in msg)
    return msg


def decode(encrypted_text):
    tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n"
    msg = encrypted_text
    msg = ''.join(tbl[ord(x) - 33] for x in msg[1:])
    return msg


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

gr.TabbedInterface(
    [encode_ui, decode_ui], ["encode", "decode"]
).launch()
