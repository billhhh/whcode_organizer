#include "StringCompare.h"

double stringCompare(string hwNum, StudentObj checkStu,StudentObj otherStu,FileObj checkFile,FileObj otherFile, int flag)
{
	double sim;
	int copy_int, copy_int2;
	string str1,str2;
// 	str1 = "#include <stdio.h>#include <stdlib.h>#include <climits>void swap(int &a, int &b){int temp = a;	a = b;	b = temp;}void Max_HeapIFY(int data[],int length,int i);void Build_Max_Heap(int data[],int length);void HeapSort(int data[],int length);int main(){	int i;	int data[11] = {INT_MAX,5,3,17,10,84,19,6,22,9,35};	HeapSort(data,10);for(i=1;i<11;++i)printf(%d ,data[i]);printf(\n);return 0;}void Max_HeapIFY(int data[],int length,int i){int left = 2 * i;int right = left + 1;	int largest;if(left <= length && data[left] > data[i])largest = left;else	largest = i;if(right <= length && data[right] > data[largest])	largest = right;if(largest != i){swap(data[largest], data[i]);		Max_HeapIFY(data, length, largest);}}void Build_Max_Heap(int data[],int length){int i;	for(i=length/2;i>0;i--)	Max_HeapIFY(data,length,i);}void HeapSort(int data[],int length){Build_Max_Heap(data,length);//堆是一个数组，在实现堆排序函数时，以变量 ix 来标志尚未排好序的部分。	int ix =length;	while(ix > 1)	{swap(data[1], data[ix]);-- ix;	Max_HeapIFY(data, ix, 1);//将剩余的部分构造成最大堆}}";
// 	str1 = "#include <stdio.h>#include <stdlib.h>#include <climits>void swap(long &a, long &b){long temp = a;	a = b;	b = temp;}void Max_HeapIFY(long date[],long length,long i);void Build_Max_Heap(long date[],long length);void HeapSort(long date[],long length);long main(){	long i;	long date[11] = {long_MAX,5,3,17,10,84,19,6,22,9,35};	HeapSort(date,10);for(i=1;i<11;++i)prlongf(%d ,date[i]);prlongf(\n);return 0;}void Max_HeapIFY(long date[],long length,long i){long left = 2 * i;long right = left + 1;	long largest;if(left <= length && date[left] > date[i])largest = left;else	largest = i;if(right <= length && date[right] > date[largest])	largest = right;if(largest != i){swap(date[largest], date[i]);		Max_HeapIFY(date, length, largest);}}void Build_Max_Heap(long date[],long length){long i;	for(i=length/2;i>0;i--)	Max_HeapIFY(date,length,i);}void HeapSort(long date[],long length){Build_Max_Heap(date,length);//堆是一个数组，在实现堆排序函数时，以变量 ix 来标志尚未排好序的部分。	long ix =length;	while(ix > 1)	{swap(date[1], date[ix]);-- ix;	Max_HeapIFY(date, ix, 1);//将剩余的部分构造成最大堆}}";
// 	str2 = "kfd#include <stdio.h>#include <stdlib.h>#include <climits>void swap(long &a, long &b){long temp = a;	a = b;	b = temp;}void Max_HeapIFY(long date[],long length,long i);void Build_Max_Heap(long date[],long length);void HeapSort(long date[],long length);long main(){	long i;	long date[11] = {long_MAX,5,3,17,10,84,19,6,22,9,35};	HeapSort(date,10);for(i=1;i<11;++i)prlongf(%d ,date[i]);prlongf(\n);return 0;}void Max_HeapIFY(long date[],long length,long i){long left = 2 * i;long right = left + 1;	long largest;if(left <= length && date[left] > date[i])largest = left;else	largest = i;if(right <= length && date[right] > date[largest])	largest = right;if(largest != i){swap(date[largest], date[i]);		Max_HeapIFY(date, length, largest);}}void Build_Max_Heap(long date[],long length){long i;	for(i=length/2;i>0;i--)	Max_HeapIFY(date,length,i);}void HeapSort(long date[],long length){Build_Max_Heap(date,length);//堆是一个数组，在实现堆排序函数时，以变量 ix 来标志尚未排好序的部分。	long ix =length;	while(ix > 1)	{swap(date[1], date[ix]);-- ix;	Max_HeapIFY(date, ix, 1);//将剩余的部分构造成最大堆}}";

	str1=checkFile.getContent();
	str2=otherFile.getContent();

	//cout<<"str1 == "<<str1<<endl;


	string filePath;

	filePath = "c:\\StrCompare\\";
	filePath.append(hwNum);
	filePath.append("\\");
	filePath.append(checkStu.studentId);
	filePath.append("\\");
	filePath.append(otherStu.studentId);

	filePath.append("-");
	filePath.append(checkFile.getFileName());
	filePath.append(".");
	filePath.append(checkFile.getFileType());
	filePath.append("-");
	filePath.append(otherFile.getFileName());
	filePath.append(".");
	filePath.append(otherFile.getFileType());
	filePath.append("@.txt");//代表到尾部了


	//判断文件是否已经存在，如果存在另作标识
	fstream _isFile;
	_isFile.open(filePath,ios::in);
	if(_isFile)
	{
		//文件已经存在，代表有缓存了，不处理
		cout<<filePath<<"已有缓存，返回\n"<<endl;
		return -1;
	}
	cout<<"filePath: "<<filePath<<endl;
	//system("pause");

	//进入核心算法
	if(flag == 0)
	{
		copy_int = 30;
		copy_int2= 31;
	}
	else if(flag == 1)
	{
		copy_int = 80;
		copy_int2= 81;
	}

	RKR_GST_Match rkr_gst(str1, str2, copy_int);
	rkr_gst.beginMatch(copy_int2);
	int sum = 0;
	for (vector<Match>::iterator it = rkr_gst.matches.begin(); it != rkr_gst.matches.end(); ++it)
	{
		sum += it->len;
	}
	sim=(sum * 2.0 /(str1.length() + str2.length()));
	fstream file;
	file.open(filePath, ios::out );
	file<<sim<<endl; //文件中放入相识度
	for (vector<Match>::iterator it = rkr_gst.matches.begin(); it != rkr_gst.matches.end(); ++it)
	{
		file<<it->m<<"-"<<it->n<<"-"<<it->len<<"\n";
	}

	cout<<"\n\nthe length  of the first string is : "<<str1.length()<<"\n";	
	cout<<"the length  of the second string is : "<<str2.length()<<"\n";
	cout<<"The total similar length of these two strings is : " <<sum<<"\n";
	cout<<"The similarity of the two string is : " <<(sum * 2.0 /(str1.length() + str2.length()) )<<"\n\n";
	

	//system("pause");
	return sim;
}




