#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>


using namespace std;

vector<int> Available;				//可利用资源向量
vector<vector<int>> Max;			//最大需求矩阵
vector<vector<int>> Allocation;		//当前分配矩阵
vector<vector<int>> Need;			//需求矩阵

vector<int> Sequence;				//执行顺序

void input(string ifile)						//文件输入各矩阵值
{

}

bool compare(vector<int>& vec_low, vector<int>& vec)		//判断 vec_low 向量各项是否小于 vec 向量
{
	if (vec_low.size() != vec.size())
	{
		cout << "两数组大小不一致" << endl;
		return false;
	}

	bool Need_low_than_Work = true;

	for (int i = 0;i < vec_low.size();i++)
	{
		Need_low_than_Work = Need_low_than_Work && (vec_low[i] <= vec[i]);
	}
	return Need_low_than_Work;
}


void banker_algorithm()				//银行家算法进行资源分配
{
	srand(time(0));

	while (1)
	{
		if (Max.empty())
		{
			//string filename;
			//cout << "请输入数据文件名导入数据" << endl;
			//cin >> filename;
			//input(filename);

			cout << "数据为空，请重试" << endl;
			break;
		}

		int Requst_ID;					//请求向量序号
		vector<int> Requst;				//请求向量

		/************

		 Requst 向量输入

		************/


		if (!compare(Requst, Need[Requst_ID]))				//判断申请数量是否小于需求数量
		{
			cout << "申请数量超过所需数量，请重试！" << endl;
			continue;
		}

		if (!compare(Requst, Available))					//判断申请数量是否小于可利用资源量
		{
			cout << "系统无足够资源，请等待！" << endl;
			continue;
		}

		for (int i = 0;i < Available.size();i++)			//尝试进行资源分配
		{
			Available[i] -= Requst[i];
			Allocation[Requst_ID][i] += Requst[i];
			Need[Requst_ID][i] -= Requst[i];
		}

		if (is_safety(Available, Max.size()))
		{
			cout << "分配成功" << endl;
		}
		else
		{
			cout << "存在死锁风险,分配失败！" << endl;

			for (int i = 0;i < Available.size();i++)			//恢复资源分配前分配状况
			{
				Available[i] += Requst[i];
				Allocation[Requst_ID][i] -= Requst[i];
				Need[Requst_ID][i] += Requst[i];
			}
		}


		/**************
		
		 结束程序

		**************/

	}

}



bool Finish_all_true(vector<bool> &Finish)				//判断 Finish 是否全真
{
	bool Finish_all_true = true;

	for (int i = 0;i < Finish.size();i++)
	{
		Finish_all_true = Finish_all_true && !Finish[i];
	}
	return Finish_all_true;

}

bool is_safety(vector<int>& Available,int process_size)					//安全性算法
{
	vector<int> Work = Available;
	vector<bool> Finish(process_size, false);

	for(int m=0;m<Finish.size();m++)				//最多循环进程数目次即可保证全部遍历
	{
		int count = 0;			//标识未处理次数

		for (int i = 0;i < Finish.size();i++)			//最少处理一项
		{
			if (!Finish[i] && compare(Need[i], Work))	//compare 判断 Need 各项是否小于 Work
			{
				for (int j = 0;j < Work.size();j++)
				{
					Work[i] = Work[i] + Allocation[i][j];
				}

				Finish[i] = true;
			}
			else
			{
				count++;
			}
		}

		if (Finish_all_true(Finish))			//若 Finish 全真即可结束循环，输出 true
		{
			return true;
		}

		if (count == Finish.size())				//若循环中 Finish 全未经处理且不全真，则必有项无法分配
		{
			return false;
		}
	}

	return false;			// Finish 不全真输出 false

}