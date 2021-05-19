# wanderer -- 开发文档

```
__        __              _                    
\ \      / /_ _ _ __   __| | ___ _ __ ___ _ __ 
 \ \ /\ / / _` | '_ \ / _` |/ _ \ '__/ _ \ '__|
  \ V  V / (_| | | | | (_| |  __/ | |  __/ |   
   \_/\_/ \__,_|_| |_|\__,_|\___|_|  \___|_|   
```

### figlet
* 艺术字生成器，由ASCII字符组成，把文本显示成标题栏。

### vscode
* 使用`vscode`的`Remote - SSH`连接`linux`进行开发,并推荐安装以下插件
* [vscode-cpptools-linux](https://github.com/Microsoft/vscode-cpptools/releases)
* [vscode-drawio](https://marketplace.visualstudio.com/items?itemName=eightHundreds.vscode-drawio)
* [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)
* ~~[clangd](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd)~~
* 装`vscode`插件`C++ Intellisense`,并安装`sudo apt install global`,并设置`vscode`配置文件`"C_Cpp.intelliSenseEngine": "Default"
}`

### 内存泄漏检测工具
* [https://www.valgrind.org/downloads/current.html#current](https://www.valgrind.org/downloads/current.html#current)

### 架构设计
* 使用在线网站: [https://www.draw.io/](https://www.draw.io/)
* 打开本地`doc/develop.drawio`文件

### JsonRpc做通讯协议
[https://github.com/badaix/jsonrpcpp](https://github.com/badaix/jsonrpcpp)

### 规范

* `c++`命名约束

    > [https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/)

    |命名|说明|示例|
    |-|-|-|
    |文件名|小写单词，下划线连接|test_socket.h test_socket.cpp|
    |普通变量|小写单词，下划线连接|test_var|
    |类变量|小写单词，下划线连接，下划线结尾|test_var_|
    |结构体变量|同普通变量|test_var|
    |类名|大驼峰命名|TestClass|
    |函数名|大驼峰命名|TestFunction|
    |常量命名|k开头+大驼峰命名|kTestValue|
    |枚举命名|名称大驼峰命名,变量同常量|AppType,kAll|

### 测试
* `secret`可以使用`openssl rand -hex 16`生成


### 日志  
```c++
LOG(Global)<< "Generic level that represents all levels. Useful when setting global configuration for all levels.";

LOG(Trace)<< "Information that can be useful to back-trace certain events - mostly useful than debug logs.";

LOG(Debug)<< "Informational events most useful for developers to debug application. Only applicable if NDEBUG is not defined (for non-VC++) or _DEBUG is defined (for VC++).";

LOG(Fatal)<< "Very severe error event that will presumably lead the application to abort.";

LOG(Error)<< "Error information but will continue application to keep running.";

LOG(Warning)<< "Information representing errors in application but application will keep running.";

LOG(Info)<< "Mainly useful to represent current progress of application.";

LOG(Verbose)<< "Information that can be highly useful and vary with verbose logging level. Verbose logging is not applicable to hierarchical logging.";

LOG(Unknown)<< "Only applicable to hierarchical logging and is used to turn off logging completely.";
```

### RSA 非对称加密

* 私钥生成
```sh
openssl genrsa -out privatekey.pen 1024
```
* 公钥生成
```sh
openssl rsa -in privatekey.pem -puout -out publickey.pem 
```


### C++ 平台宏定义示例
```c++
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   //define something for Windows (32-bit and 64-bit, this part is common)
   #ifdef _WIN64
      //define something for Windows (64-bit only)
   #else
      //define something for Windows (32-bit only)
   #endif
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
         // iOS Simulator
    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __linux__
    // linux
#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
#   error "Unknown compiler"
#endif
```
