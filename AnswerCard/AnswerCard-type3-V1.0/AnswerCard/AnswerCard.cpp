
#include "AnswerCard.h"
#include "AnswerCardDlg3.h"
#include "qdebug.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAnswerCardApp 构造
CAnswerCardApp::CAnswerCardApp()
	: m_group_state(0)
	, m_state(0)
	, is_synchronous(false)
	, min_markers_area(0)
	, anchor_type(0)
	, m_hasQuestions(true)
	, m_isFront(true)
	, questionType(0)
{
	//同步标志初始化
	is_synchronous = true;

	//读取配置文件
	readConfig();

	min_markers_area = 50;
	whiteLineRect = cv::Rect();
	blackLineRect = cv::Rect();
}

void CAnswerCardApp::readConfig()
{
	QSettings settings("config.ini", QSettings::IniFormat);

	//定位点区域
	int color_r = settings.value("AnchorPoint/Color_R").toInt();
	int color_g = settings.value("AnchorPoint/Color_G").toInt();
	int color_b = settings.value("AnchorPoint/Color_B").toInt();
	int thickness = settings.value("AnchorPoint/Thickness").toInt();
	anchor_point_color = Scalar(color_b,color_g,color_r);
	anchor_point_thickness = thickness;

	//标记点区域
	color_r = settings.value("MarkerPoint/Color_R").toInt();
	color_g = settings.value("MarkerPoint/Color_G").toInt();
	color_b = settings.value("MarkerPoint/Color_B").toInt();
	thickness = settings.value("MarkerPoint/Thickness").toInt();
	markers_point_color = Scalar(color_b,color_g,color_r);
	markers_point_thickness = thickness;

	//条形码区域
	color_r = settings.value("BarCode/Color_R").toInt();
	color_g = settings.value("BarCode/Color_G").toInt();
	color_b = settings.value("BarCode/Color_B").toInt();
	thickness = settings.value("BarCode/Thickness").toInt();
	barcode_color = Scalar(color_b,color_g,color_r);
	barcode_thickness = thickness;

	color_r = settings.value("BarCode_Clicked/Color_R").toInt();
	color_g = settings.value("BarCode_Clicked/Color_G").toInt();
	color_b = settings.value("BarCode_Clicked/Color_B").toInt();
	thickness = settings.value("BarCode_Clicked/Thickness").toInt();
	barcodeClicked_color = Scalar(color_b,color_g,color_r);
	barcodeClicked_thickness = thickness;

	//单选题颜色及线宽
	color_r = settings.value("SingleQuestion/Color_R").toInt();
	color_g = settings.value("SingleQuestion/Color_G").toInt();
	color_b = settings.value("SingleQuestion/Color_B").toInt();
	thickness = settings.value("SingleQuestion/Thickness").toInt();
	answer_color = Scalar(color_b,color_g,color_r);
	answer_single_thickness = thickness;

	color_r = settings.value("SingleQuestion_Clicked/Color_R").toInt();
	color_g = settings.value("SingleQuestion_Clicked/Color_G").toInt();
	color_b = settings.value("SingleQuestion_Clicked/Color_B").toInt();
	thickness = settings.value("SingleQuestion_Clicked/Thickness").toInt();
	answerClicked_color = Scalar(color_b,color_g,color_r);
	answerClicked_single_thickness = thickness;

	//多选题颜色及线宽
	color_r = settings.value("MultiQuestion/Color_R").toInt();
	color_g = settings.value("MultiQuestion/Color_G").toInt();
	color_b = settings.value("MultiQuestion/Color_B").toInt();
	thickness = settings.value("MultiQuestion/Thickness").toInt();
	answer_multi_color = Scalar(color_b,color_g,color_r);
	answer_multi_thickness = thickness;

	color_r = settings.value("MultiQuestion_Clicked/Color_R").toInt();
	color_g = settings.value("MultiQuestion_Clicked/Color_G").toInt();
	color_b = settings.value("MultiQuestion_Clicked").toInt();
	thickness = settings.value("MultiQuestion_Clicked/Thickness").toInt();
	answerClicked_multi_color = Scalar(color_b,color_g,color_r);
	answerClicked_multi_thickness = thickness;

	//预定义填涂点颜色线宽
	color_r = settings.value("FillPoint_Clicked/Color_R").toInt();
	color_g = settings.value("FillPoint_Clicked/Color_G").toInt();
	color_b = settings.value("FillPoint_Clicked/Color_B").toInt();
	thickness = settings.value("FillPoint_Clicked/Thickness").toInt();
	cfpClicked_color = Scalar(color_b,color_g,color_r);
	cfpClicked_thickness = thickness;

	//预定义填涂点颜色线宽
	color_r = settings.value("FillPoint/Color_R").toInt();
	color_g = settings.value("FillPoint/Color_G").toInt();
	color_b = settings.value("FillPoint/Color_B").toInt();
	thickness = settings.value("FillPoint/Thickness").toInt();
	cfp_color = Scalar(color_b,color_g,color_r);
	cfp_thickness = thickness;

	//裁切区域颜色线宽
	color_r = settings.value("CropArea/Color_R").toInt();
	color_g = settings.value("CropArea/Color_G").toInt();
	color_b = settings.value("CropArea/Color_B").toInt();
	thickness = settings.value("CropArea/Thickness").toInt();
	cropArea_color = Scalar(color_b,color_g,color_r);
	cropArea_thickness = thickness;

	color_r = settings.value("CropArea_Clicked/Color_R").toInt();
	color_g = settings.value("CropArea_Clicked/Color_G").toInt();
	color_b = settings.value("CropArea_Clicked/Color_B").toInt();
	thickness = settings.value("CropArea_Clicked/Thickness").toInt();
	cropAreaClicked_color = Scalar(color_b,color_g,color_r);
	cropAreaClicked_thickness = thickness;

	//白检测线颜色线宽
	color_r = settings.value("WhiteLine/Color_R").toInt();
	color_g = settings.value("WhiteLine/Color_G").toInt();
	color_b = settings.value("WhiteLine/Color_B").toInt();
	thickness = settings.value("WhiteLine/Thickness").toInt();
	whiteLine_color = Scalar(color_b,color_g,color_r);
	whiteLine_thickness = thickness;

	//黑检测线颜色线宽
	color_r = settings.value("BlackLine/Color_R").toInt();
	color_g = settings.value("BlackLine/Color_G").toInt();
	color_b = settings.value("BlackLine/Color_B").toInt();
	thickness = settings.value("BlackLine/Thickness").toInt();
	blackLine_color = Scalar(color_b,color_g,color_r);
	blackLine_thickness = thickness;

	//虚拟标记点颜色
	color_r = settings.value("VirtualMarker/Color_R").toInt();
	color_g = settings.value("VirtualMarker/Color_G").toInt();
	color_b = settings.value("VirtualMarker/Color_B").toInt();
	marker_color = Scalar(color_b,color_g,color_r);

	//黑检测线颜色线宽
	color_r = settings.value("VirTualMarker_Clicked/Color_R").toInt();
	color_g = settings.value("VirTualMarker_Clicked/Color_G").toInt();
	color_b = settings.value("VirTualMarker_Clicked/Color_B").toInt();
	thickness = settings.value("VirTualMarker_Clicked/Thickness").toInt();
	markerClicked_color = Scalar(color_b,color_g,color_r);
	markerClicked_thickness = thickness;

	//页码点颜色线宽
	color_r = settings.value("PagePoint/Color_R").toInt();
	color_g = settings.value("PagePoint/Color_G").toInt();
	color_b = settings.value("PagePoint/Color_B").toInt();
	thickness = settings.value("PagePoint/Thickness").toInt();
	pagePoint_color = Scalar(color_b,color_g,color_r);
	pagePoint_thickness = thickness;

	color_r = settings.value("PagePoint_Clicked/Color_R").toInt();
	color_g = settings.value("PagePoint_Clicked/Color_G").toInt();
	color_b = settings.value("PagePoint_Clicked/Color_B").toInt();
	thickness = settings.value("PagePoint_Clicked/Thickness").toInt();
	pagePointClicked_color = Scalar(color_b,color_g,color_r);
	pagePointClicked_thickness = thickness;
}

