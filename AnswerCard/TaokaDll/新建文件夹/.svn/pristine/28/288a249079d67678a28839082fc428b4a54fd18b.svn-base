 #include "stdafx.h"
#include"cv.h"
#include "DetectAnswer.h"
#include"ACStructs.h"
#include <highgui.h>
using namespace cv;
#include <map>
Point GetMinCropArea(MarkersBoundaryTable &mbt,vector<FillingPoints_info3> fillingPointGroup)
{
	Point minRightBottom;
	minRightBottom.x = mbt.GetRBoundary(mbt.GetXmarkerNum()-1);
	minRightBottom.y = mbt.GetBBoundary(mbt.GetYmarkerNum()-1);

	for(vector<FillingPoints_info3>::iterator fpIter=fillingPointGroup.begin();fpIter!=fillingPointGroup.end();++fpIter)  
	{  
		for(vector<FillingpointItemPos>::iterator fpItemIter=fpIter->fillingPoints.begin();fpItemIter!=fpIter->fillingPoints.end();++fpItemIter)  
		{  
			for(vector<Rect>::iterator itemIter=fpItemIter->pos.begin();itemIter!=fpItemIter->pos.end();++itemIter)  
			{  
				Point tmpPt = itemIter->br();
				if (tmpPt.x>minRightBottom.x)
				{
					minRightBottom.x = tmpPt.x;
				}
				if (tmpPt.y>minRightBottom.y)
				{
					minRightBottom.y = tmpPt.y;
				}
			}
		} 
	}
	return minRightBottom;
}
//检测答案  类型一 在原类型二三基础上更改，利用mbt来精确定位没一道题的每个选项的位置
int DetectAnswer1(Mat Img,vector<ItemPos> questionInfo,MarkersBoundaryTable &mbt,AnswerResult &ar,double sensibilityThresh,double areaThreshold)
{
	//题目数量
	int questionNum=questionInfo.size();
	int globalGray=0;
	for(int i=questionNum-1;i>=0;i--)
	{
		PerquestionResult questionResult;
		ItemPos perQuestionInfo = questionInfo[i];
		//计算选项数量
		ushort optionNum;
		if (perQuestionInfo.interval == 0)
			optionNum = perQuestionInfo.markerIdx[2]-perQuestionInfo.markerIdx[1]+1;
		else
			optionNum = (perQuestionInfo.markerIdx[2]-perQuestionInfo.markerIdx[1]+perQuestionInfo.interval)/(perQuestionInfo.interval+1)+1; 
		
		questionResult.questionId=perQuestionInfo.id;
		//设置小题区域
		Rect roiRect = mbt.GetQuestionBoundry(perQuestionInfo);
		Mat roi=Img(roiRect);
		Point rectPos(roiRect.x,roiRect.y);
		//检测结果
		
		int returnValue = DetectPreQuestionAnswer1(roi,globalGray,mbt,rectPos,perQuestionInfo,optionNum,sensibilityThresh,areaThreshold,questionResult);
		//检测错误
		if (returnValue)
			return returnValue;
		//中心位置加上偏移值
		for (int i =0;i<questionResult.answerPos.size();i++)
		{
			questionResult.answerPos[i].x += roiRect.x;
			questionResult.answerPos[i].y += roiRect.y;
		}


		ar.answer.push_back(questionResult);
	}
	return 0;
}

//检测答案  类型二、三
int DetectAnswer(Mat Img,vector<ItemPos> questionInfo,MarkersBoundaryTable &mbt,AnswerResult &ar,bool questionType,double sensibilityThresh,double areaThreshold,int seSize)
{
	//题目数量
	int questionNum=questionInfo.size();
	for(int i=questionNum-1;i>=0;i--)
	{
		PerquestionResult questionResult;
		ItemPos perQuestionInfo = questionInfo[i];
		//计算选项数量
		ushort optionNum;
		if (perQuestionInfo.interval == 0)
			optionNum = perQuestionInfo.markerIdx[2]-perQuestionInfo.markerIdx[1]+1;
		else
			optionNum = (perQuestionInfo.markerIdx[2]-perQuestionInfo.markerIdx[1]+perQuestionInfo.interval)/(perQuestionInfo.interval+1)+1; 

		//找到与选项数量匹配的背景
		Mat bkInfo;

		questionResult.questionId=perQuestionInfo.id;
		//设置小题区域
		Rect roiRect = mbt.GetQuestionBoundry(perQuestionInfo);
		Mat roi=Img(roiRect);

	/*	cout<<"questionId:"<<perQuestionInfo.id<<endl;*/

		//检测结果
		int returnValue = DetectPreQuestionAnswer(roi,perQuestionInfo.isCrosswise,perQuestionInfo.isSingleChoice,optionNum,questionType,sensibilityThresh,areaThreshold,seSize,questionResult);

		//检测错误
		if (returnValue)
			return returnValue;
		//中心位置加上偏移值
		for (int i =0;i<questionResult.answerPos.size();i++)
		{
			questionResult.answerPos[i].x += roiRect.x;
			questionResult.answerPos[i].y += roiRect.y;
		}


		ar.answer.push_back(questionResult);
	}
	return 0;
}

