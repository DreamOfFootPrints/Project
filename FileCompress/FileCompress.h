#pragma once
#pragma warning (disable:4996)
#include"HuffmanTree.h"
#include<stdlib.h>
#include<string>

//ͳ���ַ�����
//����Huffman��
//����Huffman����
//��ȡԴ�ļ��ַ���ѹ��


#define _DEBUG_

typedef unsigned long long LongType;//�Ժ��޸���������ֱ���������޸ļ���


//һ���ַ���Ӧһ�����룬��ȻҪһ��һ���������ù�ϣ��������ӳ�䣨�ַ������룩������ʹ��unsigned char����Щ�Ǹ����Ļ���
//������Խ�磩
struct CharInfo
{
public:
	unsigned char _ch;//�ַ�.Ϊʲô�� unsigned ��Ϊ���ֱ����п��ܳ��ָ���
	LongType _count;//���ִ���
	string _code;//huffman code
public:
	CharInfo(LongType count = 0)//���캯����Ĭ�ϵĹ��캯����д����һ��ҪдĬ�Ϲ��캯��
		:_count(count)
		, _ch(0)
	{}

	//ע��const�Ķ���ʹ��const�ķ���
	bool operator!=(const CharInfo& info) const//���γ�Ա���������ı��Ա����
	{
		return _count != info._count;
	}

	LongType operator+(const CharInfo& info)const
	{
		return _count + info._count;
	}

	bool operator<(const CharInfo& info) const//���γ�Ա���������ı��Ա����
	{
		return _count < info._count;
	}
};


class FileCompress//�ļ�ѹ��
{
public:
	FileCompress()//���캯��
	{
		for (size_t i = 0; i < 256; i++)
		{
			_infos[i]._ch = i;//int��char��ת��������û������
			_infos[i]._count = 0;
		}
	}

public:
	void Compress(const char* filename)//ѹ��
	{
		assert(filename);
		//ͳ���ļ����ַ����ֵĴ���
		FILE* fOut = fopen(filename, "rb");
		assert(fOut);
		char ch = fgetc(fOut);//��Ϊunsigned char
		while (!feof(fOut))//EOFΪ-1
		{
			_infos[(unsigned char)ch]._count++;//ֱ�Ӷ�ַ��
			ch = fgetc(fOut);
		}
		//����Huffman��������ڵ�������ַ����ص����ַ�����������Huffman�������Բ�Ϊcount
		const CharInfo invalid(0);//�Ƿ�ֵ��ʹ�÷Ƿ�ֵ����Ϊ��1��256��ֵ���趼���죬��2���ж��޽ṹ
		HuffmanTree<CharInfo> tree(_infos, 256,invalid);
		//����Huffman Code
		string code;
		_GerenateHuffmanCode(tree.GetRoot(), code);//��ÿһ��_infoes[i]д���Ӧ��_code(huffman����)
		//ѹ��
		string compressFileName = filename;
		compressFileName += ".huffman";
		FILE* fIn = fopen(compressFileName.c_str(), "wb");//��һ���ֽھ���ѹ���ļ���д
		assert(fIn);
		//��ȡ�ļ����ҳ���Ӧ���ַ���Huffman���룬ת���ɶ�Ӧ��λ������ѹ��
		fseek(fOut, 0, SEEK_SET);//0Ϊ���λ��,�ص��ļ�ͷ��
		ch = fgetc(fOut);
		char value = 0;
		int pos = 0;
		while (!feof(fOut))
		{
			string& code = _infos[(unsigned char)ch]._code;//ֱ�Ӷ�ַ��
			for (size_t i = 0; i < code.size(); ++i)
			{
				value <<= 1;//�������ж���������8��
				if (code[i] == '1')
				{
					value |= 1;
				}
				//value <<= 1;//�������ж���������7�Σ�ֻ��һ��д��

				if (++pos == 8)
				{
					fputc(value, fIn);
					value = 0;
					pos = 0;
				}
			}
			ch = fgetc(fOut);
		}
		//�п��ܲ�������8������λ
		if (pos)
		{
			value =1<<(8 - pos);//��Ϊ�ٿص���bitλ���Բ�������Ϊ2������
			fputc(value, fIn);
		}
		//�����ļ���û�д������ܹ���Huffman��������дһ�������ļ���ͳ��ÿ���ַ����ֵĴ����������ѹ����ʱ���ؽ�Huffman��
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
		//���Ӵ�����Ҫ��עch��code��pos
	}
	void UnComparess(const char* filename)//��ѹ��
	{
		//�ؽ�Huffman��
		//1.�������ļ�
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
				_infos[(unsigned char)str[0]]._count = atoi(str.substr(2).c_str());//�ӵ�����λ�ÿ�ʼ
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
			if (cur->_left == NULL&&cur->_right == NULL)//��Ϊhuffman����Ψһ���Կ�����ôд
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
	void _GerenateHuffmanCode(HuffmanNode<CharInfo>* root, string code)//ע�����ﲻ�ܼ�&code�������Ͳ�����
	{																//������һ���ʱ����-��0��
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
	CharInfo _infos[256];//ֱ�Ӷ�ֵ��
};