void CAnswerCardApp::clear()
{
	for (int i=0;i<4;i++)
	{
		//判断是否已经赋值
		if (anchorPoints[i].width>0)
		{
			anchorPoints[i] = cv::Rect();
		}
	}

	barGroup.clear();
	cropAreas.clear();
	cfp_group3.clear();
	questionInfo.clear();
	hmarkers.clear();
	vmarkers.clear();
	markers.clear();
	markersTable.clear();
	whiteLineRect = cv::Rect();
	blackLineRect = cv::Rect();
	anchorRect = cv::Rect();
	anchor_type = -1;
	originalPoint = cv::Point();
	referPoint.clear();
	pagePoint.clear();
}

// 唯一的一个 CAnswerCardApp 对象
CAnswerCardApp theApp;


// 计算点所在的连通域外接矩形，并绘制
bool CAnswerCardApp::GetArchorPointRect(QPoint pt,int ap_idx,bool is_draw)
{
	//输入有效性检查
	if (ap_idx<0||ap_idx>3)
	{
		return false;
	}
	//连通域检测
	vector<vector<cv::Point> > contours;
	vector<Vec4i>hierarchy;

	CvRect roirect;
	int roisize=img_bw.rows*0.05;
	roirect.width=roirect.height=2*roisize;
	roirect.x=min(max(0,pt.x()-roisize),img_bw.cols-roirect.width);
	roirect.y=min(max(0,pt.y()-roisize),img_bw.rows-roirect.height);
	Mat roi=img_bw(roirect);

	findContours(roi,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );

	bool isFound =false;
	if( !contours.empty())
	{
		for( unsigned int i = 0; i< contours.size(); i++ )
		{
			//不在多边形内部
			if (pointPolygonTest(contours.at(i),cv::Point(pt.x()-roirect.x,pt.y()-roirect.y),false)<0)
				continue;
			anchorPoints[ap_idx] = boundingRect(contours.at(i));
			anchorPoints[ap_idx].x += roirect.x;
			anchorPoints[ap_idx].y += roirect.y;
			isFound = true;
		}
	}
	//是否需要绘制
	if (is_draw)
	{
		//判断数据与图像是否同步
		if (is_synchronous)
		{
			switch(ap_idx)
			{
			case 0:
				cv::putText(img_show,"1",cv::Point2d(anchorPoints[ap_idx].x,anchorPoints[ap_idx].y+anchorPoints[ap_idx].height*0.8),FONT_HERSHEY_COMPLEX,.6,anchor_point_color,2);
				break;
			case 1:
				cv::putText(img_show,"2",cv::Point2d(anchorPoints[ap_idx].x,anchorPoints[ap_idx].y+anchorPoints[ap_idx].height*0.8),FONT_HERSHEY_COMPLEX,.6,anchor_point_color,2);
				break;
			case 2:
				cv::putText(img_show,"3",cv::Point2d(anchorPoints[ap_idx].x,anchorPoints[ap_idx].y+anchorPoints[ap_idx].height*0.8),FONT_HERSHEY_COMPLEX,.6,anchor_point_color,2);
				break;
			case 3:
				cv::putText(img_show,"4",cv::Point2d(anchorPoints[ap_idx].x,anchorPoints[ap_idx].y+anchorPoints[ap_idx].height*0.8),FONT_HERSHEY_COMPLEX,.6,anchor_point_color,2);
				break;

			}
			rectangle(img_show,anchorPoints[ap_idx],anchor_point_color,anchor_point_thickness);
		}else
			is_synchronous = false;
	}
	//是否找到对应的连通域
	if (isFound)
		return true;
	else
		return false;
	
}

