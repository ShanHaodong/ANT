#include "stdio.h"
#include "math.h"
#include "string.h"
#include<stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
#include <iomanip>
#include "data.h"
#include "subroutines.h"

//*******����Ϊ���ļ������Ķ���ȫ�ֱ���*******//
//********ֻʹ��ֵ��ȫ�ֱ��������ڴ�����********//
vector<double> keff;
clock_t begin_main, end_main, begin_readIn, end_readIn;
//**********************************************//
void main(int argc, char* argv[])
{
	double ver = 0.1;
	char* Name = "Advanced Neutronic Transport code";
/*	printf("*******************************************************************************\n");
	printf("*           AAA                    NNN     NN              TTTTTTTTTTTT       *\n");
	printf("*          AA AA                   NN NN   NN                   TT            *\n");
	printf("*         AA   AA                  NN  NN  NN                   TT            *\n");
	printf("*        AA     AA                 NN  NN  NN                   TT            *\n");
	printf("*        AAAAAAAAA                 NN  NN  NN                   TT            *\n");
	printf("*        AA     AA                 NN  NN  NN                   TT            *\n");
	printf("*        AA     AA                 NN   NN NN                   TT            *\n");
	printf("*        AA     AA                 NN     NNN                   TT            *\n");
	printf("*******************************************************************************\n\n");
	printf("            ������ʹ�õ���  %s  Ver %2.1f \n\n", Name, ver);
	printf("                          �й�ԭ���ܿ�ѧ�о�Ժ   ���ƶ� \n\n");
	printf("               SHAN Haodong from CIAE (E-Mail:shanhaodong@126.com)\n\n");*/ 


	printf(" ******************************************************************************\n");
	printf(" *          AAA                   NN      NN               TTTTTTTTTTTT       *\n");
	printf(" *         AA AA                  NNNN    NN                    TT            *\n");
	printf(" *        AA   AA                 NN  NN  NN                    TT            *\n");
	printf(" *       AAAAAAAAA                NN   NN NN                    TT            *\n");
	printf(" *      AA       AA               NN    NNNN                    TT            *\n");
	printf(" *     AA         AA              NN      NN                    TT            *\n");
	printf(" ******************************************************************************\n\n");
	cout<<"            ������ʹ�õ��� "<<Name<<"  Ver "<<ver<<" \n\n";
	printf("                          �й�ԭ���ܿ�ѧ�о�Ժ   ���ƶ� \n\n");
	printf("               SHAN Haodong from CIAE (E-Mail:shanhaodong@126.com)\n\n");

	//system("hello.vbs");  //���Զ��߳�
	showTime("                       --------------׼������--------------");
	begin_main = clock();
	//system("if exist ANT.exe (copy ANT.exe ANT0) ");
	showTime("                       -----------���ڶ�ȡ���뿨-----------");
	readInp();
	showTime("                       -----------���뿨��ȡ���-----------");
	MicLib miclib=MicLib();
	if (!readMicData(miclib))
	{
		system("pause");
		return;
	}
	showTime("                       ------------����������------------");
	if (!checkData(miclib))
	{
		//system("error.vbs"); //���Զ��߳�
		system("pause");
		return;
	}
	showTime("                       ------------�����������------------");
	showTime("");
	keff.push_back(1.2);
	for (int i = 0; i < keff.size(); i++)
	{
		cout << keff[i] <<"\t"<<Pi<< "\n";
	}
	cout << "N_mrt��ֵΪ" << N_mrt << "\n" << ncnum << "\n";
	//system("success.vbs");
	system("pause");
}