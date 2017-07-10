#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<string.h>
#include<string>
#include<windows.h>
std::string GBKToUTF8(const std::string& strGBK)
{
	std::string strOutUTF8 = "";
	WCHAR * str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char * str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return strOutUTF8;
}
int main()
{
	while (1)
	{
		std::ifstream file;
		file.open("E:\\Apache2\\htdocs\\answer_list.out");
		if (!file)
		{
			_sleep(100);
		}
		else {
			std::cout << "YES";
			int num;
			file >> num;
			int word_num;
			if (num >= 10)word_num = 10;
			else word_num = num;
			std::ofstream out("E:\\Apache2\\htdocs\\test.html");
			out << "<html>\n<head>\n<meta charset=\"utf-8\">\n<title>"<<GBKToUTF8("中国人民大学信息学院检索系统")<<"</title>\n<style type=\"text/css\">" << std::endl;
			out << "body{\nmargin-left:60px;\nmargin-top:40px;\n}\nimg{ \n position: absolute;\n left:1000px;\ntop:50px;\n}\n</style>\n</head>" << std::endl;
			out << "<body>\n<img src=\"E:\\Apache2\\info.jpg\" id = img>" << std::endl;
			if(num > 0)out << "<p>"<<GBKToUTF8("共搜索到") << ": " << num << GBKToUTF8("条结果")<<"</p>" << std::endl;
			else out << "<p>" << GBKToUTF8("很抱歉没有在信息学院内网中找到相关内容") << std::endl;
			for (int i = 1; i <= word_num; i++)
			{
				int link_num;
				file >> link_num;
				std::string file_name = std::to_string(link_num);
				file_name = "E:\\Apache2\\新建文件夹\\test\\test\\lac3\\" + file_name + "\\u_to_k.txt";
				std::ifstream link_file;
				link_file.open(file_name.c_str());
				std::string url;
				link_file >> url;
				link_file.close();
				std::string title;
				file_name = std::to_string(link_num);
				file_name = "E:\\Apache2\\新建文件夹\\test\\test\\lac3\\" + file_name + "\\titx.txt";
				link_file.open(file_name.c_str());
				std::getline(link_file, title);
				std::string feature = "###";
				title = title.substr(0, title.find(feature));
				link_file.close();
				out << "<a href=\""<<url<<"\">" << title << "</a><br>";
				out << "<br>";
				out << "<br>";
			}
			out.close();
			file.close();
			_sleep(1000);
		}
	}
}