//vector比较算法,按x坐标排序
bool RectXCompare(cv::Rect& rt1,cv::Rect& rt2)
{
	return rt1.x <= rt2.x;
}

//vector比较算法,按y坐标排序
bool RectYCompare(cv::Rect& rt1,cv::Rect& rt2)
{
	return rt1.y <= rt2.y;
}

// 计算标记点数量
vector<cv::Rect> CAnswerCardApp::GetMarkersNum(Mat srcroi)
 {
	 Mat roi;
	 srcroi.copyTo(roi);
	 Mat se = getStructuringElement(MORPH_ELLIPSE,Size(5,5));
	 morphologyEx(roi,roi,cv::MORPH_CLOSE,se);
	vector<cv::Rect> mks;
	vector<vector<cv::Point> > contours;
//  	imshow("test",roi);
//  	cvWaitKey(0);
	findContours(roi,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );
	if (contours.size()!=0)
	{
		vector<int> markArea;
		for( int i = contours.size()-1; i>=0 ; i-- )
		{
			int area =(int) contourArea(contours.at(i));
			markArea.push_back(area);
		}
		sort(markArea.begin(),markArea.end());
		min_markers_area=markArea.at(markArea.size()/2)/2;

		vector<int> width;
		vector<int> height;

		for( int i = contours.size()-1; i>=0 ; i-- )
		{
			int area =(int) contourArea(contours.at(i));
			if (area<min_markers_area)
			{
				continue;
			}
			mks.push_back(boundingRect(contours.at(i)));
			width.push_back(boundingRect(contours.at(i)).width);
			height.push_back(boundingRect(contours.at(i)).height);
		}

		int midWidth = width.at(width.size()/2);
		int midHeight = height.at(height.size()/2);
		//允许的误差大小
		int tolerance = 10;

		for(vector<cv::Rect>::iterator it  = mks.begin(); it != mks.end(); )  
		{  
			if (abs(it->width - midWidth) > tolerance)
			{
				it = mks.erase(it);
			}
			else if (abs(it->height - midHeight) > tolerance)
			{
				it = mks.erase(it);
			}
			else
				it++;			
		} 

	}
	return mks;
}


