#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<deque>
#include<numeric>
#include"speaker.h"
#include<algorithm>
#include<functional>
#include<fstream>
using namespace std;
//�ݽ�������
class SpeechManager
{
public:
	//���캯��
	SpeechManager();
	//�˵�����
	void show_Menu();
	//����12��ѡ��
	void createSpeaker();
	//��ʼ���� �����������̿��ƺ���
	void startSpeech();
	//�˳��˵�
	void exitSystem();
	//��ǩ
	void speechDraw();
	//����
	void speechContest();
	//��ʾ�÷�
	void showScore();
	//�������
	void saveRecord();
	//��ȡ��¼
	void loadRecord();
	//��ռ�¼
	void clearRecord();
	// �ļ�Ϊ�յı�־
	bool fileIsEmpty;
	// �����¼
	map<int, vector<string>> m_Record;
	//��ʾ�����¼
	void showRecord();
	//��������
	~SpeechManager();
	//��ʼ������������
	void initSpeech();
	//�����һ�ֱ���ѡ�ֵı�ŵ�����
	vector<int> v1;
	//����ڶ��ֽ�������ѡ�ֵı�ŵ�����
	vector<int> v2;
	//���������ʤ��ǰ����ѡ�ֵı�ŵ�����
	vector<int> vVictory;
	//��ű���Լ���Ӧѡ�ֵ�����
	map<int, Speaker>m_Speaker;
	//��ű�������
	int m_index;
};
