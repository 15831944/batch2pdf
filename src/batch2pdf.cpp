/**
Protject: batch2pdf
Desc: ������ָ��Ŀ¼��(����Ŀ¼)���ļ����ɵ�һ��pdf�ļ���.
      �����Զ���Ŀ¼���ļ�������pdfĿ¼��ǩ�Ա���ת.

	  �������޶���֧�����������ļ�:
	 ".c",".cpp",".cc",".h",".hpp",".go",".java",".py", 
	 ",lua",".erl",".pl",".rs",".js",".php", ".rb"

	  ʹ�ÿ�Դ��:https://github.com/libharu
	  ��������ÿɲο�: http://blog.csdn.net/xcl168/article/details/48229079

Author: Xiong Chuan Liang (xcl_168@aliyun.com)
Date: 2015-9-9
Example:
	batch2pdf -dE:\soft_c\wdt-master\ -nwdt.pdf  -owdt_20150909
	batch2pdf -dD:\soft_c\leveldb-master\ -nleveldb.pdf -cen -oleveldb

	batch2pdf -dD:\soft_c\rocksdb-master\ -nRocksDBԴ��_20150909.pdf -oRocksDB
*/


#include <iostream>
#include <string>
#include "pdfcreater.h"

#if defined(_WIN32) || defined(_WIN64)
	#pragma comment(lib,"..\\x64\\Release\\LIBHPDF.lib")
	#pragma warning (disable: 4996)  
#endif

static void Usage() {
	const char usage = 
	fprintf(
		stderr,
		"Usage: batch2pdf command...\n"
		"   -d Ҫ����תPDF��Ŀ¼\n"
		"   -n pdf�ļ�����,������������תĿ¼��.\n"
		"   -c cn:֧�ּ���,en:��֧��Ӣ��,tw:֧�ַ���\n"
		"   -o pdf�ļ��е�Ŀ���ǩ��\n"
		"   -n һҳ������,Ĭ��Ϊ53\n"
		"   -l ÿ�и߶�,Ĭ��Ϊ15\n"
		"   -s �����С,Ĭ��Ϊ14\n"
		"   -b ҳβ�����С,Ĭ��Ϊ10\n"
		"   -h ����˵��\n"
		);
}

int main(int argc, char **argv)
{
	std::string path = "./";  // -d
	std::string destFileName = "xcl.pdf"; // -n
	std::string outline = "files"; //-o
	std::string temp,arg,argValue;

	for (int i = 1; i < argc; i++) {
		temp = argv[i];
		arg = temp.substr(0, 2);
		argValue = temp.substr(2);
		if (argValue.empty())continue;

		if (arg.compare("-d") == 0) {
			path = argValue;
		}
		else if (arg.compare("-n") == 0) {
			destFileName = argValue;
		}
		else if (arg.compare("-f") == 0) {
			if (argValue.compare("en") == 0) {
			   pdf::config::SetConfigLanguage(pdf::config::LANGUAGE::EN);
			}
			else if (argValue.compare("cn") == 0) {
				pdf::config::SetConfigLanguage(pdf::config::LANGUAGE::CN);
			}
			else if (argValue.compare("tw") == 0) {
				pdf::config::SetConfigLanguage(pdf::config::LANGUAGE::TW);
			}
		}
		else if (arg.compare("-o") == 0) {
			outline = argValue;
		}
		else if (arg.compare("-n") == 0) {
			pdf::config::SetConfigPageLineNum(std::stoi(argValue));
		}
		else if (arg.compare("-l") == 0) {
			pdf::config::SetConfigLineHeight(std::stoi(argValue));
		}
		else if (arg.compare("-s") == 0) {
			pdf::config::SetConfigPageFontSize(std::stoi(argValue));
		}
		else if (arg.compare("-b") == 0) {
			pdf::config::SetConfigFootbarFontSize(std::stoi(argValue));
		}
		else if (arg.compare("-h") == 0) {
			Usage();
		}
	}
	
	//������Ŀ¼�µ��ļ����ɵ�һ��pdf�ļ���
	pdf::merge::FileCreator(path, destFileName, outline);
		
	// ���÷���һ
    // pdf::merge::FileCreator(R"(D:\pdf\demo\)", "zj.pdf"); 

	// ���÷�����
	//pdf::merge::FileCreator(R"(D:\pdf\demo\)", "zj.pdf", "demo"); 

	return 0;
}
