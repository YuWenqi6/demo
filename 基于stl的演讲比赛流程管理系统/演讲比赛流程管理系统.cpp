#include<iostream>
#include<string>
using namespace std;
#include"speechManager.h"
int main()
{
	SpeechManager sm;
	/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin();it != sm.m_Speaker.end();it++)
	{
		cout << "ѡ�ֵı�ţ�" << it->first << "ѡ��������"<< it->second.m_Name <<"ѡ�ֱ�ţ�"<<it->second.m_Score[0] << endl;
	}*/
	int choice;
	while (true)
	{
		sm.show_Menu();
		cout << "���������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://��ʼ�ݽ�����
			sm.startSpeech();
			break;
		case 2://�鿴���������¼
			sm.loadRecord();
			break;
		case 3://��ձ�����¼
			sm.clearRecord();
			break;
		case 0://�˳�ϵͳ
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