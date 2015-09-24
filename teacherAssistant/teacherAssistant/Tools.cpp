#include "Tools.h"

using namespace std;

//获得中文子串
string Tools::getChinese(string inputStr)
{
	string result;
	for (int i=0;i<inputStr.size();i++)
	{
		if ( (int)(inputStr.at(i))<0 )
		{
			result.append(&inputStr.at(i),2);
			i++;
		}
	}
	return result;
}



//获得某文件夹下的所有文件名，包括文件夹名
bool Tools::getDirFilesPath( string folderPath, vector<string>& files)
{
	//文件句柄
	long hFile   =   0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if((hFile = _findfirst(p.assign(folderPath).append("\\*").c_str(),&fileinfo)) !=  -1)
	{
		do
		{
			//如果是目录,继续
			if((fileinfo.attrib &  _A_SUBDIR))
			{
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
				{
					//去掉父目录和当前目录
					files.push_back( fileinfo.name );
				}
			}
			else
			{
				files.push_back( fileinfo.name );
			}
		}while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}else{
		return false;
	}

	return true;
}