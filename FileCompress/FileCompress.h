#pragma once
#pragma warning (disable:4996)
#include"HuffmanTree.h"
#include<stdlib.h>
#include<string>

//统计字符次数
//构建Huffman树
//生成Huffman编码
//读取源文件字符，压缩


#define _DEBUG_

typedef unsigned long long LongType;//以后修改数据类型直接在这里修改即可


//一个字符对应一个编码，不然要一个一个遍历，用哈希表来进行映射（字符到编码），所以使用unsigned char（有些是负数的话就
//发生了越界）
struct CharInfo
{
public:
	unsigned char _ch;//字符.为什么是 unsigned 因为汉字编码有可能出现负数
	LongType _count;//出现次数
	string _code;//huffman code
public:
	CharInfo(LongType count = 0)//构造函数和默认的构造函数，写函数一定要写默认构造函数
		:_count(count)
		, _ch(0)
	{}

	//注意const的对象使用const的方法
	bool operator!=(const CharInfo& info) const//修饰成员函数，不改变成员变量
	{
		return _count != info._count;
	}

	LongType operator+(const CharInfo& info)const
	{
		return _count + info._count;
	}

	bool operator<(const CharInfo& info) const//修饰成员函数，不改变成员变量
	{
		return _count < info._count;
	}
};


class FileCompress//文件压缩
{
public:
	FileCompress()//构造函数
	{
		for (size_t i = 0; i < 256; i++)
		{
			_infos[i]._ch = i;//int到char有转换，但是没有问题
			_infos[i]._count = 0;
		}
	}

public:
	void Compress(const char* filename)//压缩
	{
		assert(filename);
		//统计文件中字符出现的次数
		FILE* fOut = fopen(filename, "rb");
		assert(fOut);
		char ch = fgetc(fOut);//不为unsigned char
		while (!feof(fOut))//EOF为-1
		{
			_infos[(unsigned char)ch]._count++;//直接定址法
			ch = fgetc(fOut);
		}
		//构建Huffman树（保存节点个数和字符）重点是字符，次数构建Huffman树，所以不为count
		const CharInfo invalid(0);//非法值，使用非法值是因为（1）256个值无需都构造，（2）判断无结构
		HuffmanTree<CharInfo> tree(_infos, 256,invalid);
		//生成Huffman Code
		string code;
		_GerenateHuffmanCode(tree.GetRoot(), code);//将每一个_infoes[i]写入对应的_code(huffman编码)
		//压缩
		string compressFileName = filename;
		compressFileName += ".huffman";
		FILE* fIn = fopen(compressFileName.c_str(), "wb");//满一个字节就往压缩文件中写
		assert(fIn);
		//读取文件，找出对应的字符的Huffman编码，转换成对应的位，进行压缩
		fseek(fOut, 0, SEEK_SET);//0为相对位置,回到文件头部
		ch = fgetc(fOut);
		char value = 0;
		int pos = 0;
		while (!feof(fOut))
		{
			string& code = _infos[(unsigned char)ch]._code;//直接定址法
			for (size_t i = 0; i < code.size(); ++i)
			{
				value <<= 1;//放在这判断条件就是8次
				if (code[i] == '1')
				{
					value |= 1;
				}
				//value <<= 1;//放在这判断条件就是7次，只是一种写法

				if (++pos == 8)
				{
					fputc(value, fIn);
					value = 0;
					pos = 0;
				}
			}
			ch = fgetc(fOut);
		}
		//有可能不够最后的8个比特位
		if (pos)
		{
			value =1<<(8 - pos);//因为操控的是bit位所以不能设置为2等其他
			fputc(value, fIn);
		}
		//配置文件，没有次数不能构建Huffman树，所以写一个配置文件，统计每个字符出现的次数，方便解压缩的时候重建Huffman树
		string conifgFilename = filename;
		conifgFilename += ".config";
		FILE* fInConfig = fopen(conifgFilename.c_str(), "wb");
		char buffer[128];
		string str;
		for (size_t i = 0; i < 256; ++i)
		{
			if (_infos[i]._count > 0)
			{
				str += _infos[i]._ch;
				str += ",";
				itoa(_infos[i]._count, buffer, 10);
				str += buffer;
				str += '\n';
			}
			fputs(str.c_str(), fInConfig);
			str.clear();
		}
		fclose(fInConfig);
		fclose(fOut);
		fclose(fIn);
		//监视窗口主要关注ch，code，pos
	}
	void UnComparess(const char* filename)//解压缩
	{
		//重建Huffman树
		//1.读配置文件
		string config = filename;
		config += ".config";
		FILE* fOutConfig = fopen(config.c_str(), "rb");
		assert(fOutConfig);
		string str;
		LongType charCount;

		while (_ReadLine(fOutConfig, str))
		{
			if (str.empty())
			{
				str += '\n';
			}
			else
			{
				_infos[(unsigned char)str[0]]._count = atoi(str.substr(2).c_str());//从第三个位置开始
				str.clear();
			}
		}
		str.clear();

		
		CharInfo invaild(0);
		HuffmanTree<CharInfo> tree(_infos, 256,invaild);
		charCount = tree.GetRoot()->_weight._count;
		string compressFileName = filename;
		compressFileName += ".huffman";
		FILE* fOut = fopen(compressFileName.c_str(), "rb");
		assert(fOut);
		string unCompressFile = filename;
		unCompressFile += ".uncompress";
		FILE* fIn = fopen(unCompressFile.c_str(), "wb");
		assert(fIn);
		int pos = 7;
		char ch = fgetc(fOut);
		HuffmanNode<CharInfo>* root = tree.GetRoot();
		HuffmanNode<CharInfo>* cur = root;
		while (1)
		{
			if (ch & (1 << pos))
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}
			if (cur->_left == NULL&&cur->_right == NULL)//因为huffman编码唯一所以可以这么写
			{
				fputc(cur->_weight._ch, fIn);
				cur = root;
				if (--charCount == 0)
				{
					break;
				}
			}
			if (pos-- == 0)
			{
				pos = 7;
				ch = fgetc(fOut);
			}
		}
		fclose(fIn);
	}

protected:
	void _GerenateHuffmanCode(HuffmanNode<CharInfo>* root, string code)//注意这里不能加&code，这样就不用在
	{																//返回上一层的时候再-‘0’
		if (root == NULL)
			return;
		if (root->_left)
		{
			_GerenateHuffmanCode(root->_left, code + '0');
		}
		if (root->_right)
		{
			_GerenateHuffmanCode(root->_right, code + '1');
		}
		if (root->_left == NULL&&root->_right == NULL)
		{
			_infos[root->_weight._ch]._code = code;
#ifdef _DEBUG_
			cout << root->_weight._ch << "->" << code << endl;
#endif//_DEBUG
		}
	}
	bool _ReadLine( FILE* fOut, string& str)
	{
		char ch = fgetc(fOut);
		if (feof(fOut))
		{
			return false;
		}
		while (!feof(fOut)&&ch != '\n')
		{
			str += ch;
			ch = fgetc(fOut);
		}
		return true;
	}

protected:
	CharInfo _infos[256];//直接定值法
};