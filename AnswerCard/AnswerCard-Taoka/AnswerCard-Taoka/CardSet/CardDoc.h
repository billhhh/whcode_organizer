#pragma once
#ifndef CARDDOCDLG_H
#define CARDDOCDLG_H

#include "qstring.h"
#include "qlist.h"
#include "Zip\ACZip.h"
#include "qimage.h"
#include "../AnswerCard/DataIO.h"
#include <vector>

using std::vector;

#define PAPERSET_MAGIC_NUM 0x0000CD01
#define VERSION 102

//一张试卷的结构
struct PaperPage
{
	QString pageId;
	bool isPositive;
};

//一套试卷的结构
struct PaperSet
{
	QString setId;
	int dpi;
	//QString setName;
	vector<PaperPage> page;
};

struct Course
{
	QString courseName;
	vector<PaperSet> set;
};

class CardDoc
{
public:
	CardDoc(int acType);
	~CardDoc();

	int getAcType() const {return m_acType;}
	vector<PaperSet> getPaperSet(int courseIndex) {return m_course.at(courseIndex).set;}
	vector<Course> getCourse() {return m_course;}

	//添加删除一门科目
	void createCourse(const QString& name);
	void removeCourse(int index);
	//void removeCourse(const QString& name);

	//添加删除一套试卷
	void createPaperSet(int courseIndex, const QString& setId, int dpi);
	int removePaperSet(int courseIndex, int index);
	//void removePaperSet(const QString& setId);

	//添加删除一张试卷
	int insertPaperPage(int courseIndex, int setIndex, const PaperPage& paperPage, const QImage& img);
	//void insertPaperPage(const QString& setId, const PaperPage& paperPage);
	int removePaperPage(int courseIndex, int setIndex, int pageIndex);
	//void removePaperPage(const QString& setId, const QString& pageId);
	
	//获取一套试卷中有多少张试卷
	int getPageCountOfSet(int courseIndex, int setIndex) const;
	int getSetCountOfCourse(int courseIndex) const;

	//判断试卷集的id是否存在，如果存在，则返回下标，否则返回-1
	int isPaperSetIdExist(int courseIndex, const QString& id);
	int isPageIdOfSetExist(int courseIndex, int setIndex, const QString& id);
	int isCourseExist(const QString& name);

	PaperPage getPageDetail(int courseIndex, int setIndex, int pageIndex) const;
	PaperSet getPageSetDetail(int courseIndex, int setIndex) const;

	//打包所有试卷信息
	int zipPaperSetInfo(int courseIndex, const QString &zipPath);

	//从ACPOJ文件中恢复过来
	int resumeDataFromZip(const QString &zipPath);

private:
	//vector<PaperSet> m_paperSet;
	vector<Course> m_course;
	int m_acType;

	//保存试卷集关系信息
	int savePaperSetRelationFile(int courseIndex, QString fileName);

	//清除所有临时文件
	void removeTempFile();
	void removeTempFile(const QString& path);
};

#endif