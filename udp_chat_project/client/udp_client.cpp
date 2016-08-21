#include"udp_client.h"
udp_client::udp_client(string _ip,short _port)
:ip(_ip)
,port(_port)
,sock(-1)
{}
void udp_client::add_fri_list(const string& _win_f)
{
	vector<string>::iterator _iter=fri_list.begin();
	for(;_iter!=fri_list.end();++_iter)
	{
		if(*_iter==_win_f)
			return;
	}
	fri_list.push_back(_win_f);
}
void udp_client::del_fri_list(const string& _win_f)
{
	vector<string>::iterator _iter=fri_list.begin();
	for(;_iter!=fri_list.end();)
	{
		if(*_iter==_win_f)
		{
			_iter=fri_list.erase(_iter);
			break;
		}
		else
			++_iter;
	}
}
void udp_client::init()
{
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
		exit(1);
	}
}
int udp_client::send_data(string& _in)
{
	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_port=htons(port);
	client.sin_addr.s_addr=inet_addr(ip.c_str());
	socklen_t len=sizeof(client);
	ssize_t _s=sendto(sock,_in.c_str(),_in.size(),0,(struct sockaddr*)&client,len);
	if(_s<0)
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
	}
	return _s;
}
int udp_client::recv_data(string& _out)
{
	struct sockaddr_in remote;
	socklen_t len=sizeof(remote);
	char buf[_SIZE_];
	ssize_t _s=recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&remote,&len);
	if(_s>0)
	{
		buf[_s]='\0';
		_out=buf;
	}
	else 
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
	}
	return _s;
}
udp_client::~udp_client()
{
	if(sock>0)
	{
		close(sock);
	}
}
