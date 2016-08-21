#include"chat_window.h"
chat_window::chat_window()
{
	pthread_mutex_init(&mutex,NULL);
	initscr();//init screen
	curs_set(0);//hide mouse pointer
}
void chat_window::put_str_to_win(WINDOW* _win,int _y,int _x,const string& msg)
{
	mvwaddstr(_win,_y,_x,msg.c_str());//mv window  add str :C function
}
string chat_window::get_str_from_win(WINDOW* _win)
{
	char buf[_SIZE_];
	memset(buf,'\0',sizeof(buf));
	wgetnstr(_win,buf,sizeof(buf)-1);
	return buf;
}
void chat_window::create_header()
{
	int _y=0;//row
	int _x=0;//col
	int _h=LINES/5;
	int _w=COLS;
	header=newwin(_h,_w,_y,_x);//create new window
}
void chat_window::create_output()
{
	int _y=LINES/5;//row
	int _x=0;//col
	int _h=(LINES*3)/5;
	int _w=(COLS*4)/5;
	output=newwin(_h,_w,_y,_x);//create new window
}
void chat_window::create_friends_list()
{
	int _y=LINES/5;//row
	int _x=(COLS*4)/5;//col
	int _h=(LINES*3)/5;
	int _w=COLS/5;
	friends_list=newwin(_h,_w,_y,_x);//create new window
}
void chat_window::create_input()
{
	int _y=(LINES*4)/5;//row
	int _x=0;//col
	int _h=LINES/5;
	int _w=COLS;
	input=newwin(_h,_w,_y,_x);//create new window
}
chat_window::~chat_window()
{
	pthread_mutex_destroy(&mutex);
	delwin(header);//destroy window
	delwin(output);//destroy window
	delwin(friends_list);//destroy window
	delwin(input);//destroy window
	endwin();
}
//WINDOW* chat_window::create_newwin(int _h,int _w,int _y,int _x)
//{
//	WINDOW* _win=newwin(_h,_w,_y,_x);
//	box(_win,0,0u);
//	return _win;
//}
void chat_window::fflush_win(WINDOW* _win)
{
	pthread_mutex_lock(&mutex);
	box(_win,0,0);
	wrefresh(_win);
	pthread_mutex_unlock(&mutex);
}
void chat_window::clear_win_line(WINDOW* _win,int begin,int num)
{
	while(num-- > 0)
	{
		wmove(_win,begin++,0);//0 is col
		wclrtoeol(_win);//window clear to eof last
	}
}
//void* draw_header(void* arg)
//{
//	chat_window* _win=(chat_window*)arg;
//	_win->create_header();
//	string _line="HELLO WORLD";
//	int _max_y;
//	int _max_x;
//	getmaxyx(_win->header,_max_y,_max_x);
//
//	int _y=_max_y/2;
//	int _x=1;
//	while(1)
//	{
//		_win->put_str_to_win(_win->header,_y,_x,_line);
//		_win->fflush_win(_win->header);
//		usleep(10000);
//		_x++;
//		_x%=_max_x;
//		_win->clear_win_line(_win->header,_y,2);
//		_win->fflush_win(_win->header);
//		usleep(10000);
//	}
//
//}
//void* draw_output(void* arg)
//{
//	chat_window* _win=(chat_window*)arg;
//	_win->create_output();
//	while(1)
//	{
//		usleep(1000000);
//		_win->fflush_win(_win->output);
//	}
//}
//void* draw_friends_list(void* arg)
//{
//	chat_window* _win=(chat_window*)arg;
//	_win->create_friends_list();
//	while(1)
//	{
//		usleep(1000000);
//		_win->fflush_win(_win->friends_list);
//	}
//}
//void* draw_input(void* arg)
//{
//	chat_window* _win=(chat_window*)arg;
//	_win->create_input();
//	string _line="please input#";
//	int _max_y;
//	int _max_x;
//	getmaxyx(_win->input,_max_y,_max_x);
//	string _msg;
//	while(1)
//	{
//		usleep(1000000);
//		_win->put_str_to_win(_win->input,1,1,_line);
//		_win->fflush_win(_win->input);
//		_msg=_win->get_str_from_win(_win->input);
//		_win->clear_win_line(_win->input,1,1);
//		usleep(1000);
//		_win->put_str_to_win(_win->input,1,1,_line);
//		_win->fflush_win(_win->input);
//	}
//}
//int main()
//{
//	chat_window _wi;
//	pthread_t th,to,tf,ti;
//	pthread_create(&th,NULL,draw_header,(void*)&_wi);
//	pthread_create(&to,NULL,draw_output,(void*)&_wi);
//	pthread_create(&tf,NULL,draw_friends_list,(void*)&_wi);
//	pthread_create(&ti,NULL,draw_input,(void*)&_wi);
//	pthread_join(th,NULL);
//	pthread_join(to,NULL);
//	pthread_join(tf,NULL);
//	pthread_join(ti,NULL);
//	return 0;
//}
