
#include <vector>
using namespace std;
//最多打包文件个数
#define MAX_FILE_COUNT  50
//最大路径字符长度

#define MAX_PATH   260

int	ACZip( vector<string> files,string zipname);

int	ACUnZip(string zipname, string path);
//文件头
struct FileHead
{
	unsigned int FileCount;//文件个数
	unsigned int FileLen[MAX_FILE_COUNT];//文件大小
	char FileName[MAX_FILE_COUNT][MAX_PATH];//文件名
};

class MyCab
{
	private:
		FileHead fh;//文件头
		char ObjectFilePathName[MAX_PATH];//生成打包文件位置及名称
	public:
	//无参数构造
	MyCab();
	public:
		//添加文件到包内
		void AddFile(string FilePathName);
		//设置打包输出文件
		void SetOutPutFile(char * OutFile);
		//获取文件大小(传入以二进制方式打开的文件指针)
		long GetFileSize(FILE *pf);
		//制作打包文件
		void DoMakeCAB();
		//解包(为了节省时间不写错误处理了,可以根据上面自己添加)
		void DoUnCAB(char *CabFilePathName,string path);
	private:
		//显示打包内文件信息
		void printCAB();
};

