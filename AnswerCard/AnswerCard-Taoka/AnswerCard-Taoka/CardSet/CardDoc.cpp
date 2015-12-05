#include "CardDoc.h"
#include "qxmlstream.h"
#include "qfileinfo.h"
#include "qfile.h"
#include "qdebug.h"
#include "qdir.h"
#include "qdebug.h"

CardDoc::CardDoc(int type)
{
	QDir dir;
	bool exist = dir.exists("tmp");
	m_acType = type;

	if (!exist)
	{
		//创建tmp文件夹
		dir.mkdir("tmp");
	}

	m_course.resize(0);
	m_course.clear();
}

CardDoc::~CardDoc()
{
	//removeTempFile();

	QDir dir;
	bool exist = dir.exists("tmp");

	if (exist)
	{
		QDir dirTmp("tmp//");
		QFileInfoList list = dirTmp.entryInfoList();

		//遍历删除目录下的文件
		for (int i = 0; i < list.size(); ++i)
		{
			if(list.at(i).fileName() == "." || list.at(i).fileName() == "..")
			{
				continue;
			}

			dirTmp.remove(list.at(i).fileName());
		}

		//删除tmp文件夹
		dir.rmdir("tmp");
	}
}

//创建科目
void CardDoc::createCourse(const QString& name)
{
	Course course;
	course.courseName = name;
	m_course.push_back(course);
}

//移除科目
void CardDoc::removeCourse(int index)
{
	int setAmount = m_course.at(index).set.size();

	//移除科目下所有的试卷
	for (int i = 0; i < setAmount; i++)
	{
		removePaperSet(index, 0);
	}

	m_course.erase(m_course.begin() + index);
}

//创建试卷套
void CardDoc::createPaperSet(int courseIndex, const QString& setId, int dpi)
{
	PaperSet set;
	set.setId = setId;
	set.dpi = dpi;

	m_course.at(courseIndex).set.push_back(set);
}

//移除试卷套
int CardDoc::removePaperSet(int courseIndex, int index)
{
	if (index > -1 && index < m_course.at(courseIndex).set.size())
	{
		vector<PaperPage>::iterator iter = m_course.at(courseIndex).set.at(index).page.begin();

		//移除该套卡下的试卷
		for (; iter != m_course.at(courseIndex).set.at(index).page.end(); ++iter)
		{
			//获取临时文件路径
			QString dataPath = QString(QObject::tr("tmp\\%1-%2-%3-%4.dat")
				.arg(m_course.at(courseIndex).courseName)
				.arg(m_course.at(courseIndex).set.at(index).setId)
				.arg(iter->pageId)
				.arg((int)(iter->isPositive)));

			//删除临时文件
			QFile file(dataPath);

			if (file.exists())
			{
				file.remove();
			}
		}

		m_course.at(courseIndex).set.erase(m_course.at(courseIndex).set.begin() + index);

		return 1;
	}

	return 0;
}

//为某试卷套添加一张试卷
int CardDoc::insertPaperPage(int courseIndex, int setIndex, const PaperPage& paperPage, const QImage& img)
{
	if (setIndex > -1 && setIndex < m_course.at(courseIndex).set.size())
	{
		PaperPage page = paperPage;
		m_course.at(courseIndex).set.at(setIndex).page.push_back(page);

		//获取临时文件路径
		DataIO io(QObject::tr("tmp\\%1-%2-%3-%4.dat")
			.arg(m_course.at(courseIndex).courseName)
			.arg(m_course.at(courseIndex).set.at(setIndex).setId)
			.arg(page.pageId).arg((int)(page.isPositive)), 
			DATA_WRITE);

		//新建临时文件
		DataInfo info;
		info.image = img;
		info.anchorType = 0;
		info.markerDone = false;
		io.writeToDat(info);

		return 1;
	}

	return 0;
}

//移除一张试卷
int CardDoc::removePaperPage(int courseIndex, int setIndex, int pageIndex)
{
	if (setIndex > -1 && setIndex < m_course.at(courseIndex).set.size())
	{
		//int pageIndex = -1;
		//pageIndex = this->isPageIdOfSetExist(courseIndex, setIndex, pageId);

		if (pageIndex > -1 && pageIndex < m_course.at(courseIndex).set.at(setIndex).page.size())
		{
			//获取临时文件路径
			QString dataPath = QString(QObject::tr("tmp//%1-%2-%3-%4.dat")
				.arg(m_course.at(courseIndex).courseName)
				.arg(m_course.at(courseIndex).set.at(setIndex).setId)
				.arg(m_course.at(courseIndex).set.at(setIndex).page.at(pageIndex).pageId)
				.arg((int)(m_course.at(courseIndex).set.at(setIndex).page.at(pageIndex).isPositive)));

			QFile file(dataPath);

			if (file.exists())
			{
				//删除临时文件
				file.remove();
			}

			m_course.at(courseIndex).set.at(setIndex).page.erase(
				m_course.at(courseIndex).set.at(setIndex).page.begin() + pageIndex);
			return 1;
		}
	}

	return 0;
}

