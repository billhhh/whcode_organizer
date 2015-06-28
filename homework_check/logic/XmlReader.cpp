/**
 * 读取xml的工具类实现
 * 
 * @author Bill Wang
 * 
 */
#include "XmlReader.h"

void XmlReader::test()
{
	cout<<"just for testing!!"<<endl;
}

bool XmlReader::XmlIO(string xmlPath,vector<FileObj> &fileList)
{
	//xml读取方法，传入解析路径，返回填充好的student对象
	cout<<"进入XmlIO1方法"<<endl;

	if(!this->getFileList(xmlPath,fileList))
		return false;

	else
	{
		//正确读取xml
		return true;
	}

}

//重载的方法，可传入学生ID和name
bool XmlReader::XmlIO(string stuName,string stuId,string xmlPath,StudentObj &stu)
{
	//xml读取方法，传入解析路径，返回填充好的student对象
	cout<<"进入XmlIO2方法"<<endl;

	vector<FileObj> fileList;
	if(!this->getFileList(xmlPath,fileList))
		return false;

	else
	{
		//正确读取xml
		stu.studentName = stuName;
		stu.studentId = stuId;
		stu.fileList = fileList;

		return true;
	}
}


//重载的方法，可传入已有ID和姓名的学生，直接获得完整的学生对象
bool XmlReader::XmlIO(string xmlPath,StudentObj &stu)
{
	//xml读取方法，传入解析路径，返回填充好的student对象
	cout<<"进入XmlIO3方法"<<endl;

	cout<<"xmlPath = "<<xmlPath<<endl;

	vector<FileObj> fileList;
	if(!this->getFileList(xmlPath,fileList))
		return false;

	else
	{
		//正确读取xml
		stu.fileList = fileList;
		return true;
	}

}




//private方法
//传入XML路径，返回引用vector
bool XmlReader::getFileList(string xmlPath,vector<FileObj> &fileList)
{
	if("" == xmlPath)
	{
		cout<<"Filename is Null"<<endl;
		return false;
	}

	QDomDocument document;

	QString path = QString::fromStdString(xmlPath);
	QFile xmlFile(path); //xml文件路径，QString格式传入构造函数

	if (!xmlFile.open(QIODevice::ReadOnly))
	{
		return false;
	}
	// 	if (!document.setContent(&xmlFile))
	// 	{
	// 		xmlFile.close();
	// 		return false;
	// 	}

	//转码
	QTextStream floStream(&xmlFile);
	QTextCodec *codec=QTextCodec::codecForName("UTF-8");
	floStream.setCodec(codec);
	QString xmlDataStr = floStream.readAll();
	xmlFile.close();
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb2312"));

	//cout<<xmlDataStr.toStdString()<<endl;

	if (!document.setContent(xmlDataStr))
	{
		printf("载入xml失败,%s,%d \n",__FILE__,__LINE__);
		return false ;
	}


	QDomElement root = document.documentElement();
	QDomNode node=root.firstChild();   //QDomElement 对象才有tagName,QDomNode需要toElement

	//打印测试
	//qDebug()<<root.tagName();
	//cout<<node.toElement().text().toStdString()<<endl;
	//cout<<node.toElement().tagName().toStdString()<<endl;
	// 	qDebug(node.nodeName().toAscii());            //nodeName
	// 	qDebug(node.toElement().text().toAscii());    //内容

	QDomNode fileNode=node; //大的文件节点
	while(!fileNode.isNull())
	{
		if (!fileNode.toElement().isNull()){
			//cout<<qPrintable(fileElem.tagName())<<endl;

			QDomNode tmpNode=fileNode.firstChild();
			FileObj tmpFile;
			while(!tmpNode.isNull())
			{
				if (tmpNode.toElement().tagName().compare("name")==0)
					tmpFile.setFileName(tmpNode.toElement().text().toStdString());
				else if(tmpNode.toElement().tagName().compare("type")==0)
					tmpFile.setFileType(tmpNode.toElement().text().toStdString());
				else if(tmpNode.toElement().tagName().compare("content")==0)
					tmpFile.setContent(tmpNode.toElement().text().toStdString());

				tmpNode = tmpNode.nextSibling();
			}
			//测试file对象
			//cout<<"fileName = "<<tmpFile.getFileName()<<endl;
			//cout<<"fileContent = "<<tmpFile.getContent()<<endl;

			fileList.push_back(tmpFile);
			//cout<<"fileList.size = "<<fileList.size()<<endl;

		}



		fileNode = fileNode.nextSibling();
	}

	return true;
}