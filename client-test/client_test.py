# -*- coding:utf-8 -*-
import sys
from ctypes import *


def receive(result, code):
    print(str(result))


# CFUNCTYPE 第一个是返回值 ，剩下是对应的参数
CFunTypeReceive = CFUNCTYPE(None, c_bool, c_int)
receiveCallback = CFunTypeReceive(receive)

libPath = ''
if sys.platform == "win32":
    libPath = '../build/src/Debug/wanderer-sdk.dll'
elif sys.platform == "linux":
    libPath = '../build/src/libwanderer-sdk.so'

print("load lib path"+libPath)

wd = cdll.LoadLibrary(libPath)
wd.Test("xxxxxxx".encode('ascii'))

network = wd.NewNetwork()
wd.Connect(network,"127.0.0.1".encode('ascii'), 12233)

while True:
    wd.Update(network)

wd.DisConnect(network)
# wd.DeleteNetwork(network)
# wd.Test("xxxxxxx")
