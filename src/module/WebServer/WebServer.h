#ifndef __HTTP_SERVER_MODULE_H__
#define __HTTP_SERVER_MODULE_H__

#include <iostream>
#include <functional>
#include <map>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <queue>
#include <thread>

#include "base/module.h"
#include "WebServer/mongoose/mongoose.h"

namespace fs = std::filesystem;

namespace wanderer
{
    //struct http server opts
    static struct mg_serve_http_opts http_server_opts;

    struct file_writer_data
    {
        FILE *fp;
        size_t bytes_written;
    };

    class WebServer : public Module
    {

    private:
        struct mg_mgr mgr_;

        static std::map<const char *, const char *> map_upload_files;
        //	static std::map<const char*, const char*>::iterator iter_upload_files;

        // 静态事件响应函数
        static void OnHttpEvent(mg_connection *connection, int event_type, void *event_data);
        //文件处理
        static mg_str OnFileUploadEvent(mg_connection *connection, mg_str file_name);

        /* data */
    public:
        WebServer(System *system);
        ~WebServer();

        //初始化函数
        void OnInit() override;
        //循环
        void OnUpdate() override;
        //关闭
        void OnClose() override;
    };
} // namespace wanderer

#endif