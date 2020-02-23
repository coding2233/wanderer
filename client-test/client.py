# -*- coding:utf-8 -*-

import socket
import test_pb2

server_address = "127.0.0.1"
server_port = 2233

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.bind(("127.0.0.1", 0))
client_socket.connect((server_address, server_port))
# client_socket.setblocking(False)

test_msg = test_pb2.TestMessage()

test_msg.id = 5226
test_msg.name = "test_name"
test_msg.content = "test_message_content"


def parsMessage(msg):
    length = len(msg)+8
    size = (length).to_bytes(4, byteorder="big")
    ty = (1).to_bytes(4, byteorder="big")
    return size+ty+msg


for item in range(0, 100):
    data = test_msg.SerializeToString()
    print(data)
    data = parsMessage(data)
    print(data)
    # str.encode(data)
    client_socket.send(data)


print("test-success!")


while True:
    data = client_socket.recv(1024)
    if data:
        print(data.decode('utf-8'))
