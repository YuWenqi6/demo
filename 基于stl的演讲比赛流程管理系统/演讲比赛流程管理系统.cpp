#include<iostream>
#include<string>
using namespace std;
#include"speechManager.h"
int main()
{
	SpeechManager sm;
	/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin();it != sm.m_Speaker.end();it++)
	{
		cout << "选手的编号：" << it->first << "选手姓名："<< it->second.m_Name <<"选手编号："<<it->second.m_Score[0] << endl;
	}*/
	int choice;
	while (true)
	{
		sm.show_Menu();
		cout << "请输入你的选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://开始演讲比赛
			sm.startSpeech();
			break;
		case 2://查看往届比赛记录
			sm.loadRecord();
			break;
		case 3://清空比赛记录
			sm.clearRecord();
			break;
		case 0://退出系统
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}