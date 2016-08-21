#include"comm.h"
#include<iostream>
#include<string>
#include"json/json.h"
using namespace std;
class my_json
{
	public:
		my_json();
		~my_json();
        static int serialize(Json::Value& in_val ,string& out_str);
		static int deserialize(string& in_out,Json::Value& out_val);
	private:
};
