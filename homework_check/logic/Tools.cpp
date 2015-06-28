/**
 * 工具类实现
 * 
 * @author Bill Wang
 * 
 */
#include "Tools.h"

//传入Path和待检测学生，返回待检测学生信息和其他学生信息
bool Tools::getStudents(string batch,StudentObj &checkStu,vector <StudentObj> &otherStu)
{
	string xmlPath = findXmlPath(batch);
	vector<string> filesPath;
	vector<string> stuId;
	getDirFilesPath(xmlPath,filesPath,stuId); //获得XML绝对路径

	//这样处理，filesPath和stuId下标对应
	int filesSize=filesPath.size();

	for (int i=0;i<filesSize;i++)
	{
		StudentObj tmpStu;
		tmpStu.studentId = stuId.at(i);

		//送去xmlReader
		XmlReader xr;
		xr.XmlIO(filesPath.at(i),tmpStu);
		
		if (tmpStu.studentId.compare(checkStu.studentId) == 0)
		{
			//如果是待检测的同学
			checkStu.fileList=tmpStu.fileList;
		}else{
			otherStu.push_back(tmpStu);
		}
	}

	return true;
}

bool Tools::getAllStudentsNum(string batch,vector<StudentObj> &allStudents)
{
	string xmlPath = findXmlPath(batch);
	vector<string> filesPath;
	vector<string> stuId;
	getDirFilesPath(xmlPath,filesPath,stuId); //获得XML绝对路径

	//这样处理，filesPath和stuId下标对应
	int filesSize=filesPath.size();

	for (int i=0;i<filesSize;i++)
	{
		StudentObj tmpStu;
		tmpStu.studentId = stuId.at(i);

		//送去xmlReader
		XmlReader xr;
		xr.XmlIO(filesPath.at(i),tmpStu);

		allStudents.push_back(tmpStu);
	}

	return true;
}

//获得xml【文件夹】的绝对路径
string Tools::findXmlPath(string batch)
{
	string path = "C:\\pre_out\\";
	path.append(batch);
	return path;
}

//获得某文件夹下的所有文件的绝对路径
bool Tools::getDirFilesPath( string path, vector<string>& files ,vector <string> &stuId )
{
	//文件句柄
	long hFile   =   0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
	{
		do
		{
			//如果是目录,继续
			if((fileinfo.attrib &  _A_SUBDIR))
			{
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
					continue;
			}
			else
			{
				string tmp = fileinfo.name;
				tmp = tmp.substr(0,tmp.length()-4);  //截掉.xml后缀
				stuId.push_back(tmp);  //放入容器
				files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
			}
		}while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}else{
		return false;
	}

	return true;
}