// 重新绘制
int CAnswerCardApp::Redraw3(void)
{
	Mat tmp;
	img_raw.copyTo(tmp);

	//绘制定位点
	for (int i=0;i<4;i++)
	{
		//判断是否已经赋值
		if (anchorPoints[i].width>0)
		{
			rectangle(tmp,anchorPoints[i],anchor_point_color,anchor_point_thickness);
		}
	}

	if (anchorRect.width > 0)
	{
		rectangle(tmp,anchorRect,anchor_point_color,anchor_point_thickness);
	}

	//绘制黑白线
	if (whiteLineRect.width > 0)
	{
		rectangle(tmp, whiteLineRect, whiteLine_color, whiteLine_thickness);
	}
	if (blackLineRect.width > 0)
	{
		rectangle(tmp, blackLineRect, blackLine_color, blackLine_thickness);
	}

	//绘制标记点区域
	vector<cv::Rect>::iterator iter1 = hmarkers.begin();

	for (; iter1 != hmarkers.end(); ++iter1)
	{
		rectangle(tmp, (*iter1), marker_color, CV_FILLED);
	}

	vector<cv::Rect>::iterator iter2 = vmarkers.begin();

	for (; iter2 != vmarkers.end(); ++iter2)
	{
		rectangle(tmp, (*iter2), marker_color, CV_FILLED);
	}

	vector<Marker_info3>::iterator iter = markers.begin();

	for (; iter != markers.end(); ++iter)
	{
		vector<cv::Rect>::iterator xiter = iter->xMarker.begin();

		for (; xiter != iter->xMarker.end(); ++xiter)
		{
			rectangle(tmp, (*xiter), marker_color, CV_FILLED);
		}

		vector<cv::Rect>::iterator yiter = iter->yMarker.begin();

		for (; yiter != iter->yMarker.end(); ++yiter)
		{
			rectangle(tmp, (*yiter), marker_color, CV_FILLED);
		}
	}

	//绘制条形码
	for (unsigned int i = 0; i < barGroup.size(); i++)
	{
		rectangle(tmp, barGroup[i].pos, barcode_color, barcode_thickness);
	}

	//绘制页码标识
	for (unsigned int i=0;i<pagePoint.size();i++)
	{
		rectangle(tmp,pagePoint[i],pagePoint_color,pagePoint_thickness);		
	}

	//自定义填涂点
	for (unsigned int i = 0;i<cfp_group3.size();i++)
	{
		for (unsigned int j = 0;j<cfp_group3[i].fillingPoints.size();j++)
		{
			vector<Rect>::iterator iterBegin = cfp_group3[i].fillingPoints[j].pos.begin();
			vector<Rect>::iterator iterEnd = cfp_group3[i].fillingPoints[j].pos.end() - 1;
			cv::Rect rt = cv::Rect(iterBegin->tl(), iterEnd->br());

			rectangle(tmp, rt, cfp_color, cfp_thickness);
		}
	}

	//识别参考点
	for (int i = 0; i < referPoint.size(); ++i)
	{
		rectangle(tmp,referPoint.at(i),cfp_color,cfp_thickness);
	}

	//页码标识
	for (int i = 0; i < pagePoint.size(); ++i)
	{
		rectangle(tmp,pagePoint.at(i),pagePoint_color,pagePoint_thickness);
	}

	//答案区域模块
	if (questionInfo.size()>0)
	{
		for (unsigned int i=0;i<questionInfo.size();i++)
		{
			cv::Point lt,rb;
			if (questionInfo[i].isCrosswise)
			{
				lt.y = markersTable[questionInfo[i].mark_id].GetTBoundary(questionInfo[i].markerIdx[0]);
				rb.y = markersTable[questionInfo[i].mark_id].GetBBoundary(questionInfo[i].markerIdx[0]);
				lt.x = markersTable[questionInfo[i].mark_id].GetLBoundary(questionInfo[i].markerIdx[1]);
				rb.x = markersTable[questionInfo[i].mark_id].GetRBoundary(questionInfo[i].markerIdx[2]);
			}
			else{
				lt.y = markersTable[questionInfo[i].mark_id].GetTBoundary(questionInfo[i].markerIdx[1]);
				rb.y = markersTable[questionInfo[i].mark_id].GetBBoundary(questionInfo[i].markerIdx[2]);
				lt.x = markersTable[questionInfo[i].mark_id].GetLBoundary(questionInfo[i].markerIdx[0]);
				rb.x = markersTable[questionInfo[i].mark_id].GetRBoundary(questionInfo[i].markerIdx[0]);
			}

			if (questionInfo[i].isSingleChoice)
			{
				rectangle(tmp,lt,rb,answer_color,answer_single_thickness);
			}
			else
			{
				rectangle(tmp,lt,rb,answer_multi_color,answer_multi_thickness);
			}
			
		}
	}

	//绘制裁切区域
	for (unsigned int i = 0; i < cropAreas.size(); i++)
	{
		rectangle(tmp,cropAreas[i].pos,cropArea_color,cropArea_thickness);		
	}

	tmp.copyTo(img_show);
	is_synchronous = true;
	return 0;
}


//对标记点排序
void CAnswerCardApp::SortMarkers(bool is_hmarkers)
{
	if (is_hmarkers)
	{
		sort(hmarkers.begin(),hmarkers.end(),RectXCompare);
	}
	else
	{
		//升序排序
		sort(vmarkers.begin(),vmarkers.end(),RectYCompare);
	}
}

