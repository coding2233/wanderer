# -*- coding:utf-8 -*-
import sys
from ctypes import *

serverIP = "127.0.0.1"
libPath = ''
if sys.platform == "win32":
    libPath = '../build/src/Debug/wanderer-sdk.dll'
    serverIP = "192.168.0.85"
elif sys.platform == "linux":
    libPath = '../build/src/libwanderer-sdk.so'

print("load lib path"+libPath)

wd = cdll.LoadLibrary(libPath)
wd.WandererTest("xxxxxxx".encode('ascii'))


def receive(result, code):
    print(str(result))


def login_callback(result,message):
    print("--python---login_callback-----")
    print("登陆回调：" + str(result)+"  message: "+message)

# 登陆回调回调
CFunTypeLogin = CFUNCTYPE(None,c_bool,c_char_p)
login_callback_function = CFunTypeLogin(login_callback)

def connect_callback(result,message):
    print("[python] 连接回调：" + str(result)+"  message: "+str(message))
    if result:
        print("The customer service side connects to the server.")
        wd.WandererLogin("admin".encode('ascii'), "admin".encode('ascii'),login_callback_function)

# CFUNCTYPE 第一个是返回值 ，剩下是对应的参数
CFunTypeReceive = CFUNCTYPE(None, c_bool, c_int)
receiveCallback = CFunTypeReceive(receive)

# 连接回调
CFunTypeConnect = CFUNCTYPE(None,c_bool,c_char_p)
connect_callback_function = CFunTypeConnect(connect_callback)


wd.WandererConnect(serverIP.encode('ascii'), 12233,connect_callback_function)

while True:
    wd.WandererUpdate()

wd.WandererDisConnect()
