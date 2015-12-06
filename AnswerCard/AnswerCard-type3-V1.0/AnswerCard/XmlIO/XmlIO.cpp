
#include "XmlIo.h"
#include "ChineseCode.h"

XmlIo::XmlIo(void)
{
}


XmlIo::~XmlIo(void)
{
}
//////////////////////////////////写////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
int XmlIo::Write(string filename,AC_info acInfo)
{

	xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");
	xmlNodePtr root_node = xmlNewNode(NULL,BAD_CAST"AnswerCardInfo");
	//设置根节点
	xmlDocSetRootElement(doc,root_node);

	//试卷类型
	xmlAddChild(root_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("试卷类型").c_str()) ));
	xmlNewTextChild(root_node, NULL, BAD_CAST "ac_id", BAD_CAST (acInfo.ac_id.c_str()));

	//分辨率
	xmlAddChild(root_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("分辨率").c_str()) ));
	xmlNewTextChild(root_node, NULL, BAD_CAST "dpi", BAD_CAST (dtc.Int2String(acInfo.dpi).c_str()));

	//定位点信息
	WriteAnchorPointInfo(root_node,acInfo.anchorPointInfo);

	//标记点信息
	WriteMarkerInfo(root_node,acInfo.markerInfo);

	//条码信息
	WriteBarInfo(root_node,acInfo.barGroup);

	//预定义填涂点组
	WriteFillingPointsInfo(root_node,acInfo.fillingPointGroup);

	//填涂点背景信息
	WriteFillingPointBackgroundInfo(root_node,acInfo.fillingPointBackgroundInfo);

	//题目信息
	WriteQuestionInfo(root_node,acInfo.questioninfo);

	//题目背景信息
	WriteQuestionBackgroundInfo(root_node,acInfo.questionBackgroundInfo);

	//裁切区域信息
	WriteCropAreaInfo(root_node,acInfo.cropAreaInfo);
	//格式化输出到文件
	//int nRel = xmlSaveFile(filename.c_str(),doc);
	int nRel = xmlSaveFormatFileEnc( filename.c_str(), doc, "UTF-8",1);
	if (nRel != -1)
	{
		cout<<"一个xml文档被创建,写入"<<nRel<<"个字节"<<endl;
	}
	//释放文档内节点动态申请的内存
	xmlFreeDoc(doc);
	return 0;
}
int XmlIo::Write(string filename,AC_info3 acInfo)
{

	xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");
	xmlNodePtr root_node = xmlNewNode(NULL,BAD_CAST"AnswerCardInfo");
	//设置根节点
	xmlDocSetRootElement(doc,root_node);

	//试卷类型
	xmlAddChild(root_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("试卷类型").c_str()) ));
	xmlNewTextChild(root_node, NULL, BAD_CAST "ac_id", BAD_CAST (acInfo.ac_id.c_str()));

	//分辨率
	xmlAddChild(root_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("分辨率").c_str()) ));
	xmlNewTextChild(root_node, NULL, BAD_CAST "dpi", BAD_CAST (dtc.Int2String(acInfo.dpi).c_str()));

	//定位点信息
	WriteAnchorPointInfo(root_node,acInfo.anchorPointInfo);

	//标记点信息
	WriteMarkerInfo3(root_node,acInfo.markerInfo);

	//条码信息
	WriteBarInfo(root_node,acInfo.barGroup);

	//预定义填涂点组
	WriteFillingPointsInfo3(root_node,acInfo.fillingPointGroup);

	//题目信息
	WriteQuestionInfo(root_node,acInfo.questioninfo);

	//题目背景信息
	WriteQuestionBackgroundInfo(root_node,acInfo.questionBackgroundInfo);

	//裁切区域信息
	WriteCropAreaInfo(root_node,acInfo.cropAreaInfo);

	//黑白检测线
	WriteBlackWhiteLine(root_node,acInfo.blackLine,acInfo.whiteLine);
	//格式化输出到文件
	//int nRel = xmlSaveFile(filename.c_str(),doc);
	int nRel = xmlSaveFormatFileEnc( filename.c_str(), doc, "UTF-8",1);
	if (nRel != -1)
	{
		cout<<"一个xml文档被创建,写入"<<nRel<<"个字节"<<endl;
	}
	//释放文档内节点动态申请的内存
	xmlFreeDoc(doc);
	return 0;
}
//////////////////////////////////定位点模块////////////////////////////////////////

int XmlIo::WriteAnchorPointInfo(xmlNodePtr root_node,AnchorPoint_info anchorPointInfo)
{
	//xmlNodePtr cur_node = xmlAddPrevSibling(root_node,xmlNewComment(BAD_CAST"定位点"));
	//xmlAddPrevSibling( root_node, xmlNewComment( BAD_CAST "abc" ));
	//定位点
	xmlAddChild(root_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("定位点").c_str()) ));
	xmlNodePtr anchorPointInfo_node = xmlNewNode(NULL,BAD_CAST"anchorPointInfo");
	xmlAddChild(root_node,anchorPointInfo_node);

	//定位点数量
	xmlAddChild(anchorPointInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("定位点数量").c_str()) ));
	xmlNewTextChild(anchorPointInfo_node, NULL, BAD_CAST "num", BAD_CAST(dtc.Int2String(anchorPointInfo.num).c_str()));

	//定位点类型
	xmlAddChild(anchorPointInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("定位点类型").c_str()) ));
	xmlNewTextChild(anchorPointInfo_node, NULL, BAD_CAST "anchorType", BAD_CAST(dtc.Short2String(anchorPointInfo.anchorType).c_str()));

	//定位点位置信息
	xmlAddChild(anchorPointInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("定位点位置信息").c_str()) ));
	xmlNodePtr anchorPtPosInfo_node = xmlNewNode(NULL,BAD_CAST"anchorPtPosInfo");
	xmlAddChild(anchorPointInfo_node,anchorPtPosInfo_node);
	for (unsigned int i=0;i<anchorPointInfo.anchorPt.size();i++)
	{
		xmlNewTextChild(anchorPtPosInfo_node, NULL, BAD_CAST "perAnchorPtPos", BAD_CAST(dtc.Rect2String(anchorPointInfo.anchorPt[i]).c_str()));
	}

	return 0;
}

