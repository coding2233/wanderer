# -*- coding:utf-8 -*-

import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)

server.bind(("127.0.0.1", 2234))
server.listen(10)
print("server listen port: 2234")

while True:
    print("wait to connect...")
    con = server.accept()
    print("new connect!!")
