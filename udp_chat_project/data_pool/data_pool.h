#include<iostream>
#include<vector>
#include <semaphore.h>
#include"comm.h"
using namespace std;
#define _CAP_ 256
class data_pool
{
	public:
		data_pool(int size=_CAP_);
		void data_put(string& _in);
		void data_get(string& _out);
		~data_pool();
	private:
		vector<string> pool;
		int get_index;
		int put_index;
		int capacity;
		sem_t put_sem;
		sem_t get_sem;
};
