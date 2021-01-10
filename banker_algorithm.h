#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>


using namespace std;

vector<int> Available;				//��������Դ����
vector<vector<int>> Max;			//����������
vector<vector<int>> Allocation;		//��ǰ�������
vector<vector<int>> Need;			//�������

vector<int> Sequence;				//ִ��˳��

void input(string ifile)						//�ļ����������ֵ
{

}

bool compare(vector<int>& vec_low, vector<int>& vec)		//�ж� vec_low ���������Ƿ�С�� vec ����
{
	if (vec_low.size() != vec.size())
	{
		cout << "�������С��һ��" << endl;
		return false;
	}

	bool Need_low_than_Work = true;

	for (int i = 0;i < vec_low.size();i++)
	{
		Need_low_than_Work = Need_low_than_Work && (vec_low[i] <= vec[i]);
	}
	return Need_low_than_Work;
}


void banker_algorithm()				//���м��㷨������Դ����
{
	srand(time(0));

	while (1)
	{
		if (Max.empty())
		{
			//string filename;
			//cout << "�����������ļ�����������" << endl;
			//cin >> filename;
			//input(filename);

			cout << "����Ϊ�գ�������" << endl;
			break;
		}

		int Requst_ID;					//�����������
		vector<int> Requst;				//��������

		/************

		 Requst ��������

		************/


		if (!compare(Requst, Need[Requst_ID]))				//�ж����������Ƿ�С����������
		{
			cout << "���������������������������ԣ�" << endl;
			continue;
		}

		if (!compare(Requst, Available))					//�ж����������Ƿ�С�ڿ�������Դ��
		{
			cout << "ϵͳ���㹻��Դ����ȴ���" << endl;
			continue;
		}

		for (int i = 0;i < Available.size();i++)			//���Խ�����Դ����
		{
			Available[i] -= Requst[i];
			Allocation[Requst_ID][i] += Requst[i];
			Need[Requst_ID][i] -= Requst[i];
		}

		if (is_safety(Available, Max.size()))
		{
			cout << "����ɹ�" << endl;
		}
		else
		{
			cout << "������������,����ʧ�ܣ�" << endl;

			for (int i = 0;i < Available.size();i++)			//�ָ���Դ����ǰ����״��
			{
				Available[i] += Requst[i];
				Allocation[Requst_ID][i] -= Requst[i];
				Need[Requst_ID][i] += Requst[i];
			}
		}


		/**************
		
		 ��������

		**************/

	}

}



bool Finish_all_true(vector<bool> &Finish)				//�ж� Finish �Ƿ�ȫ��
{
	bool Finish_all_true = true;

	for (int i = 0;i < Finish.size();i++)
	{
		Finish_all_true = Finish_all_true && !Finish[i];
	}
	return Finish_all_true;

}

bool is_safety(vector<int>& Available,int process_size)					//��ȫ���㷨
{
	vector<int> Work = Available;
	vector<bool> Finish(process_size, false);

	for(int m=0;m<Finish.size();m++)				//���ѭ��������Ŀ�μ��ɱ�֤ȫ������
	{
		int count = 0;			//��ʶδ�������

		for (int i = 0;i < Finish.size();i++)			//���ٴ���һ��
		{
			if (!Finish[i] && compare(Need[i], Work))	//compare �ж� Need �����Ƿ�С�� Work
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

		if (Finish_all_true(Finish))			//�� Finish ȫ�漴�ɽ���ѭ������� true
		{
			return true;
		}

		if (count == Finish.size())				//��ѭ���� Finish ȫδ�������Ҳ�ȫ�棬��������޷�����
		{
			return false;
		}
	}

	return false;			// Finish ��ȫ����� false

}