//检测答案 类型三多组
int DetectAnswer(Mat Img,vector<ItemPos> questionInfo,map<ushort,MarkersBoundaryTable*> &mbtMap,AnswerResult &ar,bool questionType,double sensibilityThresh,double areaThreshold,int seSize)
{
	MarkersBoundaryTable *mbt;
	//题目数量
	int questionNum=questionInfo.size();
	for(int i=questionNum-1;i>=0;i--)
	{
		PerquestionResult questionResult;
		ItemPos perQuestionInfo = questionInfo[i];
		//计算选项数量
		ushort optionNum;
		if (perQuestionInfo.interval == 0)
			optionNum = perQuestionInfo.markerIdx[2]-perQuestionInfo.markerIdx[1]+1;
		else
			optionNum = (perQuestionInfo.markerIdx[2]-perQuestionInfo.markerIdx[1]+perQuestionInfo.interval)/(perQuestionInfo.interval+1)+1; 

		//找到与选项数量匹配的背景
//		Mat bkInfo;
		if (mbtMap.find(perQuestionInfo.mark_id)!=mbtMap.end())
		{
			mbt=mbtMap[perQuestionInfo.mark_id];
		}
		else
			return i+1;
		questionResult.questionId=perQuestionInfo.id;
		//设置小题区域
		Rect roiRect = (*mbt).GetQuestionBoundry(perQuestionInfo);
		Mat roi=Img(roiRect);

		//检测结果
		int returnValue = DetectPreQuestionAnswer(roi,perQuestionInfo.isCrosswise,perQuestionInfo.isSingleChoice,optionNum,questionType,sensibilityThresh,areaThreshold,seSize,questionResult);

		//检测错误
		if (returnValue)
			return returnValue;
		//中心位置加上偏移值
		for (int i =0;i<questionResult.answerPos.size();i++)
		{
			questionResult.answerPos[i].x += roiRect.x;
			questionResult.answerPos[i].y += roiRect.y;
		}


		ar.answer.push_back(questionResult);
	}
	return 0;

}

