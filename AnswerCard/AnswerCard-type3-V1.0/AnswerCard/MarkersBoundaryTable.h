#pragma once
#include <cv.h>
using namespace cv;
#include <vector>
using namespace std;

typedef unsigned int UINT;
#define MAXUINT ((UINT)~((UINT)0))
#define MAXINT  ((int)(MAXUINT >> 1))

class MarkersBoundaryTable
{
public:
	//构造函数
	MarkersBoundaryTable(void);
	~MarkersBoundaryTable(void);
	//计算边界查找表
	//boundaryBuffRate=边界缓冲区的大小/标记点大小
	int InitMarkersBoundaryTable(vector<cv::Rect> hMarkers,vector<cv::Rect> vMarkers,double boundaryBuffRate = 0.2,bool merge = false);
	//合并相近边界
	int MergeCloseBoundary();
protected:
	//水平、垂直方向标记点数量
	int hMarkersNum,vMarkersNum;
	//水平方向标记点左界
	int* pHmarkersLBoundary;
	//水平方向标记点右界
	int* pHmarkersRBoundary;
	//垂直方向标记点上界
	int* pVmarkersTBoundary;
	//垂直方向标记点下界
	int* pVmarkersBBoundary;
	//合并阈值
	double mergeThreshold;

public:
	// 获得水平标记点左界
	int GetLBoundary(int hmarker_idx);
	// 获得水平标记点右界
	int GetRBoundary(int hmarker_idx);
	// 获得垂直标记点上界
	int GetTBoundary(int vmarker_idx);
	// 获得垂直标记点下界
	int GetBBoundary(int vmarker_idx);
	// 获得水平标记点数量
	int GetHmarkerNum(void);
	// 获得垂直标记点数量
	int GetVmarkerNum(void);
	// 在图像中绘制边界
	int DrawBoundary(cv::Mat &img,Scalar color,int thickness);
	// 绘制编号
	int DrawMarkersNum(Mat & img, Scalar color, int thickness);
	// 获取包括该点的最大左边界
	int GetNearestLBoundary(int x);
	// 获取最小右边界
	int GetNearestRBoundary(int x);
	// 获取最大上边界
	int GetNearestTBoundary(int y);
	// 获取最小下边界
	int GetNearestBBoundary(int y);
};

