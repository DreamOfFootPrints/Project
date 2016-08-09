////#include <iostream>
////using namespace std;
////
////#include <vector>
////#include <list>
////#include <algorithm>
////
////void TestVector()
////{
////	vector<int> v;
////	v.push_back(1);
////	v.push_back(2);
////	v.push_back(3);
////	v.push_back(4);
////
////	cout<<"size?"<<v.size()<<endl;
////	cout<<"capacity?"<<v.capacity()<<endl;
////	cout<<"maxsize?"<<v.max_size()<<endl;
////
////	vector<int>::iterator it = v.begin();
////	while(it != v.end())
////	{
////		cout<<*it<<" ";
////		++it;
////	}
////
////	for (size_t i = 0; i < v.size(); ++i)
////	{
////		cout<<v[i]<<" ";
////	}
////
////	cout<<endl;
////}
////
////void TestList()
////{
////	list<int> l;
////	l.push_back(1);
////	l.push_back(2);
////	l.push_back(3);
////	l.push_back(4);
////
////	list<int>::iterator it = l.begin();
////	while (it != l.end())
////	{
////		cout<<*it<<" ";
////		++it;
////	}
////	cout<<endl;
////
////	list<int>::reverse_iterator rIt = l.rbegin();
////	while (rIt != l.rend())
////	{
////		cout<<*rIt<<" ";
////		++rIt;
////	}
////	cout<<endl;
////
////	list<int>::iterator ret = find(l.begin(), l.end(), 5);
////	if (ret != l.end())
////	{
////		cout<<"找到了"<<*ret<<endl;
////	}
////	else
////	{
////		cout<<"没有找到"<<endl;
////	}
////
////	// 迭代器失效
////	// 删除所有偶数
////	it = l.begin();
////	while (it != l.end())
////	{
////		/*list<int>::iterator del = it;
////		++it;
////
////		if (*del %2 == 0)
////		{
////			l.erase(del);
////		}*/
////
////		if (*it %2 == 0)
////		{
////			it = l.erase(it);
////		}
////		else
////		{
////			++it;
////		}
////	}
////
////	it = l.begin();
////	while (it != l.end())
////	{
////		cout<<*it<<" ";
////		++it;
////	}
////	cout<<endl;
////}
////
////int main()
////{
////	TestVector();
////	TestList();
////
////	return 0;
////}
//
////#include <iostream>
////#include <assert.h>
////using namespace std;
////
////#include "List.h"
////#include "Vector.h"
////
////#include <list>
////
//////struct A
//////{
//////	int _a1;
//////	int _a2;
//////
//////	A(int a1, int a2)
//////		:_a1(a1)
//////		,_a2(a2)
//////	{}
//////};
//////
//////list<A> l;
//////l.push_back(A(2,3));
//////l.push_back(A(3,4));
//////
//////list<A>::iterator it = l.begin();
//////while (it != l.end())
//////{
//////	//cout<<*it<<endl;
//////	// it->operator-> ==> A* 
//////	cout<<it->_a1<<":"<<it->_a2<<endl;
//////	++it;
//////}
////
////struct A
////{
////	int _a;
////
////	A(int a)
////		:_a(a)
////	{}
////};
////
////int main()
////{
////	//TestList();
////	TestVector();
////
////	return 0;
////}
//
//#include <iostream>
//#include <assert.h>
//using namespace std;
//
//#include "List.h"
//#include "Vector.h"
//#include "Iterator.h"
//#include "Allocate.h"
//
//void TestIterator()
//{
//	Vector<int> v;
//	v.PushBack(1);
//	v.PushBack(2);
//	v.PushBack(3);
//	v.PushBack(4);
//
//	List<int> l;
//	l.PushBack(1);
//	l.PushBack(2);
//	l.PushBack(3);
//
//	// O(1)
//	cout<<"Vector Distance?"<<Distance(v.Begin(), v.End())<<endl;
//	// O(N)
//	cout<<"List Distance?"<<Distance(l.Begin(), l.End())<<endl;
//
//
//	// O(1)
//	Vector<int>::Iterator vIt = v.Begin();
//	Advance(vIt, 2);
//	cout<<"Vector Advance?"<<*vIt<<endl;
//
//	// O(N)
//	List<int>::Iterator lIt = l.Begin();
//	Advance(lIt, 1);
//	cout<<"List Advance?"<<*lIt<<endl;
//}
//
//int main()
//{
//	//TestIterator();
//	//TestList();
//	TestVector();
//
//	// Test1();
//	//Test2();
//	//Test3();
//
//	return 0;
//}

