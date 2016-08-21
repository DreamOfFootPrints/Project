#include"udp_data.h"
udp_data::udp_data(const char* _cmd)
:cmd(_cmd)
{}
void udp_data::data_to_string(string& _in_name,string& _in_msg,string& _in_school,string _in_cmd,string& _out_str)
{
	nick_name=_in_name;
	msg=_in_msg;
	school=_in_school;
	cmd=_in_cmd;
	Json::Value root;
	root["nick_name"]=nick_name;
	root["msg"]=msg;
	root["school"]=school;
	root["cmd"]=cmd;
	my_json::serialize(root,_out_str);
//	cout<<_in_name<<endl;
//	cout<<_out_str<<endl;
}
void udp_data::data_to_value(string& _out_name,string& _out_msg,string& _out_school,string& _out_cmd,string& _in_str)
{
	Json::Value root;
	my_json::deserialize(_in_str,root);
	_out_name=root["nick_name"].asString();
//	cout<<_out_name<<endl;
	_out_msg=root["msg"].asString();
//	cout<<_out_msg<<endl;
	_out_school=root["school"].asString();
	_out_cmd=root["cmd"].asString();
	nick_name=_out_name;
	msg=_out_msg;
	school=_out_school;
	cmd=_out_cmd;
//	cout<<cmd;
}

udp_data::~udp_data()
{}


//int main()
//{
//	udp_data ud;
//	string _name;
////	cout<<"please input name: ";
////	cin>>_name;
//	string _msg;
////	cout<<"please input msg: ";
////	cin>>_msg;
//	string _school;
////	cout<<"please input school: ";
////	cin>>_school;
//	string _cmd;
////	cout<<"please input cmd: ";
////	cin>>_cmd;
//	string _out="{\"cmd\":\"None\",\"msg\":\"hello\",\"nick_name\":\"rz\",\"school\":\"xpu\"}";
////	_name="rz";
////	ud.data_to_string(_name,_msg,_school,_cmd,_out);
////	_name="";
//	ud.data_to_value(_name,_msg,_school,_cmd,_out);
////	cout<<_out<<endl;
//	cout<<_name<<endl;
//	cout<<_msg<<endl;
//	cout<<_school<<endl;
//	cout<<_cmd<<endl;
//	return 0;
//}