void CAnswerCardApp::SortMarkers(bool is_hmarkers, ushort markerId)
{
	bool find = false;
	vector<Marker_info3>::iterator iter = markers.begin();

	for (; iter != markers.end(); ++iter)
	{
		if (iter->id == markerId)
		{
			find = true;
			break;
		}
	}

	if (find == false)
	{
		return;
	}

	if (is_hmarkers)
	{
		sort(iter->xMarker.begin(),iter->xMarker.end(),RectXCompare);
	}
	else
	{
		//升序排序
		sort(iter->yMarker.begin(),iter->yMarker.end(),RectYCompare);
	}	
}

// 从文件中读取图像
int CAnswerCardApp::LoadImg(const QString &path)
{
	//读取图像
	img_raw = imread(path.toAscii().data());
	//判断图像读取是否正确
	if (img_raw.data == NULL)
	{
		return -1;
	}
	////使图像长宽为4的整数倍
	//if (img_raw.rows%4!=0||img_raw.cols%4!=0)
	//{
	//	cv::Rect roi(0,0,img_raw.cols-img_raw.cols%4,img_raw.rows-img_raw.rows%4);
	//	img_raw = img_raw(roi);
	//}
	is_synchronous = false;
	//图像读取成功，修改状态
	m_state++;
	return 0;
}


