#ifndef STRINGCOMPARE_H
#define STRINGCOMPARE_H

#include "rkr_gst_match.h"
#include "FileObj.h"
#include "StudentObj.h"
#include <fstream>
#include <stdlib.h>
#include <direct.h>

//正式进行字符串比较的函数
double stringCompare(string hwNum,StudentObj checkStu,StudentObj otherStu,FileObj file1,FileObj file2,int flag);
int testStringCompare(StudentObj otherStu,FileObj file1,FileObj file2);

#endif
