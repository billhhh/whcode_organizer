#include "stdafx.h"
#include "CropAreas.h"
#include <cv.h>
using namespace cv;
//²ÃÇÐÇøÓò
int CropAreas(Mat img,vector<CropArea_info> cropAreasInfo,vector<CropAreaResult>& cropAreas)
{
	Rect roiRect;
	for (unsigned int i =0;i<cropAreasInfo.size();i++)
	{
		roiRect.width =MIN(img.cols,cropAreasInfo[i].pos.width);
		roiRect.height =MIN(img.rows,cropAreasInfo[i].pos.height);
		roiRect.x = MIN(MAX(roiRect.x,0),img.cols-roiRect.width);
		roiRect.y = MIN(MAX(roiRect.y,0),img.rows-roiRect.height);
		CropAreaResult area;
		area.name = cropAreasInfo[i].name;
		area.rect=roiRect;
		area.groupNum=cropAreasInfo[i].groupNum;
		area.isSecret=cropAreasInfo[i].isSecret;
//		area.img = img(roiRect);
		cropAreas.push_back(area);
	}
	return 0;
}