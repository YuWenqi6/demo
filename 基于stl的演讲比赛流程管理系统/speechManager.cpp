#include"speechManager.h"
SpeechManager::SpeechManager()//构造函数
{
	//初始化容器和属性
	this->initSpeech();
	//创建12名选手
	this->createSpeaker();
}
void SpeechManager::show_Menu()//展示菜单
{
	cout << "*******************************" << endl;
	cout << "********欢迎参加演讲比赛*******" << endl;
	cout << "********1、开始演讲比赛********" << endl;
	cout << "********2、查看往届记录********" << endl;
	cout << "********3、清空比赛记录********" << endl;
	cout << "********0、退出比赛程序********" << endl;
	cout << "*******************************" << endl;
	cout << endl;
}
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0;i < nameSeed.size();i++)
	{
		string name = "选手";
		name += nameSeed[i];
		//创建具体选手
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0;j < 2;j++)
		{
			sp.m_Score[j] = 0;
		}
		//创建选手编号 并放到v1容器中
		this->v1.push_back(i + 10001);
		//选手编号以及以及对应选手 放入到map容器中
		this->m_Speaker.insert(make_pair(i + 10001,sp));
	}
}
void SpeechManager::startSpeech()//开始比赛 比赛整个流程控制函数
{
	//第一轮开始比赛
	
	//1、抽签
	this->speechDraw();
	//2、比赛
	this->speechContest();
	//3、显示晋级结果
	this->showScore();
	//第二轮开始比赛
	this->m_index++;
	//1、抽签
	this->speechDraw();
	//2、比赛
	this->speechContest();
	//3、显示晋级结果
	this->showScore();
	//4、保存分数到文件中
	this->saveRecord();
	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}
void SpeechManager::speechDraw()//抽签
{
	cout << "第" << this->m_index << "轮比赛选手正在抽签" << endl;
	cout << "-------------------" << endl;
	cout << "抽签后的顺序为" << endl;
	if (this->m_index == 1)
	{
		//第一轮比赛
		random_shuffle(v1.begin(), v1.end());//打乱顺序
		for (vector<int>::iterator it = v1.begin();it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//第二轮比赛
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin();it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-------------------" << endl;
	system("pause");
	cout << endl;
}
//比赛
void SpeechManager::speechContest()
{
	cout << "第" << this->m_index << "轮比赛正式开始" << endl;
	multimap<double, int, greater<double>>groupScore;//临时容器 用来存放key选手分数 value 选手编号
	int num = 0;//记录人员数，6个为一组
	vector<int>v_Src;//比赛的人员编号容器

		if (this->m_index == 1)
		{
			v_Src = v1;//将第一轮比赛人员的编号赋值给v_Src容器
	    }
		else
		{
			v_Src = v2;//否则将第二轮比赛人员的编号赋值给v_Src容器
		}
		for (vector<int>::iterator it = v_Src.begin();it != v_Src.end();it++)
		{
			num++;
			deque<double>d;//队列用于存放评委打的分数
			for (int i = 0;i < 10;i++)
			{
				double score = (rand() % 401 + 600) / 10.f;
				d.push_back(score);
			}
			sort(d.begin(), d.end(), greater<double>());//排序 降序
			d.pop_front();//去掉最高分
			d.pop_back();//去掉最低分
			double sum = accumulate(d.begin(), d.end(),0.0f);//总分
			double avg = sum / (double)d.size();//平均分
			this->m_Speaker[*it].m_Score[m_index - 1] = avg;  
			//6个人一组用临时容器保存 key 平均值 value 编号
			groupScore.insert(make_pair(avg, *it));
			if (num % 6 == 0)
			{
				cout << "第" << num / 6 << "小组比赛名次" << endl;
				for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();it != groupScore.end();it++)
				{
					cout << "编号：" << it->second << "姓名:" <<
						this->m_Speaker[it->second].m_Name << 
						"成绩：" << it->first << endl;
				}
				int count = 0;
				//取前三名
				for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();it != groupScore.end() && count < 3;it++, count++)
				{
					if (this->m_index == 1)
					{
						v2.push_back(it->second);

					}
					else
					{
						vVictory.push_back(it->second);
					}
				}
				groupScore.clear();
				cout << endl;
			}
	    }
		cout << "---------------------" << endl;
		system("pause");
		cout << endl;
}
void SpeechManager::showScore()
{
	cout << "第" << this->m_index << "轮晋级选手信息如下：" << endl;
	vector<int>v;
	if (this->m_index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin();it != v.end();it++)
	{
		cout << "选手编号:"<<*it << "选手姓名:"<<this->m_Speaker[*it].m_Name
			<<"选手得分:"<<this->m_Speaker[*it].m_Score[this->m_index-1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//用追加的方式写文件
	//将每个选手数据写入到文件中
	for (vector<int>::iterator it = vVictory.begin();it != vVictory.end();it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Name << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	//关闭
	ofs.close();
	cout << "已保存所有分数" << endl;
}
//读取记录
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//读文件
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;

	}
	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);//将上面读取的单个字符放回来
	string data;
	int index = 0;
	while (ifs >> data)
	{
		/*cout << data << endl;*/
		vector<string>v;
		int pos = -1;//查到逗号位置的变量
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//未找到
				break;
			}
			string temp = data.substr(start, pos - start);
			/*cout << temp << endl;*/
			v.push_back(temp);
			start = pos + 1;
			
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
 	ifs.close();
	for (map<int, vector<string>>::iterator it = m_Record.begin();it != m_Record.end();it++)
	{
		cout << "第" << it->first +1<< "轮比赛获奖名单:" << endl;
		cout << "冠军编号：" << it->second[0] << "冠军姓名:" << it->second[1] << "冠军分数:" <<
			it->second[2] << endl;
	}
}
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{ 
	for (int i = 0;i < this->m_Record.size();i++)
	{
		cout << "第" << i + 1 << "届" << "冠军编号:" << this->m_Record[i][0] << "选手名:"
			<< this->m_Record[i][1] << "选手得分:" << this->m_Record[i][2] << endl;
	}
	}
	system("pause");
	system("cls");
}
void SpeechManager::clearRecord()
{
	cout << "是否清空文件 1.是 2.否" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);//文件存在就清空
		ofs.close();
		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();
		cout << "清空成功！" << endl;

	}
	system("pause");
	system("cls");

}
void SpeechManager::exitSystem()//退出程序
{
	cout << "欢迎下次使用" << endl; 
	system("pause");
	exit(0);
}
SpeechManager::~SpeechManager()//析构函数
{
	

}
void SpeechManager::initSpeech()
{
	//容器都为空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	//初始化比赛轮数
	this->m_index = 1;
}