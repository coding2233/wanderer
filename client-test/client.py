# -*- coding:utf-8 -*-

import socket

server_address="127.0.0.1"
server_port=2233

client_socket= socket.socket(socket.AF_INET,socket.SOCK_STREAM);
client_socket.bind(("127.0.0.1",0))
client_socket.connect((server_address,server_port))

client_socket.send(b'123')