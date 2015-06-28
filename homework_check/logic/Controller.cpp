/**
 * 控制器类实现，收集students信息，调用xmlReader，传递给算法检测
 * 
 * @author Bill Wang
 * 
 */
#include "Controller.h"

//直接与界面接触
bool Controller::startCheck(Ui::MainWindow *ui,string homeworkPath,string batch,string batchPath,vector <studentMap> stuMap)
{
// 	checkStudent.studentId = stuId;
// 	checkStudent.studentName = stuName;
//	this->studentPath = studentPath;

	this->homeworkPath = homeworkPath;
	this->batchPath = batchPath;
	this->batch=batch;
	this->stuMap=stuMap;
	
	//预处理
	runPreprocess(batchPath);

	Tools tool;
	tool.getAllStudentsNum(batch,allStudents);

	//填满【所有】学生信息
	fillStudents();


	//逐一赋值checkStudent和otherStudent
	for (int i=0;i<allStudents.size();i++)
	{
		cout<<"处理第"<<i+1<<"个学生\n";
		//system("pause");

		string tmpStuPath = batchPath;
		this->checkStudent.studentId = this->allStudents.at(i).studentId;
		this->checkStudent.studentName = this->allStudents.at(i).studentName;
		this->checkStudent.fileList = this->allStudents.at(i).fileList;
		tmpStuPath.append("\\");
		tmpStuPath.append(this->checkStudent.studentId);
		this->studentPath = tmpStuPath;

		this->otherStudents=this->allStudents;
		std::vector<StudentObj>::iterator it = this->otherStudents.begin()+i;
		this->otherStudents.erase(it);

		//已经得到待检测学生和其他学生信息，送去算法
		sendToCompare(ui);
	}


	return true;
}




