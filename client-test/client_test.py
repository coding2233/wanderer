# -*- coding:utf-8 -*- 

from ctypes import *


def receive(s,data,sd):
    print(data)

# CFUNCTYPE 第一个是返回值 ，剩下是对应的参数
CFunTypeReceive = CFUNCTYPE(None,c_int,c_char_p,c_int)
receiveCallback = CFunTypeReceive(receive)

wd =  cdll.LoadLibrary('../build/src/libwanderer-sdk.so')
network = wd.Connect("127.0.0.1",12233,receiveCallback)
while True:
    wd.Update(network)
wd.DisConnect(network)
# wd.Test("xxxxxxx")
