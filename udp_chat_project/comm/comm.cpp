#include"comm.h"
void print_log(const char* msg,const char* fun,int line)
{
	cout<<msg<<": [ "<<fun<<" ] "<<line<<endl;
}