//送去算法检测
//c  cpp  txt   java   pdf   doc   docx    h   cs
//< c, cpp >  <java>  <cs>  < txt,doc,docx,pdf>  <h>
void Controller::sendToCompare(Ui::MainWindow *ui)
{
	//处理之前，要删除已经存在的目录，可以删掉多级目录
	//system("rd /s /q c:\\StringCompare");

	//返回值为0，表示创建成功
	_mkdir("c:\\StrCompare\\");
	string path="c:\\StrCompare\\";
	string hwNum = QString::number(ui->HwNumComboBox->currentIndex(), 10).toStdString();
	path.append(hwNum);
	const char *path_c = path.c_str();
	_mkdir(path_c);
	path.append("\\");
	path.append(checkStudent.studentId);
	path.append("\\");
	path_c = path.c_str();
	if ((_mkdir(path_c)) != 0)
	{
		//否则创建失败
		cout<<path<<"已存在"<<endl;
		//return ;
	}

	for (int i=0;i<otherStudents.size();i++)   //【i代表哪一个otherStudents】
	{
		double similarity;
		QTreeWidgetItem *item = new QTreeWidgetItem(ui->rltTreeWidget);
		item->setText(0, QString::fromStdString(checkStudent.studentName));
		item->setText(1, QString::fromStdString(otherStudents.at(i).studentName));
		item->setText(2, "");
		ui->rltTreeWidget->addTopLevelItem(item);
		//对每个otherStudent的每个file与待检测student的file（类型相同）的进行检测
		for (int j=0;j<checkStudent.fileList.size();j++)  //【j代表checkStudent的那个文件】
		{
			//checkStudent的待检测文件为< c, cpp >
			if (checkStudent.fileList.at(j).getFileType().compare("c")==0 || 
				checkStudent.fileList.at(j).getFileType().compare("cpp")==0)
			{
				//遍历otherStudents的文件，找到< c, cpp >
				for (int k=0;k<otherStudents.at(i).fileList.size();k++) //【k代表otherStudents的那个文件】
				{
					if (otherStudents.at(i).fileList.at(k).getFileType().compare("c")==0 ||
						otherStudents.at(i).fileList.at(k).getFileType().compare("cpp")==0)
					{
						//输出 test
						cout<<"in controller < c, cpp >"<<endl;
						cout<<checkStudent.fileList.at(j).getFileName()<<"."<<checkStudent.fileList.at(j).getFileType()<<"  ";
						cout<<otherStudents.at(i).fileList.at(k).getFileName()<<"."<<otherStudents.at(i).fileList.at(k).getFileType()<<endl;
						similarity=stringCompare(hwNum,checkStudent,otherStudents.at(i),checkStudent.fileList.at(j),otherStudents.at(i).fileList.at(k),0);
						
						QTreeWidgetItem *chil_item = new QTreeWidgetItem();
						chil_item->setText(0, QString::fromStdString(checkStudent.fileList.at(j).getFileName())+"."+QString::fromStdString(checkStudent.fileList.at(j).getFileType()));
						chil_item->setText(1, QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileName())+"."+QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileType()));
						if(similarity==-1)
						{
							QString path_str = QString::fromStdString(path);
							path_str =path_str+QString::fromStdString(otherStudents.at(i).studentId)+"-"+QString::fromStdString(checkStudent.fileList.at(j).getFileName())+"."+QString::fromStdString(checkStudent.fileList.at(j).getFileType())+"-"+QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileName())+"."+QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileType())+"@.txt";
							QFile file(path_str);
							if(!file.open(QIODevice::ReadOnly | QIODevice::Text))  
								qDebug()<<"Can't open the file!"<<endl;         
							QString str = file.readLine();    
							str.chop(1);
							qDebug()<< str;
							chil_item->setText(2, str);
							if(str.toInt()!=0)
							{	
								item->setTextColor(0 ,Qt::red);
								item->setTextColor(1 ,Qt::red);
							}
						}
						else
						{
							chil_item->setText(2, QString::number(similarity));
							if(similarity!=0)
							{	
								item->setTextColor(0 ,Qt::red);
								item->setTextColor(1 ,Qt::red);
							}
						}
						item->addChild(chil_item);
					}
				}
			}


			//checkStudent的待检测文件为<java>
			else if (checkStudent.fileList.at(j).getFileType().compare("java")==0 )
			{
				//遍历otherStudents的文件，找到< c, cpp >
				for (int k=0;k<otherStudents.at(i).fileList.size();k++) //k代表otherStudents的那个文件
				{
					if (otherStudents.at(i).fileList.at(k).getFileType().compare("java")==0 )
					{
						//输出 test
						cout<<"in controller <java>"<<endl;
						cout<<checkStudent.fileList.at(j).getFileName()<<"."<<checkStudent.fileList.at(j).getFileType()<<"  ";
						cout<<otherStudents.at(i).fileList.at(k).getFileName()<<"."<<otherStudents.at(i).fileList.at(k).getFileType()<<endl;
						similarity=stringCompare(hwNum, checkStudent,otherStudents.at(i),checkStudent.fileList.at(j),otherStudents.at(i).fileList.at(k),0);

						QTreeWidgetItem *chil_item = new QTreeWidgetItem();
						chil_item->setText(0, QString::fromStdString(checkStudent.fileList.at(j).getFileName())+"."+QString::fromStdString(checkStudent.fileList.at(j).getFileType()));
						chil_item->setText(1, QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileName())+"."+QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileType()));
						if(similarity==-1)
						{
							QString path_str = QString::fromStdString(path);
							path_str =path_str+QString::fromStdString(otherStudents.at(i).studentId)+"-"+QString::fromStdString(checkStudent.fileList.at(j).getFileName())+"."+QString::fromStdString(checkStudent.fileList.at(j).getFileType())+"-"+QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileName())+"."+QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileType())+"@.txt";
							QFile file(path_str);
							if(!file.open(QIODevice::ReadOnly | QIODevice::Text))  
								qDebug()<<"Can't open the file!"<<endl;         
							QByteArray line = file.readLine();    
							QString str(line);
							str.chop(1);
							qDebug()<< str;
							chil_item->setText(2, str);
							if(str.toInt()!=0)
							{	
								item->setTextColor(0 ,Qt::red);
								item->setTextColor(1 ,Qt::red);
							}
						}
						else
						{
							chil_item->setText(2, QString::number(similarity));
							if(similarity!=0)
							{	
								item->setTextColor(0 ,Qt::red);
								item->setTextColor(1 ,Qt::red);
							}
						}
						item->addChild(chil_item);
					}
				}
			}

			//checkStudent的待检测文件为<cs>
			else if (checkStudent.fileList.at(j).getFileType().compare("cs")==0 )
			{
				//遍历otherStudents的文件，找到< c, cpp >
				for (int k=0;k<otherStudents.at(i).fileList.size();k++) //k代表otherStudents的那个文件
				{
					if (otherStudents.at(i).fileList.at(k).getFileType().compare("cs")==0 )
					{
						//输出 test
						cout<<"in controller <cs>"<<endl;
						cout<<checkStudent.fileList.at(j).getFileName()<<"."<<checkStudent.fileList.at(j).getFileType()<<"  ";
						cout<<otherStudents.at(i).fileList.at(k).getFileName()<<"."<<otherStudents.at(i).fileList.at(k).getFileType()<<endl;
						similarity=stringCompare(hwNum, checkStudent,otherStudents.at(i),checkStudent.fileList.at(j),otherStudents.at(i).fileList.at(k),0);

						QTreeWidgetItem *chil_item = new QTreeWidgetItem();
						chil_item->setText(0, QString::fromStdString(checkStudent.fileList.at(j).getFileName())+"."+QString::fromStdString(checkStudent.fileList.at(j).getFileType()));
						chil_item->setText(1, QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileName())+"."+QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileType()));
						if(similarity==-1)
						{
							QString path_str = QString::fromStdString(path);
							path_str =path_str+QString::fromStdString(otherStudents.at(i).studentId)+"-"+QString::fromStdString(checkStudent.fileList.at(j).getFileName())+"."+QString::fromStdString(checkStudent.fileList.at(j).getFileType())+"-"+QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileName())+"."+QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileType())+"@.txt";
							QFile file(path_str);
							if(!file.open(QIODevice::ReadOnly | QIODevice::Text))  
								qDebug()<<"Can't open the file!"<<endl;         
							QByteArray line = file.readLine();    
							QString str(line);
							str.chop(1);
							qDebug()<< str;
							chil_item->setText(2, str);
							if(str.toInt()!=0)
							{	
								item->setTextColor(0 ,Qt::red);
								item->setTextColor(1 ,Qt::red);
							}
						}
						else
						{
							chil_item->setText(2, QString::number(similarity));
							if(similarity!=0)
							{	
								item->setTextColor(0 ,Qt::red);
								item->setTextColor(1 ,Qt::red);
							}
						}
						item->addChild(chil_item);
					}
				}
			}


			//checkStudent的待检测文件为< txt,doc,docx,pdf>
			else if (checkStudent.fileList.at(j).getFileType().compare("txt")==0 ||
					 checkStudent.fileList.at(j).getFileType().compare("doc")==0 ||
					 checkStudent.fileList.at(j).getFileType().compare("docx")==0 ||
					 checkStudent.fileList.at(j).getFileType().compare("pdf")==0 )
			{
				//遍历otherStudents的文件，找到< txt,doc,docx,pdf>
				for (int k=0;k<otherStudents.at(i).fileList.size();k++) //k代表otherStudents的那个文件
				{
					if (otherStudents.at(i).fileList.at(k).getFileType().compare("txt")==0 ||
						otherStudents.at(i).fileList.at(k).getFileType().compare("doc")==0 ||
						otherStudents.at(i).fileList.at(k).getFileType().compare("docx")==0 ||
						otherStudents.at(i).fileList.at(k).getFileType().compare("pdf")==0 )
					{
						//输出 test
						cout<<"in controller < txt,doc,docx,pdf>"<<endl;
						cout<<checkStudent.fileList.at(j).getFileName()<<"."<<checkStudent.fileList.at(j).getFileType()<<"  ";
						cout<<otherStudents.at(i).fileList.at(k).getFileName()<<"."<<otherStudents.at(i).fileList.at(k).getFileType()<<endl;
						similarity=stringCompare(hwNum, checkStudent,otherStudents.at(i),checkStudent.fileList.at(j),otherStudents.at(i).fileList.at(k),1);

						QTreeWidgetItem *chil_item = new QTreeWidgetItem();
						chil_item->setText(0, QString::fromStdString(checkStudent.fileList.at(j).getFileName())+"."+QString::fromStdString(checkStudent.fileList.at(j).getFileType()));
						chil_item->setText(1, QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileName())+"."+QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileType()));
						if(similarity==-1)
						{
							QString path_str = QString::fromStdString(path);
							path_str =path_str+QString::fromStdString(otherStudents.at(i).studentId)+"-"+QString::fromStdString(checkStudent.fileList.at(j).getFileName())+"."+QString::fromStdString(checkStudent.fileList.at(j).getFileType())+"-"+QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileName())+"."+QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileType())+"@.txt";
							QFile file(path_str);
							if(!file.open(QIODevice::ReadOnly | QIODevice::Text))  
								qDebug()<<"Can't open the file!"<<endl;         
							QByteArray line = file.readLine();    
							QString str(line);
							str.chop(1);
							qDebug()<< str;							
							chil_item->setText(2, str);
							if(str.toInt()!=0)
							{	
								item->setTextColor(0 ,Qt::red);
								item->setTextColor(1 ,Qt::red);
							}
						}
						else
						{
							chil_item->setText(2, QString::number(similarity));
							if(similarity!=0)
							{	
								item->setTextColor(0 ,Qt::red);
								item->setTextColor(1 ,Qt::red);
							}
						}
						item->addChild(chil_item);
					}
				}
			}


			//checkStudent的待检测文件为< h >
			else if (checkStudent.fileList.at(j).getFileType().compare("h")==0 )
			{
				//遍历otherStudents的文件，找到< c, cpp >
				for (int k=0;k<otherStudents.at(i).fileList.size();k++) //k代表otherStudents的那个文件
				{
					if (otherStudents.at(i).fileList.at(k).getFileType().compare("h")==0 )
					{
						//输出 test
						cout<<"in controller <h>"<<endl;
						cout<<checkStudent.fileList.at(j).getFileName()<<"."<<checkStudent.fileList.at(j).getFileType()<<"  ";
						cout<<otherStudents.at(i).fileList.at(k).getFileName()<<"."<<otherStudents.at(i).fileList.at(k).getFileType()<<endl;
						similarity=stringCompare(hwNum, checkStudent,otherStudents.at(i),checkStudent.fileList.at(j),otherStudents.at(i).fileList.at(k),0);

						QTreeWidgetItem *chil_item = new QTreeWidgetItem();
						chil_item->setText(0, QString::fromStdString(checkStudent.fileList.at(j).getFileName())+"."+QString::fromStdString(checkStudent.fileList.at(j).getFileType()));
						chil_item->setText(1, QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileName())+"."+QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileType()));
						if(similarity==-1)
						{
							QString path_str = QString::fromStdString(path);
							path_str =path_str+QString::fromStdString(otherStudents.at(i).studentId)+"-"+QString::fromStdString(checkStudent.fileList.at(j).getFileName())+"."+QString::fromStdString(checkStudent.fileList.at(j).getFileType())+"-"+QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileName())+"."+QString::fromStdString(otherStudents.at(i).fileList.at(k).getFileType())+"@.txt";
							QFile file(path_str);
							if(!file.open(QIODevice::ReadOnly | QIODevice::Text))  
								qDebug()<<"Can't open the file!"<<endl;         
							QByteArray line = file.readLine();    
							QString str(line);
							str.chop(1);
							qDebug()<< str;
							chil_item->setText(2, str);
							if(str.toInt()!=0)
							{	
								item->setTextColor(0 ,Qt::red);
								item->setTextColor(1 ,Qt::red);
							}
						}
						else
						{
							chil_item->setText(2, QString::number(similarity));
							if(similarity!=0)
							{	
								item->setTextColor(0 ,Qt::red);
								item->setTextColor(1 ,Qt::red);
							}
						}
						item->addChild(chil_item);
					}
				}
			}



		}
	}
}



//填满所有学生信息
void Controller::fillStudents()
{
	for (int i=0;i<allStudents.size();i++)
	{
		for (int j=0;j<stuMap.size();j++)
		{
			if ( allStudents.at(i).studentId.compare(stuMap.at(j).studentId) == 0 )
				allStudents.at(i).studentName = stuMap.at(j).studentName;
		}
	}
}


//调用预处理
bool Controller::runPreprocess(string batchPath)
{
	//进行预处理之前，要删除已经存在的c:\pre_out
	//system("rd /s /q c:\\pre_out");

	//"..\\run_pre.bat "+batchPath+" c:\\";
	//string cmd = "..\\run_pre\\run_pre.bat ";
	string cmd = "c:\\run_pre\\run_pre.bat "; //方便调试，临时用c盘

	cmd.append(batchPath);
	cmd.append(" c:\\");
	cout<<"预处理cmd == "<<cmd<<endl;

	const char *cCmd = cmd.data();
	system(cCmd);

	cout<<"Preprocess is over\n"<<endl;

	return true;
}