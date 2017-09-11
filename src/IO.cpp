#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
#include "data.h"
#include "subroutines.h"


//*******以下为本文件定义或改动的全局变量*******//
//********只使用值的全局变量无需在此声明********//
//特征线相关参数
int N_mrt;                    //特征线选取参量，可选取的特征线方向个数为N_mrt-1
int Nm;                       //实际选取的特征线方向个数
int Nt;                       //极角求积组的个数
vector<int> m_fy;             //实际选取的特征线方向序列，其个数为Nm
vector<thelta> thl;           //极角高斯求积组
//几何定义相关参数                   
double l_asm;                  //六角形组件的对边距
double l_cell;                 //六角形栅元的对边距
double wid_clad;               //外套管厚度
//截面库相关参数              
int ncnum;                    //计算涉及核素数目       
int MG;                       //多群能群数目
int BG;                       //少群能群数目
vector<int> BroG;             //各少群包含多群数
int Nlege;                    //计算中的勒让德展开散射阶数（不大于输入微观截面中定义的最大阶数）
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
