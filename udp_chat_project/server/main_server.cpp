#include"udp_server.h"
void Usage(const char* proc)
{
	cout<<"Usage: "<<proc<<" [ip] [port]"<<endl;
}
void* recv(void* arg)
{
	udp_server* _ser=(udp_server*)arg;
	while(1)
	{
		_ser->recv_data();
	}
	return NULL;
}
void* broad_cast(void* arg)
{
	udp_server* _ser=(udp_server*)arg;
	while(1)
	{
		_ser->broadcast();
	}
	return NULL;
}
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		Usage(argv[0]);
		exit(0);
	}
	string ip=argv[1];
	short port=atoi(argv[2]);
	udp_server _se(ip,port);
	_se.init();

//	daemon(0,0);
		
	pthread_t tid1;
	pthread_t tid2;
	pthread_create(&tid1,NULL,recv,(void*)&_se);
	pthread_create(&tid2,NULL,broad_cast,(void*)&_se);
	
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	//while(1)
	//{
	//	if(_se.recv_data()>0)
	//	{
	//		_se.broadcast();
	//	}
	//}
	return 0;
}