//获取某科目下的某试卷套下的试卷数量
int CardDoc::getPageCountOfSet(int courseIndex, int setIndex) const
{
	if (setIndex > -1 && setIndex < m_course.at(courseIndex).set.size())
	{
		return m_course.at(courseIndex).set.at(setIndex).page.size();
	}

	return -1;
}

//获取某科目下的某试卷套数量
int CardDoc::getSetCountOfCourse(int courseIndex) const
{
	if (courseIndex >-1 && courseIndex < m_course.size())
	{
		return m_course.at(courseIndex).set.size();
	}
	else
	{
		return 0;
	}
}

//判断某科目是否存在
int CardDoc::isCourseExist(const QString& name)
{
	vector<Course>::iterator iter = m_course.begin();
	int find = -1;

	if (m_course.size() == 0)
	{
		return find;
	}

	for (int i = 0; iter != m_course.end(); ++iter, ++i)
	{
		if (iter->courseName == name)
		{
			find = i;
			break;
		}
	}

	return find;
}

//判断某试卷套是否存在
int CardDoc::isPaperSetIdExist(int courseIndex, const QString& id)
{
	vector<PaperSet>::iterator iter = m_course.at(courseIndex).set.begin();
	int find = -1;

	for (int i = 0; iter != m_course.at(courseIndex).set.end(); ++iter, ++i)
	{
		if (iter->setId == id)
		{
			find = i;
			break;
		}
	}

	return find;
}

//判断某试卷页面是否存在
int CardDoc::isPageIdOfSetExist(int courseIndex, int setIndex, const QString& id)
{
	int find = -1;

	if (setIndex < 0 || setIndex > m_course.at(courseIndex).set.size())
	{
		return find;
	}

	vector<PaperPage>::iterator iter = m_course.at(courseIndex).set.at(setIndex).page.begin();

	for (int i = 0; iter !=  m_course.at(courseIndex).set.at(setIndex).page.end();++i,
		++iter)
	{
		if (iter->pageId == id)
		{
			find = i;
			break;
		}
	}

	return find;
}

//获取试卷信息
PaperPage CardDoc::getPageDetail(int courseIndex, int setIndex, int pageIndex) const
{
	PaperPage page;

	if (setIndex >= 0 && setIndex < m_course.at(courseIndex).set.size())
	{
		page.pageId = m_course.at(courseIndex).set.at(setIndex).page.at(pageIndex).pageId;
		page.isPositive = m_course.at(courseIndex).set.at(setIndex).page.at(pageIndex).isPositive;
	}

	return page;
}

//获取试卷套信息
PaperSet CardDoc::getPageSetDetail(int courseIndex, int setIndex) const
{
	PaperSet set;

	if (setIndex >= 0 && setIndex < m_course.at(courseIndex).set.size())
	{
		set = m_course.at(courseIndex).set.at(setIndex);
	}

	return set;
}

//打包整个科目的试卷信息
int CardDoc::zipPaperSetInfo(int courseIndex, const QString &zipPath)
{
	if (m_course.at(courseIndex).set.size() <= 0)
	{
		return -1;
	}

	//存放要打包的文件的路径
	vector<string> files;
	vector<PaperSet>::iterator setIter = m_course.at(courseIndex).set.begin();

	for (; setIter != m_course.at(courseIndex).set.end(); ++setIter)
	{
		vector<PaperPage>::iterator pageIter = setIter->page.begin();

		for (; pageIter != setIter->page.end(); ++pageIter)
		{
			//获取文件路径
			QString dataPath = QString(QObject::tr("tmp\\%1-%2-%3-%4.dat")
				.arg(m_course.at(courseIndex).courseName)
				.arg(setIter->setId)
				.arg(pageIter->pageId)
				.arg((int)(pageIter->isPositive)));

			files.push_back(dataPath.toStdString());
		}
	}

	//生成试卷关系文件
	QString str("tmp\\paperSet.dat");
	savePaperSetRelationFile(courseIndex, str);
	files.push_back(str.toStdString());

	ACZip(files, zipPath.toStdString());

	//删除试卷关系文件
	QFile::remove(str);

	return 1;
}