////////////////////////////////// 标记点模块//////////////////////////////////////

int XmlIo::WriteMarkerInfo(xmlNodePtr root_node, Marker_info markerInfo)
{
	//标记点
	xmlAddChild(root_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("标记点").c_str()) ));
	xmlNodePtr markerInfo_node = xmlNewNode(NULL,BAD_CAST"markerInfo");
	xmlAddChild(root_node,markerInfo_node);

	//横向标记点数量
	xmlAddChild(markerInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("横向标记点数量").c_str()) ));
	xmlNewTextChild(markerInfo_node, NULL, BAD_CAST "xNum", BAD_CAST(dtc.Int2String(markerInfo.xNum).c_str()));

	//纵向标记点数量
	xmlAddChild(markerInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("纵向标记点数量").c_str()) ));
	xmlNewTextChild(markerInfo_node, NULL, BAD_CAST "yNum", BAD_CAST(dtc.Int2String(markerInfo.yNum).c_str()));

	//横向标记点尺寸
	xmlAddChild(markerInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("横向标记点尺寸").c_str()) ));
	xmlNewTextChild(markerInfo_node, NULL, BAD_CAST "xSize", BAD_CAST(dtc.Size2String(markerInfo.xSize).c_str()));

	//纵向标记点尺寸
	xmlAddChild(markerInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("纵向标记点尺寸").c_str()) ));
	xmlNewTextChild(markerInfo_node, NULL, BAD_CAST "ySize", BAD_CAST(dtc.Size2String(markerInfo.ySize).c_str()));

	//横向标记点组所在区域
	xmlAddChild(markerInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("横向标记点组所在区域").c_str()) ));
	xmlNewTextChild(markerInfo_node, NULL, BAD_CAST "xMarker", BAD_CAST(dtc.Rect2String(markerInfo.xMarker).c_str()));

	//纵向标记点组所在区域
	xmlAddChild(markerInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("纵向标记点组所在区域").c_str()) ));
	xmlNewTextChild(markerInfo_node, NULL, BAD_CAST "yMarker", BAD_CAST(dtc.Rect2String(markerInfo.yMarker).c_str()));

	return 0;
}

int XmlIo::WriteMarkerInfo3(xmlNodePtr root_node, Marker_info3 markerInfo)
{
	//标记点
	xmlAddChild(root_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("虚拟标记点").c_str()) ));
	xmlNodePtr xMarkerInfo_node = xmlNewNode(NULL,BAD_CAST"xMarkerInfo");
	xmlAddChild(root_node,xMarkerInfo_node);
	for (int i=0;i<markerInfo.xMarker.size();i++)
	{
		xmlNewTextChild(xMarkerInfo_node, NULL, BAD_CAST "perMarkerPos", BAD_CAST(dtc.Rect2String(markerInfo.xMarker[i]).c_str()));
	}
	xmlNodePtr yMarkerInfo_node = xmlNewNode(NULL,BAD_CAST"yMarkerInfo");
	xmlAddChild(root_node,yMarkerInfo_node);
	for (int i=0;i<markerInfo.yMarker.size();i++)
	{
		xmlNewTextChild(yMarkerInfo_node, NULL, BAD_CAST "perMarkerPos", BAD_CAST(dtc.Rect2String(markerInfo.yMarker[i]).c_str()));
	}
	return 0;
}
////////////////////////////////////////////条码信息//////////////////////////////

int XmlIo::WriteBarInfo(xmlNodePtr root_node,vector<Bar_info> barGroup)
{
	xmlAddChild(root_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("条码信息").c_str()) ));
	xmlNodePtr barInfo_node = xmlNewNode(NULL,BAD_CAST"barInfo");
	xmlAddChild(root_node,barInfo_node);
	for (unsigned int i=0;i<barGroup.size();i++)
	{
		xmlNodePtr perBarInfo_node = xmlNewNode(NULL,BAD_CAST"perBarInfo");
		xmlAddChild(barInfo_node,perBarInfo_node);
		xmlAddChild(perBarInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("条码类型").c_str()) ));
		xmlNewTextChild(perBarInfo_node,NULL, BAD_CAST "barType", BAD_CAST (dtc.Ushort2String(barGroup[i].barType).c_str()));
		xmlAddChild(perBarInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("条码位置").c_str()) ));
		xmlNewTextChild(perBarInfo_node,NULL, BAD_CAST "pos", BAD_CAST (dtc.Rect2String(barGroup[i].pos).c_str()));
	}
	return 0;
}

///////////////////////////////////////预定义填涂点组/////////////////////////////////////