// 转换成输出结构体
int CAnswerCardApp::TransToOutputStruct3()
{
	acinfo3.questionType = questionType;
	acinfo3.isFront = m_isFront;
	acinfo3.imgSize = cv::Size(img_raw.cols,img_raw.rows);
	////////////////////////////////////题目信息////////////////////////////////////////
	
	for (int i=questionInfo.size()-1;i>=0;i--)
	{
		QustionItemPos item;
		
		item.id = questionInfo.at(i).id;
		item.mark_id = questionInfo.at(i).mark_id;
		item.isCrosswise = questionInfo.at(i).isCrosswise;
		item.isSingleChoice = questionInfo.at(i).isSingleChoice;
		item.interval = questionInfo.at(i).interval;

		for (int j=0;j<3;j++)
		{
			item.markerIdx[j] = questionInfo.at(i).markerIdx[j];
		}
		acinfo3.questioninfo.push_back(item);
	}
	/////////////////////////////////////定位点信息///////////////////////////////////////
	acinfo3.anchorRect = anchorRect;

	if (anchorRect.width > 0)
	{
		acinfo3.isAnchorRectExist = true;
	}
	else
	{
		acinfo3.isAnchorRectExist = false;
	}

	acinfo3.anchorPointInfo.anchorType = anchor_type;
	switch (anchor_type)
	{
	case 15:
		//1234
		acinfo3.anchorPointInfo.num = 4;
		for (int i=0;i<4;i++)
		{
			acinfo3.anchorPointInfo.anchorPt.push_back(anchorPoints[i]);
		}
		break;
	case 7:
		//123缺4
		acinfo3.anchorPointInfo.num = 3;
		for (int i = 0;i<3;i++)
		{
			acinfo3.anchorPointInfo.anchorPt.push_back(anchorPoints[i]);
		}
		break;
	case 11:
		//124缺3
		acinfo3.anchorPointInfo.num = 3;
		for (int i = 0;i<4;i++)
		{
			if (i == 2)
				continue;
			acinfo3.anchorPointInfo.anchorPt.push_back(anchorPoints[i]);
		}
		break;
	case 13:
		//134缺2
		acinfo3.anchorPointInfo.num = 3;
		for (int i = 0;i<4;i++)
		{
			if (i == 1)
				continue;
			acinfo3.anchorPointInfo.anchorPt.push_back(anchorPoints[i]);
		}
		break;
	case 14:
		//234缺1
		acinfo3.anchorPointInfo.num = 3;
		for (int i = 1;i<4;i++)
		{
			acinfo3.anchorPointInfo.anchorPt.push_back(anchorPoints[i]);
		}
		break;
	case 3:
		//12缺34
		acinfo3.anchorPointInfo.num = 2;
		for (int i = 0;i<4;i++)
		{
			if (i == 2 || i == 3)
				continue;
			acinfo3.anchorPointInfo.anchorPt.push_back(anchorPoints[i]);
		}
		break;
	case 10:
		//24缺13
		acinfo3.anchorPointInfo.num = 2;
		for (int i = 0;i<4;i++)
		{
			if (i == 0 || i == 2)
				continue;
			acinfo3.anchorPointInfo.anchorPt.push_back(anchorPoints[i]);
		}
		break;
	case 5:
		//13缺24
		acinfo3.anchorPointInfo.num = 2;
		for (int i = 0;i<4;i++)
		{
			if (i == 1 || i == 3)
				continue;
			acinfo3.anchorPointInfo.anchorPt.push_back(anchorPoints[i]);
		}
		break;
	case 12:
		//3 4缺1 2
		acinfo3.anchorPointInfo.num = 2;
		for (int i = 0;i<4;i++)
		{
			if (i == 0 || i == 1)
				continue;
			acinfo3.anchorPointInfo.anchorPt.push_back(anchorPoints[i]);
		}
		break;
	}

	if (acinfo3.anchorPointInfo.anchorPt.size() == 0)
	{
		acinfo3.isAnchorPointExist = false;
	}
	else
	{
		acinfo3.isAnchorPointExist = true;
	}

	int refer_x, refer_y;

	if (acinfo3.anchorPointInfo.anchorPt.size() > 0)
	{
		refer_x = acinfo3.anchorPointInfo.anchorPt.at(0).x;
		refer_y = acinfo3.anchorPointInfo.anchorPt.at(0).y;
	}
	else if (acinfo3.anchorRect.width > 0)
	{
		refer_x = originalPoint.x;
		refer_y = originalPoint.y;
	}
	else
	{
		refer_x = 0;
		refer_y = 0;
	}

	//////////////////////////////////标记点信息//////////////////////////////////////////
	acinfo3.markerInfo = markers;
	vector<Marker_info3>::iterator markerIter = acinfo3.markerInfo.begin();
	for (; markerIter != acinfo3.markerInfo.end(); ++markerIter)
	{
		vector<cv::Rect>::iterator xIter = markerIter->xMarker.begin();
		for (; xIter != markerIter->xMarker.end(); ++xIter)
		{
			xIter->x -= refer_x;
			xIter->y -= refer_y;
		}

		vector<cv::Rect>::iterator yIter = markerIter->yMarker.begin();
		for (; yIter != markerIter->yMarker.end(); ++yIter)
		{
			yIter->x -= refer_x;
			yIter->y -= refer_y;
		}
	}

	/////////////////////////////////页码标识////////////////////////////////////////////
	acinfo3.pageMarker = pagePoint;
	for (int i = acinfo3.pageMarker.size() - 1; i >= 0; i--)
	{
		acinfo3.pageMarker[i].x -= refer_x;
		acinfo3.pageMarker[i].y -= refer_y;
	}

	//////////////////////////////////条形码信息////////////////////////////////////////
	acinfo3.barGroup = barGroup;
	for (int i = acinfo3.barGroup.size() - 1; i >= 0; i--)
	{
		acinfo3.barGroup[i].pos.x -= refer_x;
		acinfo3.barGroup[i].pos.y -= refer_y;
	}

	//////////////////////////////////自定义填涂点////////////////////////////////////////
	acinfo3.fillingPointGroup = cfp_group3;

	for (int i = acinfo3.fillingPointGroup.size() - 1; i >= 0; --i)
	{
		for (int j = acinfo3.fillingPointGroup[i].fillingPoints.size() - 1; j >= 0; --j)
		{
			for (int z = acinfo3.fillingPointGroup[i].fillingPoints[j].pos.size() - 1; z >= 0; --z)
			{
				acinfo3.fillingPointGroup[i].fillingPoints[j].pos[z].x -= refer_x;
				acinfo3.fillingPointGroup[i].fillingPoints[j].pos[z].y -= refer_y;
			}
		}
	}

	////////////////////////////////////识别参考点//////////////////////////////////////
	acinfo3.refPoint = referPoint;

	///////////////////////////////////裁切区域///////////////////////////////////////
	acinfo3.cropAreaInfo = cropAreas;
	for (int i=cropAreas.size()-1;i>=0;i--)
	{
		acinfo3.cropAreaInfo[i].pos.x-=refer_x;
		acinfo3.cropAreaInfo[i].pos.y-=refer_y;
	}

	//////////////////////////////////////检测线////////////////////////////////////////
	acinfo3.whiteLine = cv::Rect(whiteLineRect);
	acinfo3.blackLine = cv::Rect(blackLineRect);
	acinfo3.whiteLine.x -= refer_x;
	acinfo3.whiteLine.y -= refer_y;
	acinfo3.blackLine.x -= refer_x;
	acinfo3.blackLine.y -= refer_y;

	//////////////////////////////////////背景////////////////////////////////////////
	vector<Questions> questionTmp = CountQuestionsBackground();
	vector<Questions>::iterator iter2 = questionTmp.begin();
	for (;iter2 != questionTmp.end(); ++iter2)
	{
		PerQuestionBackground_info info;
		info = GetPerQuestionBackground_info(img_raw(iter2->rect), iter2->num, 
			iter2->isCrossWise);
		acinfo3.questionBackgroundInfo.push_back(info);
	}
	return 0;
}

