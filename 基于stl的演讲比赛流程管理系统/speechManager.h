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
//演讲管理类
class SpeechManager
{
public:
	//构造函数
	SpeechManager();
	//菜单功能
	void show_Menu();
	//创建12名选手
	void createSpeaker();
	//开始比赛 比赛整个流程控制函数
	void startSpeech();
	//退出菜单
	void exitSystem();
	//抽签
	void speechDraw();
	//比赛
	void speechContest();
	//显示得分
	void showScore();
	//保存分数
	void saveRecord();
	//读取记录
	void loadRecord();
	//清空记录
	void clearRecord();
	// 文件为空的标志
	bool fileIsEmpty;
	// 往届记录
	map<int, vector<string>> m_Record;
	//显示往届记录
	void showRecord();
	//析构函数
	~SpeechManager();
	//初始化容器和属性
	void initSpeech();
	//保存第一轮比赛选手的编号的容器
	vector<int> v1;
	//保存第二轮晋级比赛选手的编号的容器
	vector<int> v2;
	//保存第三轮胜出前三名选手的编号的容器
	vector<int> vVictory;
	//存放编号以及对应选手的容器
	map<int, Speaker>m_Speaker;
	//存放比赛轮数
	int m_index;
};