//只做测试只用
int testStringCompare(StudentObj otherStu,FileObj checkFile,FileObj otherFile)
{
	string str1,str2;
	// 	str1 = "#include <stdio.h>#include <stdlib.h>#include <climits>void swap(int &a, int &b){int temp = a;	a = b;	b = temp;}void Max_HeapIFY(int data[],int length,int i);void Build_Max_Heap(int data[],int length);void HeapSort(int data[],int length);int main(){	int i;	int data[11] = {INT_MAX,5,3,17,10,84,19,6,22,9,35};	HeapSort(data,10);for(i=1;i<11;++i)printf(%d ,data[i]);printf(\n);return 0;}void Max_HeapIFY(int data[],int length,int i){int left = 2 * i;int right = left + 1;	int largest;if(left <= length && data[left] > data[i])largest = left;else	largest = i;if(right <= length && data[right] > data[largest])	largest = right;if(largest != i){swap(data[largest], data[i]);		Max_HeapIFY(data, length, largest);}}void Build_Max_Heap(int data[],int length){int i;	for(i=length/2;i>0;i--)	Max_HeapIFY(data,length,i);}void HeapSort(int data[],int length){Build_Max_Heap(data,length);//堆是一个数组，在实现堆排序函数时，以变量 ix 来标志尚未排好序的部分。	int ix =length;	while(ix > 1)	{swap(data[1], data[ix]);-- ix;	Max_HeapIFY(data, ix, 1);//将剩余的部分构造成最大堆}}";
// 	str1 = "#include <stdio.h>#include <stdlib.h>#include <climits>void swap(long &a, long &b){long temp = a;	a = b;	b = temp;}void Max_HeapIFY(long date[],long length,long i);void Build_Max_Heap(long date[],long length);void HeapSort(long date[],long length);long main(){	long i;	long date[11] = {long_MAX,5,3,17,10,84,19,6,22,9,35};	HeapSort(date,10);for(i=1;i<11;++i)prlongf(%d ,date[i]);prlongf(\n);return 0;}void Max_HeapIFY(long date[],long length,long i){long left = 2 * i;long right = left + 1;	long largest;if(left <= length && date[left] > date[i])largest = left;else	largest = i;if(right <= length && date[right] > date[largest])	largest = right;if(largest != i){swap(date[largest], date[i]);		Max_HeapIFY(date, length, largest);}}void Build_Max_Heap(long date[],long length){long i;	for(i=length/2;i>0;i--)	Max_HeapIFY(date,length,i);}void HeapSort(long date[],long length){Build_Max_Heap(date,length);//堆是一个数组，在实现堆排序函数时，以变量 ix 来标志尚未排好序的部分。	long ix =length;	while(ix > 1)	{swap(date[1], date[ix]);-- ix;	Max_HeapIFY(date, ix, 1);//将剩余的部分构造成最大堆}}";
// 	str2 = "kfd#include <stdio.h>#include <stdlib.h>#include <climits>void swap(long &a, long &b){long temp = a;	a = b;	b = temp;}void Max_HeapIFY(long date[],long length,long i);void Build_Max_Heap(long date[],long length);void HeapSort(long date[],long length);long main(){	long i;	long date[11] = {long_MAX,5,3,17,10,84,19,6,22,9,35};	HeapSort(date,10);for(i=1;i<11;++i)prlongf(%d ,date[i]);prlongf(\n);return 0;}void Max_HeapIFY(long date[],long length,long i){long left = 2 * i;long right = left + 1;	long largest;if(left <= length && date[left] > date[i])largest = left;else	largest = i;if(right <= length && date[right] > date[largest])	largest = right;if(largest != i){swap(date[largest], date[i]);		Max_HeapIFY(date, length, largest);}}void Build_Max_Heap(long date[],long length){long i;	for(i=length/2;i>0;i--)	Max_HeapIFY(date,length,i);}void HeapSort(long date[],long length){Build_Max_Heap(date,length);//堆是一个数组，在实现堆排序函数时，以变量 ix 来标志尚未排好序的部分。	long ix =length;	while(ix > 1)	{swap(date[1], date[ix]);-- ix;	Max_HeapIFY(date, ix, 1);//将剩余的部分构造成最大堆}}";
	str1 = "⊙|题目|:|基于|matlab| |c|-|mex|的|维诺图|实现|⊙|学院|：|软件|学院|⊙|老师|：|汤德佑|⊙|学生|姓名|：|王琥|⊙|学号|：|201421031134|⊙| | | | | |（|附|：|可执行文件|的|使用|说明|见|附录|）|⊙|总体设计|⊙|名称|	|基于|matlab| |c|-|mex|的|维诺图|实现|⊙|设计|⊙|目的|	|1.| | |合理|设计|数据结构|，|应用|所学|算法|编写|维诺图|程序|，|并|有|良好|的|图形化|界面|；|⊙|2.| | |将|所学|的|c|语言|知识|和|matlab|结合|起来|，|形象化|的|解决|实际|问题|；|⊙|3.| | |培养|综合|运用|专业知识|，|解决|实际|问题|的|能力|。|⊙|编程|⊙|环境|	|pc| |+| |win|7|；|⊙|安装|vs|2010|，|matlab|等|开发工具|。|⊙|任务|⊙|要求|	|用|c|语言|编写|维诺图|算法|；|⊙|实现|鼠标|点击|的|交互式|界面|（|鼠标|左键|输入|点|集|，|右键|结束|输入|）|；|⊙|实现|交互式|界面|与|c|文件|的|c|-|mex|接口|对接|。|⊙|一|、|问题|描述|⊙|为了|高质量|的|完成|老师|交给|的|维诺图|编写|任务|，|我|查阅|了|很多|资料|，|在|周培德|的|《|计算|几何|——|算法|设计|与|分析|》|一|书|中|有|一个|很|经典|的|比喻|：|假设|图|上有|n|个|点|，|如果|把|每个|点|看做|一个|火源|，|如果|把|这|n|个|点|同时|点燃|，|并以|相同|的|速度|向|各个|方向|蔓延|，|那么|燃烧|熄灭|处所|形成|的|图|便是|voronoi|图|。|⊙|这|是|我|觉得|最|生动|的|一个|比喻|，|通俗|的|理解|维诺图|就是|空间|或者|平面|的|点|集中|，|离|一个|定点|最近|的|所有|点|的|集合|。|如果|用|较|严格|一些|的|定义|：|对于|一个|空间| |m|，|假定|其中|存在|着|一个|结点|集| |s|；|s| |中|的|任意|一个|结点|都|可以|对|其|周围环境|——|属于|空间| |m| |的|点|集|，|施加影响|；|对于|空间| |m| |中|的|一组|点|集|，|在| |s| |的|所有|结|点中|，|它们|受|一|结点| |p| |的|影响|最为|强烈|，|那么|这|组|点|集|就|构成|了结|点| |p| |的|一个|作用域|。|⊙|二|、|算法|设计|与|分析|⊙|既然|要|设计|算法|解决|维诺图|问题|，|就|需要|对|维诺图|的|特性|进行|进一步|的|分析|。|据|分析|，|维诺图|的|形成|基本上|就是|三角形|网|的|外心|连线|，|这样|问题|就|转化|为|求|三角形|网络|。|我|决定|采用|delaunay|三角|剖|分|算法|进行|三角形|网络|的|构建|。|delaunay|剖|分|具有|以下|一些|优秀|的|特性|：|⊙|1.|最|接近|：|以|最近|的|三点|形成|三角形|，|且|各|线段|(|三角形|的|边|)|皆|不|相交|。|⊙|2.|唯一性|：|不论|从|区域|何处|开始|构建|，|最终|都|将|得到|一致|的|结果|。|⊙|3.|最优性|：|任意|两个|相邻|三角形|形成|的|凸|四边形|的|对角线|如果|可以|互换|的话|，|那么|两个|三角形|六个|内角|中|最小|的|角度|不会|变大|。|⊙|4.|最|规则|：|如果|将|三角网|中|的|每个|三角形|的|最小|角|进行|升序|排列|，|则|delaunay|三角网|的|排列|得到|的|数值|最大|。|⊙|5.|区域性|：|新增|、|删除|、|移动|某|一个|顶点|时|只|会|影响|临近|的|三角形|。|⊙|6.四点|不同|圆|特性|。|⊙|（|1|）|失败|的|经历|⊙|我|开始|根据|以上|特性|写出|了|一个|三角形|刨|分|的|暴力|算法|，|算法|的|思想|很|简单|，|用户|输入|的|所有|点|集中|每|三个|点|都|形成|一个|三角形|，|然后|判断|每个|三角形|和|除去|顶点|的|所有|点|是不是|同|圆|，|如果|同一个|圆|就|去掉|这个|三角形|。|⊙|这个|算法|根据|定义|得出|，|正确性|是|毋庸置疑|的|，|但是|算法|的|效率|令人堪忧|，|算法|在|点数|较少|的|情况|下|可以|很|迅速|的|得出|答案|，|点数|一旦|增多|，|处理速度|就|急速|变慢|。|我|测试|是|25个|点|就要|等|几十秒|。|。|。|原因|也|很|简单|，|因为|这个|算法|的|两步|：|1|）|构成|所有|三角形|，|这|是|一个|o|（|n|^|3|）|的|一个|复杂度| | |2|）|判断|每个|三角形|的|有效性|是|一个|o|（|n|^|2|）|的|复杂度|，|这样|复杂度|就|很|高|了|。|⊙|（|2|）|重新|编码|⊙|吸取|暴力|法|失败|的|经历|之后|，|我|思考|了|另外|一种|比较|高效|的|算法|。|算法|的|基本|步骤|是|：|⊙|1|、|构造|一个|超级|三角形|，|包含|所有|散|点|（|这些|散|点|是|用户|一个个|输入|的|）|，|放入|三角形|链表|。|⊙|2|、|将|点|集中|的|散|点|依次|插入|，|在|三角形|链表|中|找出|外接圆|包含|插入|点|的|三角形|（|称为|该|点|的|影响|三角形|）|；|这里|有|一个|很|重要|的|细节|处理|，|将|所有|影响|三角形|的|边|存入|一个|边|数组|，|删除|影响|三角形|的|公共|边|，|将|插入|点|同|影响|三角形|的|全部|顶点|连接起来|，|完成|一个点|在|delaunay|三角形|链表|中|的|插入|。|⊙|3|、|优化|三角形|，|并|将|形成|的|三角形|放入|delaunay|三角形|链表|。|⊙|4|、|循环|执行|上述|第2步|，|直到|所有|散|点|插入|完毕|。|⊙|5|、|连接|外心|，|形成|维诺图|。|⊙|这|一|算法|的|关键|的|第2步|图示|如下|：|⊙|（|3|）|算法|复杂度|分析|⊙|算法|主要|的|耗时|步骤|是|在|第2步|，|找出|新|插入|点|的|影响|三角形|需要|o|（|n|）|的|复杂度|；|将|所有|影响|三角形|的|边|存入|一个|边|数组|，|删除|影响|三角形|的|公共|边|这个|需要|o|（|n|^|2|）|的|复杂度|。|综合|来说|，|这个|算法|的|时间|复杂度|是|o|（|n|^|2|）|。|⊙|三|、|具体|代码|实现|⊙|（|1|）|变量|定义|⊙|为了|代码运行|的|有|更快|的|速度|，|我|使用|了|ansi| |c|编写|，|所有|数据结构|都|是|自己|定义|，|没有|使用|任何|c|+|+|的|stl|或者|模板|类|。|使用|数组|定义|，|虽然|会|使用|多一些|空间|，|但是|都|是|采用|下标|查找|的|方式|，|在|o|（|1|）|时间|内|直接|定位|，|速度|的确|得到|了|不错|的|提升|。|⊙|回想|编码|的|整个|过程|，|虽然|用|自己|定义|的|数据结构|很|辛苦|，|但是|收获|良多|。|⊙|实现|过程|中|各|变量|的|定义|说明|如下|：|⊙| | |1|）|结构|体|定义|⊙|typedef| |struct| | | | | | | | |x|;|	|	|	| | | | |y|;|⊙|}|point|;|⊙|typedef| |struct| | | | | | | | | | | | |start|,|end|;|⊙|	| |left|;|⊙|	|int| |right|;|⊙|}|edge|;|⊙|typedef| |struct|	| |a|,|b|,|c|;|⊙|	| |center|;|⊙|	|double| |radius|;| |isvalid|;| | |2|）|变量|定义|⊙|triangle| |triangle|[|]|;| | | |point|[|]|;|	| | | |pcnt|=|0|;| |tricnt|=|0|;| |tmpafftri|[|]|;| | | |affectedtricnt|=|0|;| | | | |affedgestart|[|]|;| |affedgeend|[|]|;| | | |outtri|[|]|;| | | |outtricnt|=|0|;| | | | |edge|[|]|;| | | |edgecnt|=|0|;|	| |init|(|)|;|	|	|	|	| |distance|(|point| |a|,|point| |b|)|;|	| | | |minicircle|(|point| |*|p|,|point|&amp;| | | |center|,|double|&amp;| | | |radius|)|;| | | | |freshtri|(|int| |sub|)|;| | | | | | | | | | | | |isaffected|(|int| |n|,|int| |i|)|;| | | | | | | | |storeaffedge|(|int| |n|)|;| | | | | | | | | |pointprocess|(|int| |n|)|;|	|	| | | | | |storenewtri|(|int| |n|)|;| | | | | | | | | | |offsuptri|(|)|;| | | | | | | | | | | | | | | | |initedge|(|)|;|	|	|	| | | | | |findedgetri|(|)|;| | | | | | | | | | | | | | |mexfunction|(|int| |nlhs|,| |mxarray| |*|plhs|[|]|,| |int| |nrhs|,| |const| |mxarray| |*|prhs|[|]|)|⊙|功能|说明|：|进行|c|文件|与|matlab|接口|的|实现|⊙|参数|说明|：|⊙|int| |nlhs|:|函数|输出|参数|的|个数|⊙|mxarray| |*|plhs|[|]|:|输出|参数|为|mxarray|结构|的|指针|数组|变量|⊙|int| |nrhs|:|函数|输入|参数|的|个数|⊙|const| |mxarray| |*|prhs|[|]|:|输入|参数|为|mxarray|结构|的|指针|数组|变量|⊙|2|）|pn|=| |mxgetpr|(|prhs|[|0|]|)|⊙|功能|说明|：|获取数据|数组|中|实数|部|的|指针|赋|给|pn|，|代表|获取|所有|点数|⊙|(|3|)| |plhs|[|0|]| |=| |mxcreatedoublematrix|(|outtricnt|*|3|*|2|,| |1|,| |mxreal|)|⊙| | | |y| |=| |mxgetpr|(|plhs|[|0|]|)|;|⊙|功能|说明|：|获取数据|数组|中|实数|部|的|指针|赋|给|y|⊙|plhs|[|1|]| |=| |mxcreatedoublematrix|(|1|,| |1|,| |mxreal|)|;|⊙|y|1| |=| |mxgetpr|(|plhs|[|1|]|)|;| | | |=| |mxcreatedoublematrix|(|edgecnt|*|2|*|2|,| |1|,| |mxreal|)|;|	| | |=| |mxgetpr|(|plhs|[|2|]|)|;| | | |=| |mxcreatedoublematrix|(|1|,| |1|,| |mxreal|)|;|⊙|y|3| |=| |mxgetpr|(|plhs|[|3|]|)|;| | | |r|2013|a| |win|64|的|机器|上|是|直接|跑|不|起来|的|，|需要|有|matlab| |r|2013|a| |win|64|的|runtime|库|才|行|。|。|⊙|这样|就|有|两种|方法|：|⊙|直接|安装|matlab| |r|2013|a| |win|64| |bit|的|程序|，|执行|mst|包|里面|的|dots|.|exe|或者|直接|在|matlab|界面|下|run| |dots|.|m|文件|都|可以|。|⊙|安装|mcrinstaller|.|exe|（|一定|要|matlab| |r|2013|a| |win|64| |bit|）|，|然后|就|可以|运行|mst|包|里面|的|dots|.|exe|了|。|⊙|如果|没有|mcrinstaller|.|exe|的|程序|（|413|mb|）|，|我|已经|上|传到|360|云盘|，|地址|是|：|http|:| | |提取|码| |1249|，|提供|下载|。|⊙|2|⊙|";
	str2 = "asf⊙|题目|:|基于|matlab| |c|-|mex|的|维诺图|实现|⊙|学院|：|软件|学院|⊙|老师|：|汤德佑|⊙|学生|姓名|：|王琥|⊙|学号|：|201421031134|⊙| | | | | |（|附|：|可执行文件|的|使用|说明|见|附录|）|⊙|总体设计|⊙|名称|	|基于|matlab| |c|-|mex|的|维诺图|实现|⊙|设计|⊙|目的|	|1.| | |合理|设计|数据结构|，|应用|所学|算法|编写|维诺图|程序|，|并|有|良好|的|图形化|界面|；|⊙|2.| | |将|所学|的|c|语言|知识|和|matlab|结合|起来|，|形象化|的|解决|实际|问题|；|⊙|3.| | |培养|综合|运用|专业知识|，|解决|实际|问题|的|能力|。|⊙|编程|⊙|环境|	|pc| |+| |win|7|；|⊙|安装|vs|2010|，|matlab|等|开发工具|。|⊙|任务|⊙|要求|	|用|c|语言|编写|维诺图|算法|；|⊙|实现|鼠标|点击|的|交互式|界面|（|鼠标|左键|输入|点|集|，|右键|结束|输入|）|；|⊙|实现|交互式|界面|与|c|文件|的|c|-|mex|接口|对接|。|⊙|一|、|问题|描述|⊙|为了|高质量|的|完成|老师|交给|的|维诺图|编写|任务|，|我|查阅|了|很多|资料|，|在|周培德|的|《|计算|几何|——|算法|设计|与|分析|》|一|书|中|有|一个|很|经典|的|比喻|：|假设|图|上有|n|个|点|，|如果|把|每个|点|看做|一个|火源|，|如果|把|这|n|个|点|同时|点燃|，|并以|相同|的|速度|向|各个|方向|蔓延|，|那么|燃烧|熄灭|处所|形成|的|图|便是|voronoi|图|。|⊙|这|是|我|觉得|最|生动|的|一个|比喻|，|通俗|的|理解|维诺图|就是|空间|或者|平面|的|点|集中|，|离|一个|定点|最近|的|所有|点|的|集合|。|如果|用|较|严格|一些|的|定义|：|对于|一个|空间| |m|，|假定|其中|存在|着|一个|结点|集| |s|；|s| |中|的|任意|一个|结点|都|可以|对|其|周围环境|——|属于|空间| |m| |的|点|集|，|施加影响|；|对于|空间| |m| |中|的|一组|点|集|，|在| |s| |的|所有|结|点中|，|它们|受|一|结点| |p| |的|影响|最为|强烈|，|那么|这|组|点|集|就|构成|了结|点| |p| |的|一个|作用域|。|⊙|二|、|算法|设计|与|分析|⊙|既然|要|设计|算法|解决|维诺图|问题|，|就|需要|对|维诺图|的|特性|进行|进一步|的|分析|。|据|分析|，|维诺图|的|形成|基本上|就是|三角形|网|的|外心|连线|，|这样|问题|就|转化|为|求|三角形|网络|。|我|决定|采用|delaunay|三角|剖|分|算法|进行|三角形|网络|的|构建|。|delaunay|剖|分|具有|以下|一些|优秀|的|特性|：|⊙|1.|最|接近|：|以|最近|的|三点|形成|三角形|，|且|各|线段|(|三角形|的|边|)|皆|不|相交|。|⊙|2.|唯一性|：|不论|从|区域|何处|开始|构建|，|最终|都|将|得到|一致|的|结果|。|⊙|3.|最优性|：|任意|两个|相邻|三角形|形成|的|凸|四边形|的|对角线|如果|可以|互换|的话|，|那么|两个|三角形|六个|内角|中|最小|的|角度|不会|变大|。|⊙|4.|最|规则|：|如果|将|三角网|中|的|每个|三角形|的|最小|角|进行|升序|排列|，|则|delaunay|三角网|的|排列|得到|的|数值|最大|。|⊙|5.|区域性|：|新增|、|删除|、|移动|某|一个|顶点|时|只|会|影响|临近|的|三角形|。|⊙|6.四点|不同|圆|特性|。|⊙|（|1|）|失败|的|经历|⊙|我|开始|根据|以上|特性|写出|了|一个|三角形|刨|分|的|暴力|算法|，|算法|的|思想|很|简单|，|用户|输入|的|所有|点|集中|每|三个|点|都|形成|一个|三角形|，|然后|判断|每个|三角形|和|除去|顶点|的|所有|点|是不是|同|圆|，|如果|同一个|圆|就|去掉|这个|三角形|。|⊙|这个|算法|根据|定义|得出|，|正确性|是|毋庸置疑|的|，|但是|算法|的|效率|令人堪忧|，|算法|在|点数|较少|的|情况|下|可以|很|迅速|的|得出|答案|，|点数|一旦|增多|，|处理速度|就|急速|变慢|。|我|测试|是|25个|点|就要|等|几十秒|。|。|。|原因|也|很|简单|，|因为|这个|算法|的|两步|：|1|）|构成|所有|三角形|，|这|是|一个|o|（|n|^|3|）|的|一个|复杂度| | |2|）|判断|每个|三角形|的|有效性|是|一个|o|（|n|^|2|）|的|复杂度|，|这样|复杂度|就|很|高|了|。|⊙|（|2|）|重新|编码|⊙|吸取|暴力|法|失败|的|经历|之后|，|我|思考|了|另外|一种|比较|高效|的|算法|。|算法|的|基本|步骤|是|：|⊙|1|、|构造|一个|超级|三角形|，|包含|所有|散|点|（|这些|散|点|是|用户|一个个|输入|的|）|，|放入|三角形|链表|。|⊙|2|、|将|点|集中|的|散|点|依次|插入|，|在|三角形|链表|中|找出|外接圆|包含|插入|点|的|三角形|（|称为|该|点|的|影响|三角形|）|；|这里|有|一个|很|重要|的|细节|处理|，|将|所有|影响|三角形|的|边|存入|一个|边|数组|，|删除|影响|三角形|的|公共|边|，|将|插入|点|同|影响|三角形|的|全部|顶点|连接起来|，|完成|一个点|在|delaunay|三角形|链表|中|的|插入|。|⊙|3|、|优化|三角形|，|并|将|形成|的|三角形|放入|delaunay|三角形|链表|。|⊙|4|、|循环|执行|上述|第2步|，|直到|所有|散|点|插入|完毕|。|⊙|5|、|连接|外心|，|形成|维诺图|。|⊙|这|一|算法|的|关键|的|第2步|图示|如下|：|⊙|（|3|）|算法|复杂度|分析|⊙|算法|主要|的|耗时|步骤|是|在|第2步|，|找出|新|插入|点|的|影响|三角形|需要|o|（|n|）|的|复杂度|；|将|所有|影响|三角形|的|边|存入|一个|边|数组|，|删除|影响|三角形|的|公共|边|这个|需要|o|（|n|^|2|）|的|复杂度|。|综合|来说|，|这个|算法|的|时间|复杂度|是|o|（|n|^|2|）|。|⊙|三|、|具体|代码|实现|⊙|（|1|）|变量|定义|⊙|为了|代码运行|的|有|更快|的|速度|，|我|使用|了|ansi| |c|编写|，|所有|数据结构|都|是|自己|定义|，|没有|使用|任何|c|+|+|的|stl|或者|模板|类|。|使用|数组|定义|，|虽然|会|使用|多一些|空间|，|但是|都|是|采用|下标|查找|的|方式|，|在|o|（|1|）|时间|内|直接|定位|，|速度|的确|得到|了|不错|的|提升|。|⊙|回想|编码|的|整个|过程|，|虽然|用|自己|定义|的|数据结构|很|辛苦|，|但是|收获|良多|。|⊙|实现|过程|中|各|变量|的|定义|说明|如下|：|⊙| | |1|）|结构|体|定义|⊙|typedef| |struct| | | | | | | | |x|;|	|	|	| | | | |y|;|⊙|}|point|;|⊙|typedef| |struct| | | | | | | | | | | | |start|,|end|;|⊙|	| |left|;|⊙|	|int| |right|;|⊙|}|edge|;|⊙|typedef| |struct|	| |a|,|b|,|c|;|⊙|	| |center|;|⊙|	|double| |radius|;| |isvalid|;| | |2|）|变量|定义|⊙|triangle| |triangle|[|]|;| | | |point|[|]|;|	| | | |pcnt|=|0|;| |tricnt|=|0|;| |tmpafftri|[|]|;| | | |affectedtricnt|=|0|;| | | | |affedgestart|[|]|;| |affedgeend|[|]|;| | | |outtri|[|]|;| | | |outtricnt|=|0|;| | | | |edge|[|]|;| | | |edgecnt|=|0|;|	| |init|(|)|;|	|	|	|	| |distance|(|point| |a|,|point| |b|)|;|	| | | |minicircle|(|point| |*|p|,|point|&amp;| | | |center|,|double|&amp;| | | |radius|)|;| | | | |freshtri|(|int| |sub|)|;| | | | | | | | | | | | |isaffected|(|int| |n|,|int| |i|)|;| | | | | | | | |storeaffedge|(|int| |n|)|;| | | | | | | | | |pointprocess|(|int| |n|)|;|	|	| | | | | |storenewtri|(|int| |n|)|;| | | | | | | | | | |offsuptri|(|)|;| | | | | | | | | | | | | | | | |initedge|(|)|;|	|	|	| | | | | |findedgetri|(|)|;| | | | | | | | | | | | | | |mexfunction|(|int| |nlhs|,| |mxarray| |*|plhs|[|]|,| |int| |nrhs|,| |const| |mxarray| |*|prhs|[|]|)|⊙|功能|说明|：|进行|c|文件|与|matlab|接口|的|实现|⊙|参数|说明|：|⊙|int| |nlhs|:|函数|输出|参数|的|个数|⊙|mxarray| |*|plhs|[|]|:|输出|参数|为|mxarray|结构|的|指针|数组|变量|⊙|int| |nrhs|:|函数|输入|参数|的|个数|⊙|const| |mxarray| |*|prhs|[|]|:|输入|参数|为|mxarray|结构|的|指针|数组|变量|⊙|2|）|pn|=| |mxgetpr|(|prhs|[|0|]|)|⊙|功能|说明|：|获取数据|数组|中|实数|部|的|指针|赋|给|pn|，|代表|获取|所有|点数|⊙|(|3|)| |plhs|[|0|]| |=| |mxcreatedoublematrix|(|outtricnt|*|3|*|2|,| |1|,| |mxreal|)|⊙| | | |y| |=| |mxgetpr|(|plhs|[|0|]|)|;|⊙|功能|说明|：|获取数据|数组|中|实数|部|的|指针|赋|给|y|⊙|plhs|[|1|]| |=| |mxcreatedoublematrix|(|1|,| |1|,| |mxreal|)|;|⊙|y|1| |=| |mxgetpr|(|plhs|[|1|]|)|;| | | |=| |mxcreatedoublematrix|(|edgecnt|*|2|*|2|,| |1|,| |mxreal|)|;|	| | |=| |mxgetpr|(|plhs|[|2|]|)|;| | | |=| |mxcreatedoublematrix|(|1|,| |1|,| |mxreal|)|;|⊙|y|3| |=| |mxgetpr|(|plhs|[|3|]|)|;| | | |r|2013|a| |win|64|的|机器|上|是|直接|跑|不|起来|的|，|需要|有|matlab| |r|2013|a| |win|64|的|runtime|库|才|行|。|。|⊙|这样|就|有|两种|方法|：|⊙|直接|安装|matlab| |r|2013|a| |win|64| |bit|的|程序|，|执行|mst|包|里面|的|dots|.|exe|或者|直接|在|matlab|界面|下|run| |dots|.|m|文件|都|可以|。|⊙|安装|mcrinstaller|.|exe|（|一定|要|matlab| |r|2013|a| |win|64| |bit|）|，|然后|就|可以|运行|mst|包|里面|的|dots|.|exe|了|。|⊙|如果|没有|mcrinstaller|.|exe|的|程序|（|413|mb|）|，|我|已经|上|传到|360|云盘|，|地址|是|：|http|:| | |提取|码| |1249|，|提供|下载|。|⊙|2|⊙|";


// 	str1=checkFile.getContent();
// 	str2=otherFile.getContent();

	//cout<<"str1 == "<<str1<<endl;

	RKR_GST_Match rkr_gst(str1, str2, 14);
	rkr_gst.beginMatch(30);


	fstream file;
	file.open("c:\\result.txt", ios::out );
	int sum = 0;
	for (vector<Match>::iterator it = rkr_gst.matches.begin(); it != rkr_gst.matches.end(); ++it)
	{
		sum += it->len;
		file<<"<"<<it->m<<", "<<it->n<<", "<<it->len<<">"<<"\n";
	}
	file<<"\n\nthe length  of the first string is : "<<str1.length()<<"\n";	
	file<<"the length  of the second string is : "<<str2.length()<<"\n";
	file<<"The total similar length of these two strings is : " <<sum<<"\n";
	file<<"The similarity of the two string is : " <<(sum * 2.0 /(str1.length() + str2.length()) )<<"\n";


	//system("pause");
	return 0;
}