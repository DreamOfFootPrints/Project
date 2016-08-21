#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<string>
#include<stdlib.h>
#include<map>
#include"comm.h"
#include"data_pool.h"
#include"udp_data.h"
#define _DEFAULT_IP_  "127.0.0.1"
#define _DEFAULT_PORT_ 8080
class udp_server
{
	public:
		udp_server(string _ip=_DEFAULT_IP_,short _port=_DEFAULT_PORT_);
		void init();
		void add_user(string& ip,struct sockaddr_in& client);
		void del_user(string& ip,string& out);
		int send_data(struct sockaddr_in& client,socklen_t size,string&  msg);
		int recv_data();
		int broadcast();
		~udp_server();
	private:
		string ip;
		short port;
		int sock;
		data_pool pool;
		map<string,struct sockaddr_in> user_online;
};