int XmlIo::WriteFillingPointsInfo(xmlNodePtr root_node,vector<FillingPoints_info> fillingPointGroup)
{
	xmlAddChild(root_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("预定义填涂点组").c_str()) ));
	xmlNodePtr fillingPointGroup_node = xmlNewNode(NULL,BAD_CAST"fillingPointGroup");
	xmlAddChild(root_node,fillingPointGroup_node);
	for (unsigned int i=0;i<fillingPointGroup.size();i++)
	{
		xmlNodePtr perFillingPointGroup_node = xmlNewNode(NULL,BAD_CAST"perFillingPointInfo");
		xmlAddChild(fillingPointGroup_node,perFillingPointGroup_node);
		xmlAddChild(perFillingPointGroup_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("填涂点名").c_str()) ));
		xmlNewTextChild(perFillingPointGroup_node,NULL, BAD_CAST "name", BAD_CAST CChineseCode::GBKToUTF8(fillingPointGroup[i].name).c_str());

		xmlAddChild(perFillingPointGroup_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("填涂点类型").c_str()) ));
		xmlNewTextChild(perFillingPointGroup_node,NULL, BAD_CAST "type", BAD_CAST (dtc.Ushort2String(fillingPointGroup[i].type).c_str()));

		for (unsigned int j=0;j<fillingPointGroup[i].fillingPoints.size();j++)
		{
			WriteItemPosInfo(perFillingPointGroup_node,fillingPointGroup[i].fillingPoints[j]);
		}
	}
	return 0;
}
//预定义填涂点组
int XmlIo::WriteFillingPointsInfo3(xmlNodePtr root_node,vector<FillingPoints_info3> fillingPointGroup)
{
	xmlAddChild(root_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("预定义填涂点组").c_str()) ));
	xmlNodePtr fillingPointGroup_node = xmlNewNode(NULL,BAD_CAST"fillingPointGroup");
	xmlAddChild(root_node,fillingPointGroup_node);
	for (unsigned int i=0;i<fillingPointGroup.size();i++)
	{
		xmlNodePtr perFillingPointGroup_node = xmlNewNode(NULL,BAD_CAST"perFillingPointInfo");
		xmlAddChild(fillingPointGroup_node,perFillingPointGroup_node);
		xmlAddChild(perFillingPointGroup_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("填涂点名").c_str()) ));
		xmlNewTextChild(perFillingPointGroup_node,NULL, BAD_CAST "name", BAD_CAST CChineseCode::GBKToUTF8(fillingPointGroup[i].name).c_str());

		xmlAddChild(perFillingPointGroup_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("填涂点类型").c_str()) ));
		xmlNewTextChild(perFillingPointGroup_node,NULL, BAD_CAST "type", BAD_CAST (dtc.Ushort2String(fillingPointGroup[i].type).c_str()));

		xmlAddChild(perFillingPointGroup_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("是否是横向的").c_str()) ));
		xmlNewTextChild(perFillingPointGroup_node,NULL, BAD_CAST "isCrosswise", BAD_CAST (dtc.Ushort2String(fillingPointGroup[i].isCrosswise).c_str()));

		xmlAddChild(perFillingPointGroup_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("背景信息").c_str()) ));
		xmlNewTextChild(perFillingPointGroup_node,NULL, BAD_CAST "bgInfo", BAD_CAST (dtc.Mat32s2String(fillingPointGroup[i].bgInfo).c_str()));

		for (unsigned int j=0;j<fillingPointGroup[i].fillingPoints.size();j++)
		{
			WriteFillingpointItemPos(perFillingPointGroup_node,fillingPointGroup[i].fillingPoints[j]);
		}
	}
	return 0;
}
///////////////////////////////////////选项信息结构体/////////////////////////////////////

int XmlIo::WriteItemPosInfo(xmlNodePtr partent_node,ItemPos itemPos)
{
	xmlNodePtr itemPos_node = xmlNewNode(NULL,BAD_CAST"itemPos");
	xmlAddChild(partent_node,itemPos_node);
	xmlAddChild(itemPos_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("序号").c_str()) ));
	xmlNewTextChild(itemPos_node,NULL, BAD_CAST "id", BAD_CAST (dtc.Int2String(itemPos.id).c_str()));
	xmlAddChild(itemPos_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("是否横向").c_str()) ));
	xmlNewTextChild(itemPos_node,NULL, BAD_CAST "isCrosswise", BAD_CAST (dtc.Bool2String(itemPos.isCrosswise).c_str()));
	xmlAddChild(itemPos_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("是否单选").c_str()) ));
	xmlNewTextChild(itemPos_node,NULL, BAD_CAST "isSingleChoice", BAD_CAST (dtc.Bool2String(itemPos.isSingleChoice).c_str()));
	xmlAddChild(itemPos_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("横向/纵向间隔，若选项排布为横向则为横向间隔").c_str()) ));
	xmlNewTextChild(itemPos_node,NULL, BAD_CAST "interval", BAD_CAST (dtc.Ushort2String(itemPos.interval).c_str()));
	xmlAddChild(itemPos_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("题目对应定位点索引，若为横向则[0]为水平方向索引号，[1]为垂直方向对应的第一个索引号，[2]为垂直方向对应的最后一个索引号").c_str()) ));
	string tmpStr = dtc.Ushort2String(itemPos.markerIdx[0]);
	tmpStr += ' '+dtc.Ushort2String(itemPos.markerIdx[1]);
	tmpStr += ' '+dtc.Ushort2String(itemPos.markerIdx[2]);
	xmlNewTextChild(itemPos_node,NULL, BAD_CAST "markerIdx", BAD_CAST (tmpStr.c_str()));
	return 0;

}
/////////////////////////////////////每位填涂点信息/////////////////////////////////////
int XmlIo::WriteFillingpointItemPos(xmlNodePtr partent_node,FillingpointItemPos itemPos)
{
	xmlNodePtr itemPos_node = xmlNewNode(NULL,BAD_CAST"fillingpointItemPos");
	xmlAddChild(partent_node,itemPos_node);
	xmlAddChild(itemPos_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("序号").c_str()) ));
	xmlNewTextChild(itemPos_node,NULL, BAD_CAST "id", BAD_CAST (dtc.Int2String(itemPos.id).c_str()));
	xmlAddChild(itemPos_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("是否单选").c_str()) ));
	xmlNewTextChild(itemPos_node,NULL, BAD_CAST "isSingleChoice", BAD_CAST (dtc.Bool2String(itemPos.isSingleChoice).c_str()));
	xmlAddChild(itemPos_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("位置").c_str()) ));
	xmlNodePtr pos_node = xmlNewNode(NULL,BAD_CAST"pos");
	xmlAddChild(itemPos_node,pos_node);
	for (int i=0;i<itemPos.pos.size();i++)
	{
		xmlNewTextChild(pos_node,NULL, BAD_CAST "perFillingPointPos", BAD_CAST (dtc.Rect2String(itemPos.pos[i]).c_str()));
	}
	return 0;
}
////////////////////////////////////填涂点背景信息//////////////////////////////////////
int XmlIo::WriteFillingPointBackgroundInfo(xmlNodePtr root_node,vector<PerFillingPtBackground_info> fillingPointBackgroundInfo)
{
	xmlNodePtr fillingPointBackgroundInfo_node = xmlNewNode(NULL,BAD_CAST"fillingPointBackgroundInfo");
	xmlAddChild(root_node,fillingPointBackgroundInfo_node);
	string matStr;
	for (unsigned int i=0;i<fillingPointBackgroundInfo.size();i++)
	{
		xmlNodePtr perFillingPointBackgroundInfo_node = xmlNewNode(NULL,BAD_CAST"perFillingPointBkInfo");
		xmlAddChild(fillingPointBackgroundInfo_node,perFillingPointBackgroundInfo_node);

		xmlAddChild(perFillingPointBackgroundInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("类型").c_str()) ));
		xmlNewTextChild(perFillingPointBackgroundInfo_node,NULL, BAD_CAST "type", BAD_CAST (dtc.Ushort2String(fillingPointBackgroundInfo[i].type).c_str()));

		xmlAddChild(perFillingPointBackgroundInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("背景信息").c_str()) ));
		if ((matStr = dtc.Mat32s2String(fillingPointBackgroundInfo[i].bkInfo))=="error")
		{
			return -1;
		}
		xmlNewTextChild(perFillingPointBackgroundInfo_node,NULL, BAD_CAST "bkInfo", BAD_CAST (matStr.c_str()));
	}
	return 0;
}