//////////////////////////////////////////////////////////////////////////
///检测每道题答案 类型三
int DetectPreQuestionAnswer( Mat roi,bool isCrosswise,bool isSingleChoice,int optionNum,bool quetionType,double sensibilityThresh,double areaThreshold,int seSizeTh,PerquestionResult &result)  //0.正常 1.没有填涂
{
	result.answer = 0;
	result.suspectFlag = 0;


	//选项矩形
	Rect optionRect;
	double step;
	if(isCrosswise)
	{
		step = (double)roi.cols/optionNum;
		optionRect = Rect(0,0,(int)step,roi.rows);
	}else
	{
		step = (double)roi.rows/optionNum;
		optionRect = Rect(0,0,roi.cols,(int)step);
	}

	//形态学闭操作
	Mat closed_roi,bw_roi;
	cv::Size seSize(3,3);
	if(quetionType)         //如果选择题中有字母
	{
		seSize.width = MAX(6,(optionRect.width>>1)-(optionRect.width>>3));
		seSize.height= optionRect.height>>2;
	/*	seSize.width = optionRect.width>>2;
		seSize.height= optionRect.height>>2;*/
	}
	else
	{
		seSize.width = optionRect.width>>2;
		seSize.height= optionRect.height>>2;
	}
	if (seSizeTh>0)
	{
		seSize.width = optionRect.width>>2;
		seSize.height= optionRect.height>>2;
	}
	Mat se = getStructuringElement(MORPH_RECT,seSize);
	cv::morphologyEx(roi,closed_roi,MORPH_CLOSE,se);
	
	double t = threshold(closed_roi,bw_roi,128,255,THRESH_OTSU);
/*	cout<<t<<endl;*/


	if(t>240||t==0)
	{
		
		if (quetionType)
		{
			if (isCrosswise)
			{
				seSize.width =MAX(6,(optionRect.width>>1)-(optionRect.width>>4));
				seSize.height= optionRect.height>>2;
				Mat se = getStructuringElement(MORPH_RECT,seSize);
				cv::morphologyEx(roi,closed_roi,MORPH_CLOSE,se);
				int bwThresh=220;
				if (seSizeTh>0)
				{
					bwThresh=235;
				}
				threshold(closed_roi,bw_roi,bwThresh,255,THRESH_BINARY);
			} 
			else
			{
				seSize.width =MAX(6,(optionRect.width>>2)/*+(optionRect.width>>4)*/);
				seSize.height= optionRect.height>>2;
				Mat se = getStructuringElement(MORPH_RECT,seSize);
				cv::morphologyEx(roi,closed_roi,MORPH_CLOSE,se);
				int bwThresh=235;
				if (seSizeTh>0)
				{
					bwThresh=245;
				}
				threshold(closed_roi,bw_roi,bwThresh,255,THRESH_BINARY);
			}
			
			
		} 
		else
		{
			/*int bwThresh=MIN(t,245);*/
			threshold(closed_roi,bw_roi,240,255,THRESH_BINARY);
		}
		
	}

	//imshow("closroiiiii",closed_roi);
	//imshow("bwaaaa",bw_roi);
	//waitKey();

	closed_roi=255-closed_roi;
	bw_roi=255-bw_roi;
	Mat opImg=bw_roi&(255-roi);
	Mat qsTypeImg=bw_roi&closed_roi;

	  //	imshow("test",roi);
	 	//imshow("test2",closed_roi);
	  //	waitKey(0);

	//计算灰度和
	Mat questionGraySum(1,optionNum,CV_32S),qsArea(1,optionNum,CV_32S),avgGray(1,optionNum,CV_32S);;
	Mat optionImg,bwoptionImg;
	//如果横排
	if(isCrosswise)
	{
		Mat optionImg;
		for (int i=0;i<optionNum;i++)
		{
			optionRect.x=min((int)(step*i)+1,roi.cols-optionRect.width);
			//取出每个选项区域并反相
			optionImg = closed_roi(optionRect);
			bwoptionImg= bw_roi(optionRect);
			Mat oImg=opImg(optionRect);

	/*		imshow("testbbb",roi(optionRect));
			waitKey();*/
			//保存各选项灰度和
			if (quetionType)
			{
				questionGraySum.at<int>(i) = (int)cv::sum(qsTypeImg(optionRect)).val[0];
			} 
			else
			{
				questionGraySum.at<int>(i) = (int)cv::sum(optionImg).val[0];
			}
			
			int area=cv::sum(bwoptionImg).val[0]/255;
			qsArea.at<int>(i)=area;
			if(area<12)
				avgGray.at<int>(i)=0;
			else
				avgGray.at<int>(i)=(int)cv::sum(oImg).val[0]/(area);
		}
	}
	//如果竖排
	else
	{
		Mat optionImg;
		for (int i=0;i<optionNum;i++)
		{
			optionRect.y=min((int)(step*i+0.5),roi.rows-optionRect.height);
			//取出每个选项区域并反相
			optionImg = closed_roi(optionRect);
			bwoptionImg= bw_roi(optionRect);
			Mat oImg=opImg(optionRect);

	/*		imshow("testbbb",roi(optionRect));
			waitKey();*/
			//保存各选项灰度和
			if (quetionType)
			{
				questionGraySum.at<int>(i) = (int)cv::sum(qsTypeImg(optionRect)).val[0];
			} 
			else
			{
				questionGraySum.at<int>(i) = (int)cv::sum(optionImg).val[0];
			}
			
			int area=cv::sum(bwoptionImg).val[0]/255;
			qsArea.at<int>(i)=area;
			if(area<12)
				avgGray.at<int>(i)=0;
			else
				avgGray.at<int>(i)=(int)cv::sum(oImg).val[0]/(area);
		}
	} 
	//求最大值
	double minValue,maxVaule;
	int minIdx[2],maxIdx[2];

 	//
 /*	cout<<"questionId:"<<result.questionId<<endl;
 	cout<<t<<endl;
 	imshow("testjjjj",roi);
 	imshow("test2",255-closed_roi);
 	imshow("bw",bw_roi);
 	cout<<questionGraySum<<endl;
 	cout<<qsArea<<endl;
 	cout<<avgGray<<endl;
 	waitKey(0);*/

	cv::minMaxIdx(questionGraySum,&minValue,&maxVaule,minIdx,maxIdx);
	//求最大平均灰度
	int maxAvgGray=0;
	int maxAvgGrayId=0;
	for(int i=0;i<optionNum;i++)
	{
		if(avgGray.at<int>(i)>maxAvgGray)
		{
			maxAvgGray=avgGray.at<int>(i);
			maxAvgGrayId=i;
		}
	}

	//if (avgGray.at<int>(maxIdx[1]) + 10<maxAvgGray&&qsArea.at<int>(maxAvgGrayId) > qsArea.at<int>(maxIdx[1])*0.45)
	//{
	//	cout<<"questionId:"<<result.questionId<<endl;
	//	cout<<t<<endl;
	//	imshow("testjjjj",roi);
	//	imshow("test2",255-closed_roi);
	//	imshow("bw",bw_roi);
	//	cout<<questionGraySum<<endl;
	//	cout<<qsArea<<endl;
	//	cout<<avgGray<<endl;
	//	waitKey();

	//	questionGraySum.at<int>(maxIdx[1])=questionGraySum.at<int>(maxAvgGrayId)*0.9;
	//	avgGray.at<int>(maxIdx[1])=avgGray.at<int>(maxIdx[1])*0.85;
	//	cv::minMaxIdx(questionGraySum,&minValue,&maxVaule,minIdx,maxIdx);

	//}

	//一致性阈值设置
	double suspect_upperBound,suspect_lowerBound,grayThresh;
	if (isSingleChoice)
	{
		suspect_upperBound = 0.6;
		suspect_lowerBound = 0.55;
		if (quetionType)
		{
			grayThresh=0.8*(1+sensibilityThresh);
		} 
		else
		{
			grayThresh=0.75*(1+sensibilityThresh);
		}
		
	} 
	else
	{
		
		if(quetionType)         //如果选择题中有字母
		{
			suspect_upperBound = 0.5;
			suspect_lowerBound = 0.3;
			grayThresh=0.6*(1+sensibilityThresh);
		}
		else
		{
			suspect_upperBound = 0.5;
			suspect_lowerBound = 0.2;
			grayThresh = 0.5*(1+sensibilityThresh);
		}
	}

	result.suspectFlag=0;

	int threshold_filled,threshold_suspect,threshold_true_filled,threshold_may_filled;
	if (quetionType)
	{
		threshold_filled = optionRect.area()*3*(1+areaThreshold);
		threshold_suspect = threshold_filled*.5;
	}
	else
	{
		threshold_filled = optionRect.area()*3*(1+areaThreshold);
		threshold_suspect = threshold_filled*.5;
	}

	/*cout<<threshold_filled<<endl;*/

	//最大值大于填涂阈值，则不是空选项
	if (maxVaule>threshold_filled)
	{
		//int maxDiffValue = max(threshold_filled,(int)(maxVaule*(suspect_upperBound+0.2*sensibilityThresh)));
		//int suspectValue = max(threshold_filled,(int)(maxVaule*(suspect_lowerBound+0.2*sensibilityThresh)));
		int maxDiffValue =(int)(maxVaule*(suspect_upperBound+0.2*sensibilityThresh));
		int suspectValue = (int)(maxVaule*(suspect_lowerBound+0.2*sensibilityThresh));
		result.answer = 0;
		for (int i=0;i<optionNum;i++)
		{
			//一致性判断
			if (questionGraySum.at<int>(i)>maxDiffValue)
			{
				if (avgGray.at<int>(i)>maxAvgGray*grayThresh)      //利用平均灰度去除多选
				{
					result.answer = result.answer|(1<<i);
					if (isCrosswise)
					{
						Point point;
						point.x = (int)((i+0.5)*step);
						point.y = roi.rows>>1;
						result.answerPos.push_back(point);

					}else
					{
						Point point;
						point.y = (int)((i+0.5)*step);
						point.x = roi.cols>>1;
						result.answerPos.push_back(point);
					}
				}
				else if (avgGray.at<int>(i)>maxAvgGray*0.6)
				{
					result.suspectFlag=3;
				}
				

			}//填涂一致性可疑判断
			else if (questionGraySum.at<int>(i)>suspectValue)
			{
				if (avgGray.at<int>(i)>maxAvgGray*grayThresh)
				{
					result.answer = result.answer|(1<<i);
					if (isCrosswise)
					{
						Point point;
						point.x = (int)((i+0.5)*step);
						point.y = roi.rows>>1;
						result.answerPos.push_back(point);

					}else
					{
						Point point;
						point.y = (int)((i+0.5)*step);
						point.x = roi.cols>>1;
						result.answerPos.push_back(point);
					}
				}
				else if (avgGray.at<int>(i)>maxAvgGray*0.57)
					result.suspectFlag = 1;
			}
		}
	}
	else if (maxVaule>threshold_suspect)
	{
		result.suspectFlag = 2;
		result.answer=0;
	}else{
		result.answer = 0;
	}
	return 0;
}


