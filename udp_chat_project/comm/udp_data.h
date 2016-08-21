#pragma once
#include"comm.h"
#include"my_json.h"
#include<iostream>
using namespace std;
class udp_data
{
	public:
		udp_data(const char* _cmd="None");
		void data_to_string(string& _in_name,string& _in_msg,string& _in_school,string _in_cmd,string& _out_str);
		void data_to_value(string& _out_name,string& _out_msg,string& _out_school,string& _out_cmd,string& _in_str);
		~udp_data();
	public:
		string nick_name;
		string msg;
		string school;
		string cmd;
};