/////////////////////////////////////题目信息///////////////////////////////////////
int XmlIo::WriteQuestionInfo(xmlNodePtr root_node,vector<ItemPos> questionInfo)
{
	xmlNodePtr questionInfo_node = xmlNewNode(NULL,BAD_CAST"questionInfo");
	xmlAddChild(root_node,questionInfo_node);
	for (unsigned int i=0;i<questionInfo.size();i++)
	{
		WriteItemPosInfo(questionInfo_node,questionInfo[i]);
	}
	return 0;
}

/////////////////////////////////////题目背景信息///////////////////////////////////////

int XmlIo::WriteQuestionBackgroundInfo(xmlNodePtr root_node,vector<PerQuestionBackground_info> questionBackgroundInfo)
{
	xmlAddChild(root_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("题目背景信息").c_str()) ));
	xmlNodePtr questionBackgroundInfo_node = xmlNewNode(NULL,BAD_CAST"questionBackgroundInfo");
	xmlAddChild(root_node,questionBackgroundInfo_node);
	string matStr;
	for (unsigned int i=0;i<questionBackgroundInfo.size();i++)
	{
		xmlNodePtr perQuestionBackgroundInfo_node = xmlNewNode(NULL,BAD_CAST"perQuestionBackgroundInfo");
		xmlAddChild(questionBackgroundInfo_node,perQuestionBackgroundInfo_node);

		xmlAddChild(perQuestionBackgroundInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("类型").c_str()) ));
		xmlNewTextChild(perQuestionBackgroundInfo_node,NULL, BAD_CAST "type", BAD_CAST (dtc.Ushort2String(questionBackgroundInfo[i].type).c_str()));

		xmlAddChild(perQuestionBackgroundInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("背景信息").c_str()) ));
		if ((matStr = dtc.Mat32s2String(questionBackgroundInfo[i].bkInfo))=="error")
		{
			return -1;
		}
		xmlNewTextChild(perQuestionBackgroundInfo_node,NULL, BAD_CAST "bkInfo", BAD_CAST (matStr.c_str()));
	}
	return 0;
}
////////////////////////////////////裁切区域//////////////////////////////////////

int XmlIo::WriteCropAreaInfo(xmlNodePtr root_node,vector<CropArea_info> cropAreaInfo)
{
	xmlAddChild(root_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("裁切区域信息").c_str()) ));
	xmlNodePtr cropAreaInfo_node = xmlNewNode(NULL,BAD_CAST"cropAreaInfo");
	xmlAddChild(root_node,cropAreaInfo_node);

	for (unsigned int i=0;i<cropAreaInfo.size();i++)
	{
		xmlNodePtr perCropAreaInfo_node = xmlNewNode(NULL,BAD_CAST"perCropAreaInfo");
		xmlAddChild(cropAreaInfo_node,perCropAreaInfo_node);

		xmlAddChild(perCropAreaInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("裁切区域名字").c_str()) ));
		xmlNewTextChild(perCropAreaInfo_node,NULL, BAD_CAST "name", BAD_CAST (CChineseCode::GBKToUTF8(cropAreaInfo[i].name).c_str()));

		xmlAddChild(perCropAreaInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("裁切区域位置").c_str()) ));
		xmlNewTextChild(perCropAreaInfo_node,NULL, BAD_CAST "pos", BAD_CAST (dtc.Rect2String(cropAreaInfo[i].pos).c_str()));

		xmlAddChild(perCropAreaInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("合并组号").c_str()) ));
		xmlNewTextChild(perCropAreaInfo_node,NULL, BAD_CAST "groupNum", BAD_CAST (dtc.Int2String(cropAreaInfo[i].groupNum).c_str()));

		xmlAddChild(perCropAreaInfo_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("保密属性").c_str()) ));
		xmlNewTextChild(perCropAreaInfo_node,NULL, BAD_CAST "isSecret", BAD_CAST (dtc.Bool2String(cropAreaInfo[i].isSecret).c_str()));

	}
	return 0;
}
///////////////////////////////黑白检测线/////////////////////////////////////////////

