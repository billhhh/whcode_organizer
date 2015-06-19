/**
 * 学生实体类
 * 
 * @author Bill Wang
 * 
 */
#ifndef STUDENTOBJ_H
#define STUDENTOBJ_H

#include "FileObj.h"
#include <vector>
using namespace std;

class StudentObj
{
public:
	vector<FileObj> fileList;
	string studentName;
	string studentId;
private:
};

#endif

