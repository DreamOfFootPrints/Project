#include"udp_server.h"
udp_server::udp_server(string _ip,short _port)
:ip(_ip)
,port(_port)
,sock(-1)
{}
void udp_server::init()
{
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
		exit(1);
	}

	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(port);
	if(ip=="any")
		local.sin_addr.s_addr=htonl(INADDR_ANY);
	else
		local.sin_addr.s_addr=inet_addr(ip.c_str());
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
		exit(2);
	}
}
void udp_server::add_user(string& ip,struct sockaddr_in& client)
{
	map<string,struct sockaddr_in>::iterator iter=user_online.find(ip);
	if(iter==user_online.end())
	{
		user_online.insert(pair<string,struct sockaddr_in>(ip,client));
	}
	else
		return;
}
void udp_server::del_user(string& ip,string& out)
{
	string _name;
	string _msg;
	string _school;
	string _cmd;
	udp_data _data;
	_data.data_to_value(_name,_msg,_school,_cmd,out);
	if(_cmd=="QUIT")
		user_online.erase(ip);
}
int udp_server::send_data(struct sockaddr_in& client,socklen_t size,string& msg)
{

	ssize_t _s=sendto(sock,msg.c_str(),msg.size(),0,(struct sockaddr*)&client,size);
	if(_s<0)
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
	}

//	cout<<"send"<<endl;
	return _s;
}
int udp_server::recv_data()
{
	struct sockaddr_in remote;
	socklen_t len=sizeof(remote);
	char buf[_SIZE_];
	ssize_t _s=recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&remote,&len);
	if(_s>0)
	{
		buf[_s]='\0';
		cout<<"client: "<<buf<<endl;
		string out=buf;
		pool.data_put(out);
		string key_ip=inet_ntoa(remote.sin_addr);

		this->add_user(key_ip,remote);
		this->del_user(key_ip,out);
	}
	else if(_s==0)
	{
		print_log("client is close",__FUNCTION__,__LINE__);
	}
	else 
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
	}
	return _s;
}
int udp_server::broadcast()
{
	string msg;
	pool.data_get(msg);
//	cout<<msg<<endl;
	map<string,struct sockaddr_in>::iterator iter=user_online.begin();
	for(;iter!=user_online.end();++iter)
	{
		send_data(iter->second,sizeof(iter->second),msg);
	}
	return 0;
}
udp_server::~udp_server()
{
	if(sock>0)
	{
		close(sock);
	}
}
