#include "Controller.h"
#include "Tools.h"
#include "xlsIO.h"

using namespace std;

void Controller::startCheck(QString excelPath,string homeworkPath,vector<string> stuNames)//stuNames的下标信息就就可以确定excel写入地方
{
	//开始检查哪些学生交了作业

	Tools tools;
	tools.getDirFilesPath(homeworkPath,fileNames);

	//填满fileNames
	for (int i=0;i<fileNames.size();i++)
	{
		//cout<<files.at(i)<<"\n";
		chineseFileNames.push_back( tools.getChinese(fileNames.at(i)) );
	}

	//test compareName()
	//compareName("afdsdfs_hello_sdfas#@!","hello");

	XlsIO xlsio;
	//对chineseFileNames中的每一项去找学生的每一项，看是不是有子串关系
	for (int i=0;i<chineseFileNames.size();i++)
	{
		for (int j=0;j<stuNames.size();j++)
		{
			//cout<<chineseFileNames.at(i)<<" "<<stuNames.at(j)<<"\n";
			if (compareName( chineseFileNames.at(i),stuNames.at(j)) )
			{
				//发现是子串关系
				cout<<"行数："<<j<<"\n";
				cout<<"是子串，"<<i+1<<"："<<stuNames.at(j)<<"\n";
				//写excel
				xlsio.xlsWriter(excelPath,j);

				break;
			}
		}
	}

	return;
}

bool Controller::compareName(string name1,string name2)
{
	string::size_type findResult = name1.find(name2);

	if (findResult != string::npos) //找到
		return true;
	else
		return false;
}