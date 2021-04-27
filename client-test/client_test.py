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
wd = cdll.LoadLibrary(libPath)
network = wd.Connect("127.0.0.1".encode('ascii'), 12233, receiveCallback)

while True:
    wd.Update(network)

wd.DisConnect(network)
# wd.Test("xxxxxxx")
