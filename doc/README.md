# wanderer

### vscode
* 下载`vscode`,并安装插件`Settings Sync`,同步插件以及配置
* 使用`gist id`:  `482670641db3f8a4530bea3672f116fb`

### 架构设计
* 使用在线网站: [https://www.draw.io/](https://www.draw.io/)
* 打开本地`doc/develop.drawio`文件

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