// 新加一道题
void CAnswerCardApp::AddQuestion(int id, ushort markerId, bool isCrosswise, bool isSingleChoice, ushort interval, ushort markerIdx0, ushort markerIdx1, ushort markerIdx2)
{
	QustionItemPos item;
	item.id = id;
	item.mark_id = markerId;
	item.isCrosswise = isCrosswise;
	item.interval = interval;
	item.isSingleChoice = isSingleChoice;
	item.markerIdx[0] = markerIdx0;
	item.markerIdx[1] = markerIdx1;
	item.markerIdx[2] = markerIdx2;
	questionInfo.push_back(item);
}

//加一个自定义填涂点
void CAnswerCardApp::AddFillPoint(string name, FillingPointsType type,
	bool isCrosswise, bool isSingleChoice, int numOfRect, int cspace, 
	int rspace, cv::Point lt, cv::Point rb, int numOfOption)
{
	FillingPoints_info3 info;
	info.name = name;
	info.type = type;
	info.isCrosswise = isCrosswise;

	//横向排布
	if (isCrosswise)
	{
		int height = (rb.y - lt.y) / numOfRect;
		int width = (rb.x - lt.x) / numOfOption;

		//计算背景
		PerFillingPtBackground_info backInfo;
		cv::Rect rt = cv::Rect(lt.x, lt.y, rb.x - lt.x, height);
		backInfo = GetPerFillingPtBackground_info(img_raw(rt), numOfOption, rspace, 
			isCrosswise, type);
		info.bgInfo = cv::Mat(backInfo.bkInfo);

		for (int i = 0; i < numOfRect; i += cspace + 1)
		{
			FillingpointItemPos item;
			item.isSingleChoice = isSingleChoice;
			item.id = info.fillingPoints.size() + 1;

			for (int j = 0; j < numOfOption; j += rspace + 1)
			{
				cv::Rect rect(lt.x + j * width, lt.y + i * height, width, height);
				item.pos.push_back(rect);
			}

			info.fillingPoints.push_back(item);
		}

		cfp_group3.push_back(info);
	}
	else
	{
		int height = (rb.y - lt.y) / numOfOption;
		int width = (rb.x - lt.x) / numOfRect;

		//计算背景
		PerFillingPtBackground_info backInfo;
		cv::Rect rt = cv::Rect(lt.x, lt.y, width, rb.y - lt.y);
		backInfo = GetPerFillingPtBackground_info(img_raw(rt), numOfOption, cspace, 
			isCrosswise, type);
		info.bgInfo = cv::Mat(backInfo.bkInfo);

		for (int i = 0; i < numOfRect; i += rspace + 1)
		{
			FillingpointItemPos item;
			item.isSingleChoice = isSingleChoice;
			item.id = info.fillingPoints.size() + 1;

			for (int j = 0; j < numOfOption; j += cspace + 1)
			{
				cv::Rect rect(lt.x + i * width, lt.y + j * height, width, height);
				item.pos.push_back(rect);
			}

			info.fillingPoints.push_back(item);
		}

		cfp_group3.push_back(info);
	}
}

void CAnswerCardApp::clearACInfo3()
{
	theApp.acinfo3.barGroup.clear();
	theApp.acinfo3.cropAreaInfo.clear();
	theApp.acinfo3.fillingPointGroup.clear();
	theApp.acinfo3.anchorPointInfo.anchorPt.clear();
	theApp.acinfo3.questioninfo.clear();
	theApp.acinfo3.questionBackgroundInfo.clear();
	theApp.acinfo3.whiteLine = cv::Rect();
	theApp.acinfo3.blackLine = cv::Rect();
	theApp.acinfo3.markerInfo.clear();
	theApp.acinfo3.anchorRect = cv::Rect();
	theApp.acinfo3.isAnchorPointExist = false;
	theApp.acinfo3.isAnchorRectExist = false;
	theApp.acinfo3.anchorPointInfo.num = 0;
	theApp.acinfo3.anchorPointInfo.anchorType = 0;
	theApp.acinfo3.refPoint.clear();
	theApp.acinfo3.pageMarker.clear();
	theApp.acinfo3.questionType = 0;
}

vector<Questions> CAnswerCardApp::CountQuestionsBackground()
{
	vector<Questions> questions;
	vector<QustionItemPos>::iterator iter;

	for (iter = questionInfo.begin(); iter != questionInfo.end(); ++iter)
	{
		bool crossWise = iter->isCrosswise;
		short num = iter->markerIdx[2] - iter->markerIdx[1] + 1;
		bool find = false;

		vector<Questions>::iterator iter2;
		for (iter2 = questions.begin(); iter2 != questions.end(); ++iter2)
		{
			if (iter2->num == num && iter2->isCrossWise == crossWise)
			{
				find = true;
				break;
			}
		}

		if (find == false)
		{
			Questions q;
			q.isCrossWise = crossWise;
			q.num = num;

			cv::Point lt,rb;
			if (crossWise)
			{
				lt.y = markersTable[iter->mark_id].GetTBoundary(iter->markerIdx[0]);
				rb.y = markersTable[iter->mark_id].GetBBoundary(iter->markerIdx[0]);
				lt.x = markersTable[iter->mark_id].GetLBoundary(iter->markerIdx[1]);
				rb.x = markersTable[iter->mark_id].GetRBoundary(iter->markerIdx[2]);
			}
			else{
				lt.y = markersTable[iter->mark_id].GetTBoundary(iter->markerIdx[1]);
				rb.y = markersTable[iter->mark_id].GetBBoundary(iter->markerIdx[2]);
				lt.x = markersTable[iter->mark_id].GetLBoundary(iter->markerIdx[0]);
				rb.x = markersTable[iter->mark_id].GetRBoundary(iter->markerIdx[0]);
			}

			q.rect = cv::Rect(lt, rb);
			questions.push_back(q);
			
		}
	}

	return questions;
}

