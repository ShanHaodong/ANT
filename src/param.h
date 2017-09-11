#ifndef param
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <vector>
using namespace std;
//常用常数
const double Pi = 3.14159;
const double NA = 6.022E23;
//特征线相关参数
 extern int N_mrt;                    //特征线选取参量，可选取的特征线方向个数为N_mrt-1
 extern int Nm;                       //实际选取的特征线方向个数
 extern int Nt;                       //极角求积组的个数
 extern vector<int> m_fy;             //实际选取的特征线方向序列，其个数为Nm
 struct thelta                        //极角高斯求积组自定义数据类型
 {
	 double sin;
	 double cos;
	 double w;
 };
 extern vector<thelta> thl;           //极角高斯求积组
 //几何定义相关参数                   
 extern double l_asm;                  //六角形组件的对边距
 extern double l_cell;                 //六角形栅元的对边距
 extern double wid_clad;               //外套管厚度
//截面库相关参数    
 extern int ncnum;                    //计算涉及核素数目
 extern int MG;                       //多群能群数目
 extern int BG;                       //少群能群数目
 extern vector<int> BroG;             //各少群包含多群数
 extern int Nlege;                    //计算中的勒让德展开散射阶数（不大于输入微观截面中定义的最大阶数）
//计算结果参数                       
extern vector<double> keff;           //有效增殖因子的记录序列
extern clock_t begin_main,end_main,begin_readIn,end_readIn;    //记录程序运行时间


#endif // !param                     
