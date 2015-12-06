#include "stdafx.h"
#include"MarkersBoundaryTable.h"


MarkersBoundaryTable::MarkersBoundaryTable(void)
{
	//水平方向标记点左界
	pHmarkersLBoundary = NULL;
	//水平方向标记点右界
	pHmarkersRBoundary = NULL;
	//垂直方向标记点上界
	pVmarkersTBoundary = NULL;
	//垂直方向标记点下界
	pVmarkersBBoundary = NULL;
	//标记点数量
	hMarkersNum = vMarkersNum =0;
	//合并阈值
	mergeThreshold = 0.8;
}


MarkersBoundaryTable::~MarkersBoundaryTable(void)
{
	if (pHmarkersLBoundary)
	{
		delete []pHmarkersLBoundary;
		delete []pHmarkersRBoundary;
		delete []pVmarkersTBoundary;
		delete []pVmarkersBBoundary;
	}
}

//计算边界查找表
//boundaryBuffRate=边界缓冲区的大小/标记点大小
int MarkersBoundaryTable::InitMarkersBoundaryTable(vector<cv::Rect> hMarkers,vector<cv::Rect> vMarkers,double boundaryBuffRate,bool merge)
{
	//数量赋值
	hMarkersNum = hMarkers.size();
	vMarkersNum = vMarkers.size();
	//若已申请内存，则释放
	if (pHmarkersLBoundary)
	{
		delete []pHmarkersLBoundary;
		delete []pHmarkersRBoundary;
		delete []pVmarkersTBoundary;
		delete []pVmarkersBBoundary;
		//水平方向标记点左界
		pHmarkersLBoundary = NULL;
		//水平方向标记点右界
		pHmarkersRBoundary = NULL;
		//垂直方向标记点上界
		pVmarkersTBoundary = NULL;
		//垂直方向标记点下界
		pVmarkersBBoundary = NULL;
	}
	//申请内存
	pHmarkersLBoundary = new int[hMarkers.size()];
	if (!pHmarkersLBoundary)
	{
		return -1;
	}
	pHmarkersRBoundary = new int[hMarkers.size()];
	if (!pHmarkersRBoundary)
	{
		return -1;
	}
	pVmarkersTBoundary = new int[vMarkers.size()];
	if (!pVmarkersTBoundary)
	{
		return -1;
	}
	pVmarkersBBoundary = new int[vMarkers.size()];
	if (!pVmarkersBBoundary)
	{
		return -1;
	}
	//计算
	for (unsigned int i=0;i<hMarkers.size();i++)
	{
		int hBoundaryBuff = (int)(boundaryBuffRate*hMarkers.at(i).width+0.5);
		pHmarkersLBoundary[i] = hMarkers.at(i).x-hBoundaryBuff;
		pHmarkersRBoundary[i] = hMarkers.at(i).x+hMarkers.at(i).width+hBoundaryBuff;
	}
	for (unsigned int i=0;i<vMarkers.size();i++)
	{
		int vBoundaryBuff = (int)(boundaryBuffRate*vMarkers.at(i).height+0.5);
		pVmarkersTBoundary[i] = vMarkers.at(i).y-vBoundaryBuff;
		pVmarkersBBoundary[i] = vMarkers.at(i).y+vMarkers.at(i).height+vBoundaryBuff;
	}
	//合并相近边界
	if (merge)
	{
		MergeCloseBoundary();
	}
	return 1;
}
//合并相近边界
int MarkersBoundaryTable::MergeCloseBoundary()
{
	if (!pHmarkersLBoundary||hMarkersNum==0||vMarkersNum==0)
	{
		return -1;
	}
	int pixelMergeThreshold = (int)(mergeThreshold*(pVmarkersBBoundary[0]-pVmarkersTBoundary[0])+0.5);
	for (int i=0;i<hMarkersNum-1;i++)
	{
		if (pHmarkersLBoundary[i+1]-pHmarkersRBoundary[i]<pixelMergeThreshold)
		{
			pHmarkersRBoundary[i] = pHmarkersLBoundary[i+1] = (pHmarkersLBoundary[i+1]+pHmarkersRBoundary[i])>>1;
		}
	}
	for (int i=0;i<vMarkersNum-1;i++)
	{
		if (pVmarkersTBoundary[i+1]-pVmarkersBBoundary[i]<pixelMergeThreshold)
		{
			pVmarkersBBoundary[i] = pVmarkersTBoundary[i+1] = (pVmarkersTBoundary[i+1]+pVmarkersBBoundary[i])>>1;
		}
	}
	return 0;
}

