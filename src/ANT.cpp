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

//*******以下为本文件定义或改动的全局变量*******//
//********只使用值的全局变量无需在此声明********//
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
	printf("            你正在使用的是  %s  Ver %2.1f \n\n", Name, ver);
	printf("                          中国原子能科学研究院   单浩栋 \n\n");
	printf("               SHAN Haodong from CIAE (E-Mail:shanhaodong@126.com)\n\n");*/ 


	printf(" ******************************************************************************\n");
	printf(" *          AAA                   NN      NN               TTTTTTTTTTTT       *\n");
	printf(" *         AA AA                  NNNN    NN                    TT            *\n");
	printf(" *        AA   AA                 NN  NN  NN                    TT            *\n");
	printf(" *       AAAAAAAAA                NN   NN NN                    TT            *\n");
	printf(" *      AA       AA               NN    NNNN                    TT            *\n");
	printf(" *     AA         AA              NN      NN                    TT            *\n");
	printf(" ******************************************************************************\n\n");
	cout<<"            你正在使用的是 "<<Name<<"  Ver "<<ver<<" \n\n";
	printf("                          中国原子能科学研究院   单浩栋 \n\n");
	printf("               SHAN Haodong from CIAE (E-Mail:shanhaodong@126.com)\n\n");

	//system("hello.vbs");  //尝试多线程
	showTime("                       --------------准备运行--------------");
	begin_main = clock();
	//system("if exist ANT.exe (copy ANT.exe ANT0) ");
	showTime("                       -----------正在读取输入卡-----------");
	readInp();
	showTime("                       -----------输入卡读取完毕-----------");
	MicLib miclib=MicLib();
	if (!readMicData(miclib))
	{
		system("pause");
		return;
	}
	showTime("                       ------------检查输入参数------------");
	if (!checkData(miclib))
	{
		//system("error.vbs"); //尝试多线程
		system("pause");
		return;
	}
	showTime("                       ------------输入参数无误------------");
	showTime("");
	keff.push_back(1.2);
	for (int i = 0; i < keff.size(); i++)
	{
		cout << keff[i] <<"\t"<<Pi<< "\n";
	}
	cout << "N_mrt的值为" << N_mrt << "\n" << ncnum << "\n";
	//system("success.vbs");
	system("pause");
}