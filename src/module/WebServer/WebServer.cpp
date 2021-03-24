#include "WebServer/WebServer.h"
namespace wanderer
{
	std::map<const char *, const char *> WebServer::map_upload_files = {
		{"a", "a"}};

	WebServer::WebServer(System *system) : Module(system)
	{
		map_upload_files.clear();
	}

	WebServer::~WebServer()
	{
	}

	void WebServer::OnInit()
	{
		const char *port = "19321";
		const char *document_root = "./files";

		struct mg_connection *nc;

		mg_mgr_init(&mgr_, NULL);
		std::cout << "Starting web server on port: " << port << ", Document root path:" << document_root << std::endl;

		nc = mg_bind(&mgr_, port, OnHttpEvent);
		if (nc == nullptr)
		{
			throw std::runtime_error("Failed to create listener");
		}
		mg_set_protocol_http_websocket(nc);
		http_server_opts.document_root = document_root;
		http_server_opts.enable_directory_listing = "yes";
	}

	void WebServer::OnUpdate()
	{
		int poll_result = mg_mgr_poll(&mgr_, 1000);
	}

	void WebServer::OnClose()
	{
		mg_mgr_free(&mgr_);
	}

	mg_str WebServer::OnFileUploadEvent(mg_connection *connection, mg_str mg_file_name)
	{
		mg_printf(connection,
				  "HTTP/1.1 200 OK\r\n"
				  "Content-Type: text/plain\r\n"
				  "Connection: close\r\n\r\n"
				  "File-Name: %s \n\n",
				  mg_file_name.p);
		connection->flags |= MG_F_SEND_AND_CLOSE;
		return mg_file_name;
	}

	void WebServer::OnHttpEvent(mg_connection *connection, int event_type, void *event_data)
	{
		http_message *http_req = (http_message *)event_data;
		struct file_writer_data *data = (struct file_writer_data *)connection->user_data;
		struct mg_http_multipart_part *mp = (struct mg_http_multipart_part *)event_data;

		switch (event_type)
		{
		case MG_EV_HTTP_REQUEST:
			mg_serve_http(connection, (struct http_message *)event_data, http_server_opts);
		case MG_EV_HTTP_MULTIPART_REQUEST_END:
		case MG_EV_HTTP_PART_BEGIN:
		case MG_EV_HTTP_PART_DATA:
		case MG_EV_HTTP_PART_END:
			//save map
			struct mg_http_multipart_part *mp = (struct mg_http_multipart_part *)event_data;
			map_upload_files[mp->file_name] = mp->var_name;
			//	map_upload_files.insert(mp->file_name, mp->var_name);
			//write file
			mg_file_upload_handler(connection, event_type, event_data, OnFileUploadEvent);
			if (event_type == MG_EV_HTTP_PART_END)
			{
				std::cout << "MG_EV_HTTP_PART_END!!" << mp->file_name << std::endl;

				std::string file_name = mp->file_name;
				auto iter = map_upload_files.find(mp->file_name);
				if (iter != map_upload_files.end())
				{
					if (fs::exists(file_name))
					{
						std::string dir_name = std::string(iter->second);
						int index = dir_name.find("/");
						dir_name = dir_name.substr(0, index);
						std::string root_path = std::string(http_server_opts.document_root);
						dir_name = root_path + "/" + dir_name;
						if (!fs::exists(dir_name))
						{
							fs::create_directories(dir_name);
						}
						dir_name = dir_name + "/" + file_name;
						if (fs::exists(dir_name))
						{
							fs::remove(dir_name);
						}

						fs::copy_file(file_name, dir_name);
						fs::remove(file_name);

						std::cout << "Move file to other place  :  " << iter->first << "  ##  " << iter->second << "  ##  " << dir_name << std::endl;
						map_upload_files.erase(iter->first);
					}
				}
			}
			/*if (event_type == MG_EV_HTTP_MULTIPART_REQUEST_END)
			{
				std::cout << "end!!" << std::endl;
			}*/
			break;
			/*default:
				break;*/
		}
	}

} // namespace wanderer