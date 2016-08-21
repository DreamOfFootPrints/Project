#include"data_pool.h"
data_pool::data_pool(int size)
:get_index(0)
,put_index(0)
,capacity(size)
,pool(size)
{
	 sem_init(&put_sem, 0, capacity);
	 sem_init(&get_sem, 0, 0);
}
void data_pool::data_put(string& _in)
{
	sem_wait(&put_sem);//p
	pool[put_index++]=_in;
	put_index%=capacity;
	sem_post(&get_sem);//v
}
void data_pool::data_get(string& _out)
{
	sem_wait(&get_sem);//p
	_out=pool[get_index++];
	get_index%=capacity;
	sem_post(&put_sem);//v
}
data_pool::~data_pool()
{
	sem_destroy(&put_sem);
	sem_destroy(&get_sem);
}
