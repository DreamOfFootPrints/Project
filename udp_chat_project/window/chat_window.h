#pragma once
#include<iostream>
#include<string.h>
#include<string>
#include<ncurses.h>
#include<pthread.h>
#include<unistd.h>
#include"comm.h"
//#define _SIZE_ 1024
using namespace std;
class chat_window
{
	public:
		chat_window();
		void put_str_to_win(WINDOW* _win,int _y,int _x,const string& msg);
		string get_str_from_win(WINDOW* _win);

		void create_header();
		void create_output();
		void create_friends_list();
		void create_input();
		~chat_window();
//		WINDOW* create_newwin(int _h,int _w,int _y,int _x);
		void fflush_win(WINDOW* _win);
		void clear_win_line(WINDOW* _win,int begin,int num);
	public:
		WINDOW* header;
		WINDOW* output;
		WINDOW* friends_list;
		WINDOW* input;
		pthread_mutex_t mutex;
};