int XmlIo::WriteBlackWhiteLine(xmlNodePtr root_node,Rect blackLine,Rect whiteLine)
{
	xmlAddChild(root_node,xmlNewComment( BAD_CAST (CChineseCode::GBKToUTF8("黑白检测线").c_str()) ));
	xmlNewTextChild(root_node,NULL, BAD_CAST "blackLine", BAD_CAST (dtc.Rect2String(blackLine).c_str()));
	xmlNewTextChild(root_node,NULL, BAD_CAST "whiteLine", BAD_CAST (dtc.Rect2String(whiteLine).c_str()));
	return 0;
}
//////////////////////////////////////////////////////////////////////////
/////////////////////////////////读模块/////////////////////////////////////////
int XmlIo::Read(string filename,AC_info &acInfo)
{
	xmlDocPtr doc;
	xmlNodePtr root_node;
	// load an exist xml file.
	doc = xmlReadFile(filename.c_str(),"UTF-8",XML_PARSE_NOBLANKS); 
	if (doc == NULL ) 
	{ 
		return -1; 
	} 
	// get root
	root_node = xmlDocGetRootElement(doc);

	if (root_node == NULL) 
	{ 
		xmlFreeDoc(doc);
		return 1;
	}
	
	xmlNodePtr cur_node;      //定义结点指针
	cur_node = root_node->xmlChildrenNode; //子节点集是链表
	int nRel;
	string content;
	//开始读取内容

	//试卷类型
	if ((nRel = GetNextElement("ac_id",cur_node))!=0)
	{
		return nRel;
	}
	acInfo.ac_id = string((char * )cur_node->children->content);
	cur_node = cur_node->next;

	//分辨率
	if ((nRel = GetNextElement("dpi",cur_node))!=0)	
	{
		return nRel;
	}
	content = string((char * )cur_node->children->content);
	acInfo.dpi = dtc.String2Int(content);
	cur_node = cur_node->next;

	//定位点信息
	if ((nRel = GetNextElement("anchorPointInfo",cur_node))!=0)	
	{
		return nRel;
	}
	ReadAnchorPointInfo(cur_node,acInfo.anchorPointInfo);
	cur_node = cur_node->next;

	//标记点信息
	if ((nRel = GetNextElement("markerInfo",cur_node))!=0)	//获取试卷类型元素
	{
		return nRel;
	}
	ReadMarkerInfo(cur_node,acInfo.markerInfo);
	cur_node = cur_node->next;

	//条码信息
	if ((nRel = GetNextElement("barInfo",cur_node))!=0)	//获取试卷类型元素
	{
		return nRel;
	}
	ReadBarInfo(cur_node,acInfo.barGroup);
	cur_node = cur_node->next;
	//预定义填涂点组
	if ((nRel = GetNextElement("fillingPointGroup",cur_node))!=0)	//获取试卷类型元素
	{
		return nRel;
	}
	ReadFillingPointsInfo(cur_node,acInfo.fillingPointGroup);
	cur_node = cur_node->next;
	//填涂点背景信息
	if ((nRel = GetNextElement("fillingPointBackgroundInfo",cur_node))!=0)	//获取试卷类型元素
	{
		return nRel;
	}
	ReadFillingPointBackgroundInfo(cur_node,acInfo.fillingPointBackgroundInfo);
	cur_node = cur_node->next;
	//题目信息
	if ((nRel = GetNextElement("questionInfo",cur_node))!=0)	//获取试卷类型元素
	{
		return nRel;
	}
	ReadQuestionInfo(cur_node,acInfo.questioninfo);
	cur_node = cur_node->next;
	//题目背景信息
	if ((nRel = GetNextElement("questionBackgroundInfo",cur_node))!=0)	//获取试卷类型元素
	{
		return nRel;
	}
	ReadQuestionBackgroundInfo(cur_node,acInfo.questionBackgroundInfo);
	cur_node = cur_node->next;
	//裁切区域
	if ((nRel = GetNextElement("cropAreaInfo",cur_node))!=0)	//获取试卷类型元素
	{
		return nRel;
	}
	ReadCropAreaInfo(cur_node,acInfo.cropAreaInfo);

	return 0;
}
int XmlIo::Read(string filename,AC_info3 &acInfo){

	xmlDocPtr doc;
	xmlNodePtr root_node;
	// load an exist xml file.
	doc = xmlReadFile(filename.c_str(),"UTF-8",XML_PARSE_NOBLANKS); 
	if (doc == NULL ) 
	{ 
		return -1; 
	} 
	// get root
	root_node = xmlDocGetRootElement(doc);

	if (root_node == NULL) 
	{ 
		xmlFreeDoc(doc);
		return 1;
	}

	xmlNodePtr cur_node;      //定义结点指针
	cur_node = root_node->xmlChildrenNode; //子节点集是链表
	int nRel;
	string content;
	//开始读取内容

	//试卷类型
	if ((nRel = GetNextElement("ac_id",cur_node))!=0)
	{
		return nRel;
	}
	acInfo.ac_id = string((char * )cur_node->children->content);
	cur_node = cur_node->next;

	//分辨率
	if ((nRel = GetNextElement("dpi",cur_node))!=0)	
	{
		return nRel;
	}
	content = string((char * )cur_node->children->content);
	acInfo.dpi = dtc.String2Int(content);
	cur_node = cur_node->next;

	//定位点信息
	if ((nRel = GetNextElement("anchorPointInfo",cur_node))!=0)	
	{
		return nRel;
	}
	ReadAnchorPointInfo(cur_node,acInfo.anchorPointInfo);
	cur_node = cur_node->next;

	//标记点信息
	if ((nRel = GetNextElement("xMarkerInfo",cur_node))!=0)	
	{
		return nRel;
	}
	ReadMarkerInfo(cur_node,acInfo.markerInfo);
	cur_node = cur_node->next;	//跳过ymarker标签
	cur_node = cur_node->next;

	//条码信息
	if ((nRel = GetNextElement("barInfo",cur_node))!=0)
	{
		return nRel;
	}
	ReadBarInfo(cur_node,acInfo.barGroup);
	cur_node = cur_node->next;
	//预定义填涂点组
	if ((nRel = GetNextElement("fillingPointGroup",cur_node))!=0)
	{
		return nRel;
	}
	ReadFillingPointsInfo(cur_node,acInfo.fillingPointGroup);
	cur_node = cur_node->next;

	//题目信息
	if ((nRel = GetNextElement("questionInfo",cur_node))!=0)
	{
		return nRel;
	}
	ReadQuestionInfo(cur_node,acInfo.questioninfo);
	cur_node = cur_node->next;
	//题目背景信息
	if ((nRel = GetNextElement("questionBackgroundInfo",cur_node))!=0)
	{
		return nRel;
	}
	ReadQuestionBackgroundInfo(cur_node,acInfo.questionBackgroundInfo);
	cur_node = cur_node->next;
	//裁切区域
	if ((nRel = GetNextElement("cropAreaInfo",cur_node))!=0)
	{
		return nRel;
	}
	ReadCropAreaInfo(cur_node,acInfo.cropAreaInfo);
	cur_node = cur_node->next;
	//黑白线
	if ((nRel = GetNextElement("blackLine",cur_node))!=0)
	{
		return nRel;
	}
	content = string((char * )cur_node->children->content);
	acInfo.blackLine = dtc.String2Rect(content);
	cur_node = cur_node->next;
	if ((nRel = GetNextElement("whiteLine",cur_node))!=0)
	{
		return nRel;
	}
	content = string((char * )cur_node->children->content);
	acInfo.whiteLine = dtc.String2Rect(content);

	return 0;
}
//定位点模块
int XmlIo::ReadAnchorPointInfo(xmlNodePtr root_node,AnchorPoint_info &anchorPointInfo)
{
	xmlNodePtr cur_node = root_node->children;
	int nRel;
	string content;
	//获取定位点数量
	if ((nRel = GetNextElement("num",cur_node))!=0)	
		return nRel;
	content = string((char * )cur_node->children->content);
	anchorPointInfo.num = dtc.String2Int(content);
	cur_node = cur_node->next;
	//获取定位点类型
	if ((nRel = GetNextElement("anchorType",cur_node))!=0)	
		return nRel;
	content = string((char * )cur_node->children->content);
	anchorPointInfo.anchorType = dtc.String2Short(content);
	cur_node = cur_node->next;
	//获取定位点位置
	if ((nRel = GetNextElement("anchorPtPosInfo",cur_node))!=0)	
		return nRel;
	xmlNodePtr anchorPtPosInfo_node = cur_node;
	xmlNodePtr tmp = cur_node->children;
	while(tmp)
	{
		content = string((char * )tmp->children->content);
		anchorPointInfo.anchorPt.push_back(dtc.String2Rect(content));
		tmp = tmp->next;
	}
	return 0;
}
// 标记点模块
int XmlIo::ReadMarkerInfo(xmlNodePtr root_node, Marker_info &markerInfo)
{

	xmlNodePtr cur_node = root_node->children;
	int nRel;
	string content;
	//横向标记点数量
	if ((nRel = GetNextElement("xNum",cur_node))!=0)	
		return nRel;
	content = string((char * )cur_node->children->content);
	markerInfo.xNum = dtc.String2Int(content);
	cur_node = cur_node->next;

	//纵向标记点数量
	if ((nRel = GetNextElement("yNum",cur_node))!=0)	
		return nRel;
	content = string((char * )cur_node->children->content);
	markerInfo.yNum = dtc.String2Int(content);
	cur_node = cur_node->next;

	//横向标记点尺寸
	if ((nRel = GetNextElement("xSize",cur_node))!=0)	
		return nRel;
	content = string((char * )cur_node->children->content);
	markerInfo.xSize = dtc.String2Size(content);
	cur_node = cur_node->next;

	//纵向标记点尺寸
	if ((nRel = GetNextElement("ySize",cur_node))!=0)	
		return nRel;
	content = string((char * )cur_node->children->content);
	markerInfo.ySize = dtc.String2Size(content);
	cur_node = cur_node->next;

	//横向标记点组所在区域
	if ((nRel = GetNextElement("xMarker",cur_node))!=0)	
		return nRel;
	content = string((char * )cur_node->children->content);
	markerInfo.xMarker = dtc.String2Rect(content);
	cur_node = cur_node->next;

	//纵向标记点组所在区域
	if ((nRel = GetNextElement("yMarker",cur_node))!=0)	
		return nRel;
	content = string((char * )cur_node->children->content);
	markerInfo.yMarker = dtc.String2Rect(content);
	return 0;
}
int XmlIo::ReadMarkerInfo(xmlNodePtr root_node, Marker_info3 &markerInfo)
{

	xmlNodePtr cur_node = root_node->children;
	int nRel;
	string content;
	while(cur_node)
	{
		content = string((char * )cur_node->children->content);
		markerInfo.xMarker.push_back(dtc.String2Rect(content));
		cur_node = cur_node->next;
	}
	cur_node = root_node->next->children;
	while(cur_node)
	{
		content = string((char * )cur_node->children->content);
		markerInfo.yMarker.push_back(dtc.String2Rect(content));
		cur_node = cur_node->next;
	}
	return 0;
}
//条码信息
int XmlIo::ReadBarInfo(xmlNodePtr root_node,vector<Bar_info> &barGroup)
{
	xmlNodePtr perBar_node = root_node->children;
	xmlNodePtr cur_node;
	int nRel,i=0;
	string content;
	//每个条码信息
	while (perBar_node)
	{
		Bar_info barInfo;
		cur_node = perBar_node->children;
		//条码类型
		if ((nRel = GetNextElement("barType",cur_node))!=0)	
			return nRel;
		content = string((char * )cur_node->children->content);
		barInfo.barType = (BarType)dtc.String2Ushort(content);
		cur_node = cur_node->next;
		//条码位置
		if ((nRel = GetNextElement("pos",cur_node))!=0)	
			return nRel;
		content = string((char * )cur_node->children->content);
		barInfo.pos = dtc.String2Rect(content);
		barGroup.push_back(barInfo);

		perBar_node = perBar_node->next;
	}		
	return 0;
}
//预定义填涂点组
int XmlIo::ReadFillingPointsInfo(xmlNodePtr root_node,vector<FillingPoints_info> &fillingPointGroup)
{
	xmlNodePtr perFillingPoint_node = root_node->children;
	xmlNodePtr cur_node;
	int nRel;
	string content;
	//每个填涂点信息
	while (perFillingPoint_node)
	{
		FillingPoints_info fillingPointsInfo;
		cur_node = perFillingPoint_node->children;
		//填涂点名字
		if ((nRel = GetNextElement("name",cur_node))!=0)	
			return nRel;
		content = string((char * )cur_node->children->content);
		fillingPointsInfo.name = CChineseCode::UTF8ToGBK(content);
		cur_node = cur_node->next;
		//填涂点类型
		if ((nRel = GetNextElement("type",cur_node))!=0)	
			return nRel;
		content = string((char * )cur_node->children->content);
		fillingPointsInfo.type = (FillingPointsType)dtc.String2Ushort(content);
		cur_node = cur_node->next;
		while(cur_node)
		{
			//填涂点位置
			if ((nRel = GetNextElement("itemPos",cur_node))!=0)	
				return nRel;
			ItemPos itemPos;
			ReadItemPos(cur_node,itemPos);
			fillingPointsInfo.fillingPoints.push_back(itemPos);
			cur_node = cur_node->next;
		}
		fillingPointGroup.push_back(fillingPointsInfo);
		perFillingPoint_node = perFillingPoint_node->next;

	}		
	return 0;

}
int XmlIo::ReadFillingPointsInfo(xmlNodePtr root_node,vector<FillingPoints_info3> &fillingPointGroup)
{
	xmlNodePtr perFillingPoint_node = root_node->children;
	xmlNodePtr cur_node;
	int nRel;
	string content;
	//每个填涂点信息
	while (perFillingPoint_node)
	{
		FillingPoints_info3 fillingPointsInfo;
		cur_node = perFillingPoint_node->children;
		//填涂点名字
		if ((nRel = GetNextElement("name",cur_node))!=0)	
			return nRel;
		content = string((char * )cur_node->children->content);
		fillingPointsInfo.name = CChineseCode::UTF8ToGBK(content);
		cur_node = cur_node->next;
		//填涂点类型
		if ((nRel = GetNextElement("type",cur_node))!=0)	
			return nRel;
		content = string((char * )cur_node->children->content);
		fillingPointsInfo.type = (FillingPointsType)dtc.String2Ushort(content);
		cur_node = cur_node->next;

		//是否是横向的
		if ((nRel = GetNextElement("isCrosswise",cur_node))!=0)	
			return nRel;
		content = string((char * )cur_node->children->content);
		fillingPointsInfo.isCrosswise = dtc.String2Bool(content);
		cur_node = cur_node->next;

		//填涂点背景
		if ((nRel = GetNextElement("bgInfo",cur_node))!=0)	
			return nRel;
		content = string((char * )cur_node->children->content);
		fillingPointsInfo.bgInfo = dtc.String2Mat32s(content);
		cur_node = cur_node->next;

		while(cur_node)
		{
			//填涂点位置
			if ((nRel = GetNextElement("fillingpointItemPos",cur_node))!=0)	
				return nRel;
			FillingpointItemPos itemPos;
			ReadFillingpointItemPos(cur_node,itemPos);
			fillingPointsInfo.fillingPoints.push_back(itemPos);
			cur_node = cur_node->next;
		}
		fillingPointGroup.push_back(fillingPointsInfo);
		perFillingPoint_node = perFillingPoint_node->next;

	}		
	return 0;

}
// 读取选项位置信息
int XmlIo::ReadItemPos(xmlNodePtr firstItemPosPtr,ItemPos &itemPos)
{
	xmlNodePtr cur_node = firstItemPosPtr->children;
	int nRel;
	string content;
	//序号
	if ((nRel = GetNextElement("id",cur_node))!=0)	
		return nRel;
	content = string((char * )cur_node->children->content);
	itemPos.id = dtc.String2Int(content);
	cur_node = cur_node->next;

	//是否是横向的
	if ((nRel = GetNextElement("isCrosswise",cur_node))!=0)	
		return nRel;
	content = string((char * )cur_node->children->content);
	itemPos.isCrosswise = dtc.String2Bool(content);
	cur_node = cur_node->next;

	//是否是单选
	if ((nRel = GetNextElement("isSingleChoice",cur_node))!=0)	
		return nRel;
	content = string((char * )cur_node->children->content);
	itemPos.isSingleChoice = dtc.String2Bool(content);
	cur_node = cur_node->next;

	//横向/纵向间隔
	if ((nRel = GetNextElement("interval",cur_node))!=0)	
		return nRel;
	content = string((char * )cur_node->children->content);
	itemPos.interval = dtc.String2Ushort(content);
	cur_node = cur_node->next;

	//题目对应定位点索引
	while(cur_node){
		if ((nRel = GetNextElement("markerIdx",cur_node))!=0)	
			return nRel;
		content = string((char * )cur_node->children->content);
		string subString;
		int l = 0,r = 0;
		for (int i=0;i<3;i++)
		{
			r = content.find(' ',r+1);
			subString = content.substr(l,r);
			l = r+1;
			itemPos.markerIdx[i] = dtc.String2Ushort(subString);
		}
		cur_node = cur_node->next;
	}
	return 0;
}
//读取每位填涂点信息
int XmlIo::ReadFillingpointItemPos(xmlNodePtr firstItemPosPtr,FillingpointItemPos &itemPos)
{
	xmlNodePtr cur_node = firstItemPosPtr->children;
	int nRel;
	string content;
	//序号
	if ((nRel = GetNextElement("id",cur_node))!=0)	
		return nRel;
	content = string((char * )cur_node->children->content);
	itemPos.id = dtc.String2Int(content);
	cur_node = cur_node->next;


	//是否是单选
	if ((nRel = GetNextElement("isSingleChoice",cur_node))!=0)	
		return nRel;
	content = string((char * )cur_node->children->content);
	itemPos.isSingleChoice = dtc.String2Bool(content);
	cur_node = cur_node->next;

	//题目对应定位点索引
	if ((nRel = GetNextElement("pos",cur_node))!=0)	
		return nRel;
	cur_node = cur_node->children;
	while(cur_node){
		content = string((char * )cur_node->children->content);
		itemPos.pos.push_back(dtc.String2Rect(content));
		cur_node = cur_node->next;
	}
	return 0;
}
//填涂点背景信息
int XmlIo::ReadFillingPointBackgroundInfo(xmlNodePtr root_node,vector<PerFillingPtBackground_info> &fillingPointBackgroundInfo)
{
	xmlNodePtr perFillingPtBackgroundInfo_node = root_node->children;
	xmlNodePtr cur_node;
	int nRel;
	string content;
	//每个填涂背景信息
	while(perFillingPtBackgroundInfo_node)
	{
		cur_node = perFillingPtBackgroundInfo_node->children;
		PerFillingPtBackground_info perFillingPtBackgroundInfo;
		//填涂点类型
		if ((nRel = GetNextElement("type",cur_node))!=0)	
			return nRel;
		content = string((char * )cur_node->children->content);
		perFillingPtBackgroundInfo.type = (FillingPointsType)dtc.String2Ushort(content);
		cur_node = cur_node->next;

		//填涂点背景
		if ((nRel = GetNextElement("bkInfo",cur_node))!=0)	
			return nRel;
		content = string((char * )cur_node->children->content);
		perFillingPtBackgroundInfo.bkInfo = dtc.String2Mat32s(content);
		fillingPointBackgroundInfo.push_back(perFillingPtBackgroundInfo);
		perFillingPtBackgroundInfo_node = perFillingPtBackgroundInfo_node->next;
	}

	return 0;
}
//题目信息
int XmlIo::ReadQuestionInfo(xmlNodePtr root_node,vector<ItemPos> &questionInfo)
{
	xmlNodePtr perQuestionInfo_node = root_node->children;
	int nRel;
	ItemPos itemPos;
	//每个填涂背景信息
	while(perQuestionInfo_node)
	{
		//获取定位点数量
		if ((nRel = GetNextElement("itemPos",perQuestionInfo_node))!=0)	
			return nRel;
		ReadItemPos(perQuestionInfo_node,itemPos);
		questionInfo.push_back(itemPos);
		perQuestionInfo_node = perQuestionInfo_node->next;
	}
	return 0;
}
//题目背景信息
int XmlIo::ReadQuestionBackgroundInfo(xmlNodePtr root_node,vector<PerQuestionBackground_info> &questionBackgroundInfo)
{
	xmlNodePtr perQuestionBackgroundInfo_node = root_node->children;
	xmlNodePtr cur_node;
	int nRel;
	string content;
	//每个填涂背景信息
	while(perQuestionBackgroundInfo_node)
	{
		cur_node = perQuestionBackgroundInfo_node->children;
		PerQuestionBackground_info perQuestionBackgroundInfo;
		//填涂点类型
		if ((nRel = GetNextElement("type",cur_node))!=0)	
			return nRel;
		content = string((char * )cur_node->children->content);
		perQuestionBackgroundInfo.type = (FillingPointsType)dtc.String2Ushort(content);
		cur_node = cur_node->next;

		//填涂点背景
		if ((nRel = GetNextElement("bkInfo",cur_node))!=0)	
			return nRel;
		content = string((char * )cur_node->children->content);
		perQuestionBackgroundInfo.bkInfo = dtc.String2Mat32s(content);
		questionBackgroundInfo.push_back(perQuestionBackgroundInfo);
		perQuestionBackgroundInfo_node = perQuestionBackgroundInfo_node->next;
	}

	return 0;
}
//答题区域
int XmlIo::ReadCropAreaInfo(xmlNodePtr root_node,vector<CropArea_info> &cropAreaInfo)
{
	xmlNodePtr perCropAreaInfo_node = root_node->children;
	xmlNodePtr cur_node;
	int nRel;
	string content;
	//每个裁切区域信息
	while(perCropAreaInfo_node)
	{
		cur_node = perCropAreaInfo_node->children;
		CropArea_info perCropAreaInfo;
		//裁切区域名
		if ((nRel = GetNextElement("name",cur_node))!=0)	
			return nRel;
		content = string((char * )cur_node->children->content);
		perCropAreaInfo.name = CChineseCode::UTF8ToGBK(content);
		cur_node = cur_node->next;

		//裁切区域位置
		if ((nRel = GetNextElement("pos",cur_node))!=0)	
			return nRel;
		content = string((char * )cur_node->children->content);
		perCropAreaInfo.pos = dtc.String2Rect(content);
		cur_node = cur_node->next;

		//合并组号
		if ((nRel = GetNextElement("groupNum",cur_node))!=0)	
			return nRel;
		content = string((char * )cur_node->children->content);
		perCropAreaInfo.groupNum = dtc.String2Int(content);
		cur_node = cur_node->next;

		//保密属性
		if ((nRel = GetNextElement("isSecret",cur_node))!=0)	
			return nRel;
		content = string((char * )cur_node->children->content);
		perCropAreaInfo.isSecret = dtc.String2Bool(content);
		cropAreaInfo.push_back(perCropAreaInfo);
		perCropAreaInfo_node = perCropAreaInfo_node->next;
	}
	return 0;
}


// 获得有效元素
int XmlIo::GetNextElement(string elementName, xmlNodePtr &cur_node)
{
	while (cur_node != NULL)
	{
		//跳过注释节点
		if (cur_node->type ==XML_COMMENT_NODE)
			cur_node = cur_node->next;
		else
			break;
	}
	//卡格式文件不完整
	if (NULL == cur_node)
	{
		return -1;
	}
	//卡格式文件不匹配
	if (elementName.compare((char *)cur_node->name)!=0)
	{
		return -2;
	}
	return 0;
}



