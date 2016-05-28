#pragma once
#include"HuffmanTree.h"
#include"FileCompress.h"
#include<time.h>


void Test1()
{
	int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int len = sizeof(arr) / sizeof(arr[0]);
	HuffmanTree<int> t(arr, len);
}


void TestFileCompress()
{
	int a = clock();
	FileCompress fc;
	char* fileName = "Input.BIG";
	fc.Compress(fileName);
	cout << "ѹ���ļ�" << fileName << endl;
	char* fileUnCompress =fileName;
	fc.UnComparess(fileUnCompress);
	cout << "��ѹ���ļ���" << fileUnCompress << endl;
	int b = clock();
	cout << "����ʱ����" << b - a << endl;
}

int main()
{
	/*Test1();*/
	TestFileCompress();
	system("pause");
	return 0;
}