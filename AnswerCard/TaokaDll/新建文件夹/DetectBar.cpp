#include "stdafx.h"
#include "DetectBar.h"

//条形码与二维码识别，Mat必须为灰度图片，否则识别不出结果,且Mat需为一幅子图像，不能为roi子区域。
bool GetBar(Mat bar,string &str)
{
	if(bar.channels()!=1)
	{
		cout<<"图片不是灰度图片"<<endl;
		return FALSE;
	}
	bool flag=FALSE;
	// create a reader
	ImageScanner scanner;
	// configure the reader
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);     //zbar设置
//	scanner.set_config(ZBAR_CODE128, ZBAR_CFG_ENABLE,1);
	const void *raw = bar.data;
	int width=bar.size().width;
	int height=bar.size().height;
		// wrap image data
	Image image(width, height, "Y800", raw, width * height);   //创建zabr中的图像结果image

		// scan the image for barcodes
		int n = scanner.scan(image);               //条码识别api
		if(n!=0)
		{		flag=TRUE;
			// extract results
				for(Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end();  ++symbol) {
					// do something useful with results
					if(str.compare(symbol->get_data())!=0){
/*						cout <<"   "<< "decoded " << symbol->get_type_name()
						<< " symbol \"" << symbol->get_data() << '"' << endl;
						*/
						str=symbol->get_data();      //获取识别结果字符串
					} 
				}
		}

	return flag;
}
////条形码检测；src为源图像，Rect为条形码所在区域。
bool GetBar(Mat src,Rect rect,string &str)
{
	bool flag;
	if(src.channels()!=1)
	{
		cvtColor(src,src,CV_RGB2GRAY);     //如果源图像不是单通道灰度图则转为单通道灰度图。
	}
	Mat roi;
	src(rect).convertTo(roi,0,1,0);        //提取条码所在区域图像
	flag=GetBar(roi,str);                  //条码识别，str为结果字符串
	return flag;
}
int GetBar(Mat src,vector<Bar_info> barGroup,vector<BarResult> &barResult,double xRangeScale,double yRangeScale)
{
	bool flag;
	int num=barGroup.size();
	if(src.channels()!=1)
	{
		cvtColor(src,src,CV_RGB2GRAY);     //如果源图像不是单通道灰度图则转为单通道灰度图。
	}
	Mat roi;
	for(int i=0;i<num;i++)
	{
		BarResult bar;
		Rect roiRect;
		bar.errflag=false;
		bar.barType=barGroup[i].barType;
		roiRect.width=barGroup[i].pos.width*(1+xRangeScale);
		roiRect.height=barGroup[i].pos.height*(1+yRangeScale);
		roiRect.width=MIN(roiRect.width,src.cols);
		roiRect.height=MIN(roiRect.height,src.rows);
		roiRect.x=MIN(MAX(barGroup[i].pos.x - ((roiRect.width-barGroup[i].pos.width)>>1),0),src.cols-roiRect.width);
		roiRect.y = MIN(MAX(barGroup[i].pos.y - ((roiRect.height-barGroup[i].pos.height)>>1),0),src.rows-roiRect.height);
		src(roiRect).convertTo(roi,0,1,0);        //提取条码所在区域图像

//		flag=GetBar(src,bar.bar);
		flag=GetBar(roi,bar.bar);
		if(!flag)
		{
			src(roiRect).convertTo(roi,-1,2,15);
			flag=GetBar(roi,bar.bar);
			bar.errflag=(!flag);
		}
		barResult.push_back(bar);
	}
	return 0;
}

int GetBar(Mat src,vector<Bar_info> barGroup,vector<BarResult> &barResult)
{
	bool flag;
	int num=barGroup.size();
	if(src.channels()!=1)
	{
		cvtColor(src,src,CV_RGB2GRAY);     //如果源图像不是单通道灰度图则转为单通道灰度图。
	}
	Mat roi;
	for(int i=0;i<num;i++)
	{
		BarResult bar;
		Rect roiRect;
		bar.errflag=false;
		bar.barType=barGroup[i].barType;
		roiRect.width=barGroup[i].pos.width*(1+0.2);
		roiRect.height=barGroup[i].pos.height*(1+0.2);
		roiRect.width=MIN(roiRect.width,src.cols);
		roiRect.height=MIN(roiRect.height,src.rows);
		roiRect.x=MIN(MAX(barGroup[i].pos.x - ((roiRect.width-barGroup[i].pos.width)>>1),0),src.cols-roiRect.width);
		roiRect.y = MIN(MAX(barGroup[i].pos.y - ((roiRect.height-barGroup[i].pos.height)>>1),0),src.rows-roiRect.height);
		src(roiRect).convertTo(roi,0,1,0);        //提取条码所在区域图像
		flag=GetBar(roi,bar.bar);
		if(!flag)
			return i;
		barResult.push_back(bar);
	}
	return 0;
}