//检测每道题答案 类型 一 修改每个填涂位置的计算方法 改为利用mbt来精确定位每小题的每个选项区域
int DetectPreQuestionAnswer1( Mat roi,int &globalGray,MarkersBoundaryTable &mbt,Point rectPos,ItemPos perQuestionInfo,int optionNum,double sensibilityThresh,double areaThreshold,PerquestionResult &result)  //0.正常 1.没有填涂
{
	bool isCrosswise=perQuestionInfo.isCrosswise;
	bool isSingleChoice=perQuestionInfo.isSingleChoice;
	result.answer = 0;
	result.suspectFlag = 0;
	//选项矩形
	Rect optionRect;
	double step = 0;
	int bwthresh=246;
	if (areaThreshold<0)
	{
		bwthresh=247;
	}
	if(isCrosswise)
	{
		step = (double)roi.cols/optionNum;
		optionRect = Rect(0,0,(int)step,roi.rows);
	}else
	{
		step = (double)roi.rows/optionNum;
		optionRect = Rect(0,0,roi.cols,(int)step);
	}
	//形态学闭操作
	Mat closed_roi,bw_roi,bwRoi;

	cv::Size seSize;
	//seSize.width=2;
	//seSize.height=2;
//	Mat se = getStructuringElement(MORPH_RECT,seSize);
//	cv::morphologyEx(roi,closed_roi,MORPH_CLOSE,se);
	seSize.width = MAX(optionRect.width>>2,6);
	seSize.height= 4;
	Mat se = getStructuringElement(MORPH_RECT,seSize);
	cv::morphologyEx(roi,closed_roi,MORPH_CLOSE,se);
	double t = threshold(closed_roi,bwRoi,128,255,THRESH_OTSU);
	double tt=MIN(bwthresh,t*1.1);
	threshold(closed_roi,bw_roi,tt,255,THRESH_BINARY);
	threshold(closed_roi,bwRoi,tt-6,255,THRESH_BINARY);
// 
//  	cout<<perQuestionInfo.id<<"   "<<t<<endl;
// 	imshow("roiaaaa",roi);
// 	waitKey();
	if(optionNum<8&&(t>250||t==0))
	{
		return 0;
	}
	seSize.width=3;
	seSize.height=1;
	se = getStructuringElement(MORPH_RECT,seSize);
	cv::morphologyEx(bwRoi,bwRoi,MORPH_OPEN,se);
   /*	imshow("bwaaaaa",bwRoi);
  	imshow("bwbbbb",bw_roi);
   	waitKey();*/
	//去除直线污染问题
	vector<vector<Point> > contours;    //轮廓数组（非矩形数组），每个轮廓是一个Point型的vector
	bwRoi=255-bwRoi;
	findContours(bwRoi,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );
	Rect questRect;
	for(int i = contours.size()-1;i>=0; i-- )
	{
		questRect = boundingRect(contours[i]);
		if (MAX(questRect.width,questRect.height) >optionRect.width*1.5 && MIN(questRect.width,questRect.height) < MIN(optionRect.height,optionRect.width)*.3)
		{
			return 0;
		}
	}

 	bw_roi=255-bw_roi;
	Mat OpImg=bw_roi&(255-roi);
	Mat opCloseRoi=255-closed_roi;
	//计算灰度和
	Mat questionGraySum(1,optionNum,CV_32S),qsArea(1,optionNum,CV_32S),qsAvgGray(1,optionNum,CV_32S);
	perQuestionInfo.markerIdx[2]=perQuestionInfo.markerIdx[1];
	Mat optionImg,bwoptionImg;
	for (int i=0;i<optionNum;i++)
	{

//		optionRect.y=min((int)step*i,roi.rows-optionRect.height);
		optionRect=mbt.GetQuestionBoundry(perQuestionInfo);
		optionRect.x-=rectPos.x;
		optionRect.y-=rectPos.y; 
		//取出每个选项区域并反相
		bwoptionImg= bw_roi(optionRect);
		Mat oImg=OpImg(optionRect);
		questionGraySum.at<int>(i)=cv::sum(opCloseRoi(optionRect)).val[0];
		//保存各选项灰度和
		/*bwoptionImg=255-bwoptionImg;*/
		int area=cv::sum(bwoptionImg).val[0]/255;
		qsArea.at<int>(i)=area; 
		if(area<optionRect.area()*0.07)
			qsAvgGray.at<int>(i)=0;
		else
			qsAvgGray.at<int>(i)=cv::sum(oImg).val[0]/(area);  
		perQuestionInfo.markerIdx[1]+=(perQuestionInfo.interval+1);
		perQuestionInfo.markerIdx[2]+=(perQuestionInfo.interval+1);
	}
	//求最大值
	double minValue,maxVaule;
	int minIdx[2],maxIdx[2];
//    
//            	cout<<"queId:"<<perQuestionInfo.id<<endl;
//            	imshow("roi",roi);
//            	imshow("closeroi",closed_roi);
//            	imshow("bwroi",bwRoi);
//            	imshow("bw",255-bw_roi);
//            	cout<<questionGraySum<<endl;
//            	cout<<qsArea<<endl;
//            	cout<<qsAvgGray<<endl;
//            	waitKey(0);


	cv::minMaxIdx(questionGraySum,&minValue,&maxVaule,minIdx,maxIdx);
	//计算选项的平均灰度的平均值
	int avgAvgGray=0,graySum=0,grayCont=0;
	int maxAvgGray=0;
	int maxAvgGrayId=0;
	int maxArea=0;
	for(int i=0;i<optionNum;i++)
	{
		if(qsAvgGray.at<int>(i)>maxAvgGray)
		{
			maxAvgGray=qsAvgGray.at<int>(i);
			maxAvgGrayId=i;
		}
		if(qsArea.at<int>(i)>maxArea)
			maxArea=qsArea.at<int>(i);
		if (qsArea.at<int>(i)>10&&qsAvgGray.at<int>(i)>0)
		{
			graySum+=qsAvgGray.at<int>(i);
			grayCont++;
		}
	}
	if (qsAvgGray.at<int>(maxIdx[1]) + 5<maxAvgGray&&qsArea.at<int>(maxAvgGrayId) > qsArea.at<int>(maxIdx[1])*0.45)
	{
		questionGraySum.at<int>(maxIdx[1])=questionGraySum.at<int>(maxAvgGrayId)*0.9;
		qsAvgGray.at<int>(maxIdx[1])=qsAvgGray.at<int>(maxIdx[1])*0.85;
		cv::minMaxIdx(questionGraySum,&minValue,&maxVaule,minIdx,maxIdx);

	}

	if(grayCont)
		avgAvgGray=graySum/grayCont;
	double globGrayThresh=globalGray*(0.55+0.4*sensibilityThresh);
	double devThresh;
	int minGlobeTh=14;
	if (areaThreshold<0)
	{
		minGlobeTh=10;
	}
	if (optionNum<5)
	{
		devThresh=7.8;
	} 
	else
	{
		devThresh=3;
	}
	if (t>225)
	{
		cv::Scalar imgMean,imgDev;
		meanStdDev(roi,imgMean,imgDev);
		if(imgDev.val[0]<devThresh)
			return 0;
		if (globGrayThresh<minGlobeTh)
		{
			globGrayThresh=minGlobeTh;
		}
		if(maxAvgGray<globGrayThresh&&imgDev.val[0]<12)
			return 0;
		if (maxAvgGray<26&&maxArea>optionRect.area()*0.7)
		{
			return 0;
		}
	}

	//一致性阈值设置
	double suspect_upperBound,suspect_lowerBound;
	int graythresh,graythresh_lowerBound;
	if (isSingleChoice)
	{
		suspect_upperBound = 0.9;
		suspect_lowerBound = 0.7;
		graythresh=MAX(globGrayThresh,maxAvgGray*0.85);
		graythresh_lowerBound=MAX(globGrayThresh,maxAvgGray)*0.8;
	} 
	else
	{
		suspect_upperBound = 0.6;
		suspect_lowerBound = 0.3;
		graythresh=MAX(globGrayThresh*0.8, (maxAvgGray+qsAvgGray.at<int>(maxIdx[1]))*suspect_upperBound/2 )*(1+sensibilityThresh);
		graythresh_lowerBound=MAX(globGrayThresh,maxAvgGray)*suspect_upperBound*(1+sensibilityThresh);
	}

	result.suspectFlag=0;

	int threshold_filled,threshold_suspect,threshold_true_filled,threshold_may_filled;
// 
 	threshold_filled = optionRect.area()*9.2*(1+1.3*areaThreshold);
 	threshold_suspect = threshold_filled*.7;

//	cout<<threshold_filled<<endl;


	//最大值大于填涂阈值，则不是空选项
	if (maxVaule>threshold_filled)
	{
		int maxDiffValue = (int)(maxVaule*MIN(1,(suspect_upperBound+0.6*sensibilityThresh)));
		int suspectValue = (int)(maxVaule*MIN(1,(suspect_lowerBound+0.3*sensibilityThresh)));
		result.answer = 0;
		for (int i=0;i<optionNum;i++)
		{
			//一致性判断
			if (questionGraySum.at<int>(i)>maxDiffValue&&qsAvgGray.at<int>(i)>graythresh)
			{
				result.answer = result.answer|(1<<i);
				//更新全局灰度化的阈值 只往小更新
				if (globalGray>0)
				{
					if (globalGray>qsAvgGray.at<int>(i))
					{
						globalGray=(globalGray+qsAvgGray.at<int>(i))>>1;
					}
				} 
				else
				{
					globalGray=qsAvgGray.at<int>(i);
				}
				if (isCrosswise)
				{
					Point point;
					point.x = (int)((i+0.5)*step);
					point.y = roi.rows>>1;
					result.answerPos.push_back(point);

				}else
				{
					Point point;
					point.y = (int)((i+0.5)*step);
					point.x = roi.cols>>1;
					result.answerPos.push_back(point);
				}

			}//填涂一致性可疑判断
			else if (questionGraySum.at<int>(i)>suspectValue)
			{
				int graythreshMiddle;
				if(isSingleChoice)
					graythreshMiddle=graythresh_lowerBound;
				else
					graythreshMiddle=(avgAvgGray+qsAvgGray.at<int>(maxIdx[1]))*suspect_upperBound/2;
				if(qsAvgGray.at<int>(i)>graythreshMiddle&&qsArea.at<int>(i)>qsArea.at<int>(maxIdx[1])*0.5)
				{
					result.answer = result.answer|(1<<i);
					//更新全局灰度化的阈值 只往小更新
					if (globalGray>0)
					{
						if (globalGray>qsAvgGray.at<int>(i))
						{
							globalGray=(globalGray+qsAvgGray.at<int>(i))>>1;
						}
					} 
					else
					{
						globalGray=qsAvgGray.at<int>(i);
					}
					if (isCrosswise)
					{
						Point point;
						point.x = (int)((i+0.5)*step);
						point.y = roi.rows>>1;
						result.answerPos.push_back(point);

					}else
					{
						Point point;
						point.y = (int)((i+0.5)*step);
						point.x = roi.cols>>1;
						result.answerPos.push_back(point);
					}
				}                                             //avgGray为几个填涂点的平均灰度的平均值
				else if(qsArea.at<int>(i)>qsArea.at<int>(maxIdx[1])*suspect_lowerBound&&qsAvgGray.at<int>(i)>graythresh_lowerBound)
				{
					result.answer = result.answer|(1<<i);
					if (isCrosswise)
					{
						Point point;
						point.x = (int)((i+0.5)*step);
						point.y = roi.rows>>1;
						result.answerPos.push_back(point);

					}else
					{
						Point point;
						point.y = (int)((i+0.5)*step);
						point.x = roi.cols>>1;
						result.answerPos.push_back(point);
					}
						result.suspectFlag = 1;
				}
			}
		}
	}
	else if (maxVaule>threshold_suspect)
	{
		result.suspectFlag = 2;
		result.answer=0;
	}else{
		result.answer = 0;
	}
	return 0;
}