double GetEmptyRate(Mat gray)
{
	Mat mask230;
	Mat tmp;
	if(gray.type() == CV_8UC3)
	{
		cvtColor(gray,tmp,CV_RGB2GRAY);
	}

	threshold(tmp,mask230,230,255,THRESH_BINARY_INV);
	Scalar mean,stddev;
	meanStdDev(tmp,mean,stddev,mask230);	//计算方差

	return stddev.val[0]*stddev.val[0]/cv::countNonZero(mask230);
}

PerFillingPtBackground_info  GetPerFillingPtBackground_info(Mat img2,int num,int interval,bool isCrosswise,FillingPointsType type){
    PerFillingPtBackground_info  pfpt_info;

    int optionNum=(num+interval)/(interval+1);
    Mat questionGraySum(2,optionNum,CV_32S);
	Mat img;
	img2.copyTo(img);
    //选项矩形
    Rect optionRect;
    double step;
    //如果横排
    if(isCrosswise)
    {
        step = img.cols/num;
        optionRect = Rect(0,0,(int)step,img.rows);
        Mat optionImg;
        int j=0;
        for (int i=0;i<num;i=i+interval+1)
        {

            optionRect.x=min((int)step*i,img.cols-optionRect.width);
            //取出每个选项区域并反相
            optionImg = 255-img(optionRect);
            //保存各选项灰度和
            questionGraySum.at<int>(0, j) = (int)cv::sum(optionImg).val[0];

			double val = GetEmptyRate(img2(optionRect));
			questionGraySum.at<int>(1, j) = (int)(val * 128  + 0.5);

            j++;
        }
    }
    //如果竖排
    else
    {
        step = img.rows/num;
        optionRect = Rect(0,0,img.cols,(int)step);
        Mat optionImg;
        int j=0;
        for (int i=0;i<num;i=i+interval+1)
        {
            optionRect.y=min((int)step*i,img.rows-optionRect.height);
            //取出每个选项区域并反相
            optionImg = 255-img(optionRect);
            //保存各选项灰度和
            questionGraySum.at<int>(0, j) = (int)cv::sum(optionImg).val[0];

			double val = GetEmptyRate(img2(optionRect));
			questionGraySum.at<int>(1, j) = (int)(val * 128  + 0.5);
            j++;
        }
    }
	pfpt_info.type = type;
    pfpt_info.bkInfo= questionGraySum;
    return pfpt_info;
}

PerQuestionBackground_info  GetPerQuestionBackground_info(Mat img2,int num,bool isCrosswise){
	PerQuestionBackground_info  pq_info;
    Scalar s;
    Mat srcimg;
    img2.copyTo(srcimg);
	srcimg = 255-srcimg;
	Mat grayvalue(2,num,CV_32S,s);
	short type=num;  
	Rect itemrt;
	itemrt.x=0;
	itemrt.y=0;
	if (!isCrosswise)
	{
		itemrt.width=img2.size().width;
		itemrt.height=int(img2.size().height/num);
		for (int i=0;i<num;i++)
		{

			Mat item=srcimg(itemrt);
			double val = GetEmptyRate(img2(itemrt));
			s=sum(item);
			grayvalue.at<int>(0,i)= (int)s.val[0];
			grayvalue.at<int>(1,i)= (int)(val * 128  + 0.5);
			itemrt.y=itemrt.y+itemrt.height;
		}
		pq_info.bkInfo=grayvalue;
		pq_info.type=num;
		return pq_info;
	}
	else {
		itemrt.height=img2.size().height;
		itemrt.width=int(img2.size().width/num);
		for (int i=0;i<num;i++)
		{
			Mat item=srcimg(itemrt);
			double val = GetEmptyRate(img2(itemrt));
			s=sum(item);
			grayvalue.at<int>(0,i)= (int)s.val[0];
			grayvalue.at<int>(1,i)= (int)(val * 128 + 0.5);
			itemrt.x=itemrt.x+itemrt.width;
		}
		pq_info.bkInfo=grayvalue;
		pq_info.type=num;
		return pq_info;
	}
}