#include <iostream>
#include <string>
using namespace std;

#include <map>
#include <set>

void TestSet()
{
	set<string> nameSet;
	nameSet.insert("吴");
	nameSet.insert("田");
	nameSet.insert("马");

	cout<<"count?"<<nameSet.count("ma")<<endl;
	cout<<"count?"<<nameSet.count("吴")<<endl;

	set<string>::iterator it = nameSet.find("马");
	if (it != nameSet.end())
	{
		nameSet.erase(it);
	}
	
	/*it = nameSet.find("马");
	nameSet.erase(it);*/

	nameSet.erase("tian");
	nameSet.erase("田");

	it = nameSet.begin();
	while (it != nameSet.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;

	set<int> s;
	s.insert(3);
	s.insert(10);
	s.insert(2);
	s.insert(11);
	s.insert(100);

	set<int>::iterator it2 = s.begin();
	while (it2 != s.end())
	{
		cout<<*it2<<" ";
		++it2;
	}

	cout<<endl;
}

struct Info
{
	string _name;
	int _score;
	// ...

	Info(const char* name, int score)
		:_name(name)
		,_score(score)
	{}

	bool operator<(const Info& info) const
	{
		return _score < info._score;
	}
};

void TestMap()
{
	//map<int, Info> infosMap;
	//infosMap.insert(pair<int, Info>(60, Info("xiaoxu", 60)));
	//infosMap.insert(pair<int, Info>(80, Info("xiaowang", 80)));
	//infosMap.insert(pair<int, Info>(20, Info("xiaoyang", 20)));
	//infosMap.insert(pair<int, Info>(70, Info("xiaozhang", 70)));
	//
	//map<int, Info>::iterator it = infosMap.find(60);
	//while (it != infosMap.end())
	//{
	//	// pair<key, value>
	//	cout<<it->first<<" : ";
	//	cout<<it->second._name<<" "<<it->second._score<<endl;
	//	++it;
	//}
	//cout<<endl;


	//map<Info, int> infosMap;
	//infosMap.insert(pair<Info, int>(Info("xiaoxu", 60), 60));
	//infosMap.insert(pair<Info, int>(Info("xiaoxu", 60), 70));
	//infosMap.insert(pair<Info, int>(Info("xiaoxu", 60), 80));

	//map<Info, int>::iterator it = infosMap.begin();
	//if (it != infosMap.end())
	//{
	//	cout<<it->second<<endl;
	//}

	//set<int> s;
	//s.insert(3);
	//s.insert(10);
	//s.insert(3);
	//s.insert(11);
	//s.insert(100);

	//set<int>::iterator it2 = s.begin();
	//while (it2 != s.end())
	//{
	//	cout<<*it2<<" ";
	//	++it2;
	//}
	//cout<<endl;

	//multiset<int> s1;
	//s1.insert(3);
	//s1.insert(10);
	//s1.insert(3);
	//s1.insert(11);
	//s1.insert(100);

	//multiset<int>::iterator it3 = s1.begin();
	//while (it3 != s1.end())
	//{
	//	cout<<*it3<<" ";
	//	++it3;
	//}
	//cout<<endl;

	char* a[5] = {"hash", "sort", "hash", "word", "iterator"};
	map<string, int> countMap;
	for (size_t i = 0; i < 5; ++i)
	{
		/*map<string, int>::iterator it = countMap.find(a[i]);
		if (it == countMap.end())
		{
			countMap.insert(pair<string, int>(a[i], 1));
		}
		else
		{
			it->second++;
		}*/
		countMap[a[i]]++;
	}

	countMap["map"] = 5;

	map<string, string> dict;
	dict["hash"] = "哈希";
	dict["sort"] = "排序";
	dict["hash"] = "排序";

	pair<map<string, string>::iterator, bool> ret;
	ret = dict.insert(pair<string, string>("hash", "sdadada"));
	ret.first->second = "sdadada";

	ret = dict.insert(pair<string, string>("string", "sdadada"));
}

int main()
{
	//TestSet();
	TestMap();
	return 0;
}
	//for()
	//{
	//	countMap[a[i]]++;
	//}

	//countMap["map"];

//V& operator[](const K& key)
//{
//	it = find(key);
//	if(it == end())
//	{
//		it = insert(pair<K, V>(key, V()));
//	}
//
//	return it->second;
//}