// 获得水平标记点左界
int MarkersBoundaryTable::GetLBoundary(int hmarker_idx)
{
	if (hmarker_idx<0||hmarker_idx>hMarkersNum)
	{
		return -1;
	}
	return pHmarkersLBoundary[hmarker_idx];
}
// 获得水平标记点右界
int MarkersBoundaryTable::GetRBoundary(int hmarker_idx)
{
	if (hmarker_idx<0||hmarker_idx>hMarkersNum)
	{
		return -1;
	}
	return pHmarkersRBoundary[hmarker_idx];
}
// 获得垂直标记点上界
int MarkersBoundaryTable::GetTBoundary(int vmarker_idx)
{
	if (vmarker_idx<0||vmarker_idx>vMarkersNum)
	{
		return -1;
	}
	return pVmarkersTBoundary[vmarker_idx];
}
// 获得垂直标记点下界
int MarkersBoundaryTable::GetBBoundary(int vmarker_idx)
{
	if (vmarker_idx<0||vmarker_idx>vMarkersNum)
	{
		return -1;
	}
	return pVmarkersBBoundary[vmarker_idx];
}

// 获得水平标记点数量
int MarkersBoundaryTable::GetXmarkerNum(void)
{
	return hMarkersNum;
}


// 获得垂直标记点数量
int MarkersBoundaryTable::GetYmarkerNum(void)
{
	return vMarkersNum;
}


// 在图像中绘制边界
int MarkersBoundaryTable::DrawBoundary(cv::Mat &img,Scalar color,int thickness)
{
	if (img.cols<pHmarkersRBoundary[hMarkersNum-1]||img.rows<pVmarkersBBoundary[vMarkersNum-1])
	{
		return -1;
	}
	//绘制左右界
	for (int i=0;i<hMarkersNum;i++)
	{
		cv::line(img,cv::Point(pHmarkersLBoundary[i],0),cv::Point(pHmarkersLBoundary[i],img.rows-1),color,thickness);
		cv::line(img,cv::Point(pHmarkersRBoundary[i],0),cv::Point(pHmarkersRBoundary[i],img.rows-1),color,thickness);
	}
	//绘制上下界
	for (int i=0;i<vMarkersNum;i++)
	{
		cv::line(img,cv::Point(0,pVmarkersTBoundary[i]),cv::Point(img.cols-1,pVmarkersTBoundary[i]),color,thickness);
		cv::line(img,cv::Point(0,pVmarkersBBoundary[i]),cv::Point(img.cols-1,pVmarkersBBoundary[i]),color,thickness);
	}
	return 0;
}


// 绘制编号
int MarkersBoundaryTable::DrawMarkersNum(Mat & img, Scalar color, int thickness)
{
	if (img.cols<pHmarkersRBoundary[hMarkersNum-1]||img.rows<pVmarkersBBoundary[vMarkersNum-1])
	{
		return -1;
	}
	//绘制水平编号
	cv::Point pt;
	for (int i=0;i<hMarkersNum;i++)
	{
		ostringstream oss;
		oss<<i+1;
		if (oss.str().length()==1)			//一位数
		{
			pt.x = (pHmarkersLBoundary[i]+pHmarkersRBoundary[i]-16)>>1;
			pt.y = pVmarkersTBoundary[0];
		}else if (oss.str().length()==2)	//两位数
		{
			pt.x = (pHmarkersLBoundary[i]+pHmarkersRBoundary[i]-32)>>1;
			pt.y = pVmarkersTBoundary[0];
		}
		cv::putText(img,oss.str(),pt,FONT_HERSHEY_SCRIPT_SIMPLEX,0.6,color,thickness);
	}
	for (int i=0;i<vMarkersNum;i++)
	{
		ostringstream oss;
		oss<<i+1;
		if (oss.str().length()==1)			//一位数
		{
			pt.x = pHmarkersLBoundary[0]-16;
			pt.y = pVmarkersBBoundary[i];
		}else if (oss.str().length()==2)	//两位数
		{
			pt.x = pHmarkersLBoundary[0]-32;
			pt.y = pVmarkersBBoundary[i];
		}
		cv::putText(img,oss.str(),pt,FONT_HERSHEY_SCRIPT_SIMPLEX,0.6,color,thickness);
	}
	return 0;
}