//保存各试卷关系信息
int CardDoc::savePaperSetRelationFile(int courseIndex, QString fileName)
{
	QList<QString> setId;
	QList<int> dpi;
	QList<int> pageCount;
	QList<QString> pageId;
	QList<bool> isPositive;

	vector<PaperSet>::iterator iter = m_course.at(courseIndex).set.begin();

	for (; iter != m_course.at(courseIndex).set.end(); ++iter)
	{
		setId.push_back(iter->setId);
		dpi.push_back(iter->dpi);
		pageCount.push_back(iter->page.size());

		vector<PaperPage>::iterator iter2 = iter->page.begin();

		for (; iter2 != iter->page.end(); ++iter2)
		{
			pageId.push_back(iter2->pageId);
			isPositive.push_back(iter2->isPositive);
		}
	}

	QFile file(fileName);

	if (!file.open(QIODevice::WriteOnly))
	{
		return 0;
	}

	QDataStream data;
	data.setDevice(&file);
	data.setVersion(QDataStream::Qt_4_8);

	//输出试卷关系信息
	data << quint32(PAPERSET_MAGIC_NUM) << quint32(VERSION) 
		 << m_acType << m_course.at(courseIndex).courseName
		 << m_course.at(courseIndex).set.size() << setId << dpi
		 << pageCount << pageId << isPositive;

	if (file.isOpen())
	{
		file.close();
	}
	return 1;
}

//清除程序临时文件
void CardDoc::removeTempFile()
{
	QDir dir;
	bool exist = dir.exists("tmp");

	if (exist)
	{
		QDir dirTmp("tmp//");
		QFileInfoList list = dirTmp.entryInfoList();

		//遍历删除目录下的文件
		for (int i = 0; i < list.size(); ++i)
		{
			if(list.at(i).fileName() == "." || list.at(i).fileName() == "..")
			{
				continue;
			}

			dirTmp.remove(list.at(i).fileName());
		}

		//删除tmp文件夹
		/*dir.rmdir("tmp");*/
	}
}

//清除程序临时文件
void CardDoc::removeTempFile(const QString& path)
{
	QDir dir;
	bool exist = dir.exists(path);

	if (exist)
	{
		QDir dirTmp(path);
		QFileInfoList list = dirTmp.entryInfoList();

		//遍历删除目录下的文件
		for (int i = 0; i < list.size(); ++i)
		{
			if(list.at(i).fileName() == "." || list.at(i).fileName() == "..")
			{
				continue;
			}

			dirTmp.remove(list.at(i).fileName());
		}

		//删除tmp文件夹
		dir.rmdir(path);
	}
}

//恢复数据
int CardDoc::resumeDataFromZip(const QString &zipPath)
{
//	removeTempFile();
	QDir dir;
	bool exist = dir.exists("tmp1");

	if (!exist)
	{
		//创建tmp文件夹
		dir.mkdir("tmp1");
	}

	try
	{
		ACUnZip(zipPath.toStdString(), "tmp1\\");

		QFile file("tmp1\\paperSet.dat");
		if (!file.open(QIODevice::ReadOnly))
		{
			file.close();
			removeTempFile("tmp1");
			return 0;
		}

		QDataStream data;
		data.setDevice(&file);
		data.setVersion(QDataStream::Qt_4_8);

		quint32 magic;
		data >> magic;

		//判断是否为可识别格式
		if (magic != (quint32)PAPERSET_MAGIC_NUM)
		{
			file.close();
			removeTempFile("tmp1");
			return 0;
		}

		quint32 version;
		data >> version;

		//判断是否为可识别版本
		if (version != (quint32)VERSION)
		{
			file.close();
			removeTempFile("tmp1");
			return 0;
		}

		int type;
		data >> type;

		if (type != m_acType)
		{
			removeTempFile("tmp1");
			return 0;
		}
		//m_acType = type;

		QString courseName;
		data >> courseName;
	
		vector<PaperSet> paperSet;

		QList<QString> setId;
		QList<int> dpi;
		QList<int> pageCount;
		QList<QString> pageId;
		QList<bool> isPositive;
		int setSize;
		int pageIdx = 0;

		data >> setSize >> setId >> dpi
			 >> pageCount >> pageId >> isPositive;

		for (int i = 0; i < setSize; ++i)
		{
			PaperSet set;
			set.setId = setId.at(i);
			set.dpi = dpi.at(i);

			for (int j = 0; j < pageCount.at(i); ++j, ++pageIdx)
			{
				PaperPage page;
				page.pageId = pageId.at(pageIdx);
				page.isPositive = isPositive.at(pageIdx);
				set.page.push_back(page);
			}

			paperSet.push_back(set);
		}

		int find = isCourseExist(courseName);

		if (find > -1)
		{
			m_course.at(find).set.clear();
			m_course.at(find).set = paperSet;
		}
		else
		{
			Course course;
			course.courseName = courseName;
			course.set = paperSet;
			m_course.push_back(course);
		}

		file.close();
		//文件确认无误后，将tmp1文件夹删除，并解压到tmp中
		removeTempFile("tmp1");
		ACUnZip(zipPath.toStdString(), "tmp\\");
		QFile::remove("tmp\\paperSet.dat");
	}
	catch (exception)
	{
		return 0;
	}

	return 1;
	
}
