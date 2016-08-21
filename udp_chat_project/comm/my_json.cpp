#include"my_json.h"
my_json::my_json()
{}
int my_json::serialize(Json::Value& in_val ,string& out_str)
{
#ifdef	_FAST_JSON_
	Json::FastWriter write;
	out_str=write.write(in_val);
#else
	Json::StyledWriter write;
	out_str=write.write(in_val);
#endif
	return 0;
}
int my_json::deserialize(string& in_str,Json::Value& out_val)
{
	Json::Reader read;
	if(read.parse(in_str,out_val,false))
	{
	//	cout<<in_str<<endl;
		return 0;
	}
	return -1;	
}
my_json::~my_json()
{}