// 获取包括该点的最大左边界
int MarkersBoundaryTable::GetNearestLBoundary(int x)
{
	int diff,minDiff = INT_MAX,minIdx = -1;
	for (int i=0;i<hMarkersNum;i++)
	{
		diff = abs(pHmarkersLBoundary[i]-x);
		if(diff<minDiff)
		{
			minIdx = i;
			minDiff = diff;
		}
	}
	return minIdx;
}


// 获取最小右边界
int MarkersBoundaryTable::GetNearestRBoundary(int x)
{
	int diff,minDiff = INT_MAX,minIdx = -1;
	for (int i=0;i<hMarkersNum;i++)
	{
		diff = abs(pHmarkersRBoundary[i]-x);
		if(diff<minDiff)
		{
			minIdx = i;
			minDiff = diff;
		}
	}
	return minIdx;
}


// 获取最大上边界
int MarkersBoundaryTable::GetNearestTBoundary(int y)
{
	int diff,minDiff = INT_MAX,minIdx = -1;
	for (int i=0;i<hMarkersNum;i++)
	{
		diff = abs(pVmarkersTBoundary[i]-y);
		if(diff<minDiff)
		{
			minIdx = i;
			minDiff = diff;
		}
	}
	return minIdx;
}


// 获取最小下边界
int MarkersBoundaryTable::GetNearestBBoundary(int y)
{
	int diff,minDiff = INT_MAX,minIdx = -1;
	for (int i=0;i<hMarkersNum;i++)
	{
		diff = abs(pVmarkersBBoundary[i]-y);
		if(diff<minDiff)
		{
			minIdx = i;
			minDiff = diff;
		}
	}
	return minIdx;
}

//获取题目区域
cv::Rect MarkersBoundaryTable::GetQuestionBoundry(ItemPos pos)
{
	cv::Rect rt;
	if(pos.isCrosswise)
	{
		rt.x=GetLBoundary(pos.markerIdx[1]);
		rt.y = GetTBoundary(pos.markerIdx[0]);
		rt.width=GetRBoundary(pos.markerIdx[2])-GetLBoundary(pos.markerIdx[1]);
		rt.height=GetBBoundary(pos.markerIdx[0])-GetTBoundary(pos.markerIdx[0]);
	}
	else
	{
		rt.x=GetLBoundary(pos.markerIdx[0]);
		rt.y = GetTBoundary(pos.markerIdx[1]);
		rt.width=GetRBoundary(pos.markerIdx[0])-GetLBoundary(pos.markerIdx[0]);
		rt.height=GetBBoundary(pos.markerIdx[2])-GetTBoundary(pos.markerIdx[1]);
	}
	return rt;
	
}

void MarkersBoundaryTable::printMBT()
{
	cout<<"hmarker"<<endl;
	for (int i=0;i<this->hMarkersNum;i++)
	{
		cout<<i<<"  "<<this->pHmarkersLBoundary[i]<<"  "<<this->pHmarkersRBoundary[i]<<endl;
	}
	cout<<"vmarker"<<endl;
	for (int i=0;i<this->vMarkersNum;i++)
	{
		cout<<i<<"  "<<this->pVmarkersBBoundary[i]<<"  "<<this->pVmarkersTBoundary[i]<<endl;
	}
}