#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
#include "data.h"
#include "subroutines.h"


//*******����Ϊ���ļ������Ķ���ȫ�ֱ���*******//
//********ֻʹ��ֵ��ȫ�ֱ��������ڴ�����********//
//��������ز���
int N_mrt;                    //������ѡȡ��������ѡȡ�������߷������ΪN_mrt-1
int Nm;                       //ʵ��ѡȡ�������߷������
int Nt;                       //���������ĸ���
vector<int> m_fy;             //ʵ��ѡȡ�������߷������У������ΪNm
vector<thelta> thl;           //���Ǹ�˹�����
//���ζ�����ز���                   
double l_asm;                  //����������ĶԱ߾�
double l_cell;                 //������դԪ�ĶԱ߾�
double wid_clad;               //���׹ܺ��
//�������ز���              
int ncnum;                    //�����漰������Ŀ       
int MG;                       //��Ⱥ��Ⱥ��Ŀ
int BG;                       //��Ⱥ��Ⱥ��Ŀ
vector<int> BroG;             //����Ⱥ������Ⱥ��
int Nlege;                    //�����е����õ�չ��ɢ�����������������΢�۽����ж������������
//**********************************************//


void readInp()
{
	ncnum = 108;
	
}
bool readMicData(MicLib a)
{
	if(!a.readIn()) return false;
	return true;
}
class Result_Trim
{
	
};
class Result_View
{

};
