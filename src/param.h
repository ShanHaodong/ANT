#ifndef param
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <vector>
using namespace std;
//���ó���
const double Pi = 3.14159;
const double NA = 6.022E23;
//��������ز���
 extern int N_mrt;                    //������ѡȡ��������ѡȡ�������߷������ΪN_mrt-1
 extern int Nm;                       //ʵ��ѡȡ�������߷������
 extern int Nt;                       //���������ĸ���
 extern vector<int> m_fy;             //ʵ��ѡȡ�������߷������У������ΪNm
 struct thelta                        //���Ǹ�˹������Զ�����������
 {
	 double sin;
	 double cos;
	 double w;
 };
 extern vector<thelta> thl;           //���Ǹ�˹�����
 //���ζ�����ز���                   
 extern double l_asm;                  //����������ĶԱ߾�
 extern double l_cell;                 //������դԪ�ĶԱ߾�
 extern double wid_clad;               //���׹ܺ��
//�������ز���    
 extern int ncnum;                    //�����漰������Ŀ
 extern int MG;                       //��Ⱥ��Ⱥ��Ŀ
 extern int BG;                       //��Ⱥ��Ⱥ��Ŀ
 extern vector<int> BroG;             //����Ⱥ������Ⱥ��
 extern int Nlege;                    //�����е����õ�չ��ɢ�����������������΢�۽����ж������������
//����������                       
extern vector<double> keff;           //��Ч��ֳ���ӵļ�¼����
extern clock_t begin_main,end_main,begin_readIn,end_readIn;    //��¼��������ʱ��


#endif // !param                     
