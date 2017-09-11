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
extern clock_t begin_main, end_main, begin_readIn, end_readIn;    //记录程序运行时间


#endif // !param                     

#ifndef CrsData
#define CrsData
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
struct mic_general   //通用基本核素截面数据类
{
	string nunam;
	int nudat;
	int ntemp;
	vector<double> temp;
	int nreac;
	vector<int>reac;
	int nsrea;
	vector<int> sreac;
	vector<int> nlege;

	struct scadat
	{
		vector<vector<double> > scdat;                   // 群散射矩阵截面（nscd）  
	};
	struct crdata
	{
		vector<vector<double>  > reacdata;
		vector<vector<scadat> > sca;
	};

	vector<crdata> data;
	mic_general()
	{
		nunam = "";
		nudat = 0;
		ntemp = 0;


	}
};
class MicLib
{
public:
	void showTime(string tem)
	{
		cout << tem.c_str();
		for (int i = 0; i<68 - tem.size(); i++) cout << " ";
		printf("Time:%6.1fs\n",double(clock()) / 1000.00);
		//cout << "Time：" << double(clock()) / 1000.00 << "s\n" << endl;
	};
	string transfer(string line)  //将数据行中的R与Z识别并转换为浮点数，将-+号改换成可识别的符号，返回转换后的数据行
	{
		string transfer;
		transfer = line.substr(0, 74);
		while (transfer.find("R") != string::npos)  //将R改写成相应数值
		{
			string tem = transfer.substr(0, transfer.find('R'));

			tem = tem.substr(tem.rfind(' '));
			int n = tem.size();
			int m = stoi(tem);
			double x = stod(transfer.substr(transfer.find('R') + 1));
			ostringstream convert;
			convert << x;
			string rep;
			for (int i = 0; i < m - 1; i++)
			{
				rep = rep + convert.str() + "  ";
			}
			transfer = transfer.replace(transfer.find('R') + 1 - n, n, rep);
		}
		while (transfer.find("Z") != string::npos)   //将Z改写成若干0
		{
			string tem = transfer.substr(0, transfer.find('Z'));

			tem = tem.substr(tem.rfind(' '));
			int n = tem.size();
			int m = stoi(tem);
			string rep;
			for (int i = 0; i < m; i++)
			{
				rep = rep + " 0 ";
			}
			transfer = transfer.replace(transfer.find('Z') + 1 - n, n, rep);
		}
		while (transfer.find("+") != string::npos)   //将该行中的“+”改成“E”
		{
			transfer = transfer.replace(transfer.find('+'), 1, "E");
		}
		while (transfer.find("-") != string::npos)   //将改行中的“-”先改成“+”（为避免循环调用分为两步）
		{
			transfer = transfer.replace(transfer.find('-'), 1, "+");
		}
		while (transfer.find(" +") != string::npos)   //为避免误改动负号进行此操作
		{
			transfer = transfer.replace(transfer.find(" +"), 2, " -");
		}
		while (transfer.find("+") != string::npos)    //将‘-’改为“E-”
		{
			transfer = transfer.replace(transfer.find('+'), 1, "E-");
		}
		return transfer;
	}

	struct micrs :mic_general     //AMPX格式下的mic子类
	{
		string nunam;                                  // 核素名称                              
		int nusym;                                     // 核素CITATION编号                      
		int nudat;                                     // 核素质子数与质量数描述                
		int nsig0;                                     // 本底截面个数                          
		int ntemp;                                     // 温度个数                              
		int nreac;                                     // 反应道个数                            
		int narea;                                     // 平均中子截面反应类型个数              
		int nsrea;                                     // 群散射反应类型个数                    
		vector<double> sig0;                           // 本底截面                              
		vector<double> temp;                           // 温度                                  
		vector<int> reac;                              // 反应类型编号    
		vector<vector<double> > idcs;                  // 无限稀释截面（nreac,MG）              
		vector<vector<vector<vector<double> > > > boda;// 邦达连柯因子（nreac,nsig0,ntemp,MG）                        
		vector<int>areac;                              // 平均中子截面反应类型(narea)           
		vector<vector<double> > acdat;                 // 平均中子截面数据(narea,MG)            
		vector<int> sreac;                             // 群散射反应类型编号（nsrea）           
		vector<int> nlege;                             // 群散射矩阵勒让德阶数（nsrea）         
		vector<vector<int> > nmagi;                    // 群散射幻字个数（nsrea,(nlege+1)）     
		vector<vector<int> > nscd;                     // 群散射矩阵元素个数（nsrea,(nlege+1)） 

		struct scadat
		{
			vector<int> magic;                     // 群散射幻字（nmagi）                
			vector<int> manum;                     // 各幻字代表散射类型数（由幻字决定） 
			vector<int> cdnum;                     // 散射截面总数（为mannum(:)的总和） 
			vector<double> scdat;                   // 群散射矩阵截面（nscd）  
			string transfer(string line)  //将数据行中的R与Z识别并转换为浮点数，将-+号改换成可识别的符号，返回转换后的数据行
			{
				string transfer;
				transfer = line.substr(0, 74);
				while (transfer.find("R") != string::npos)  //将R改写成相应数值
				{
					string tem = transfer.substr(0, transfer.find('R'));

					tem = tem.substr(tem.rfind(' '));
					int n = tem.size();
					int m = stoi(tem);
					double x = stod(transfer.substr(transfer.find('R') + 1));
					ostringstream convert;
					convert << x;
					string rep;
					for (int i = 0; i < m - 1; i++)
					{
						rep = rep + convert.str() + "  ";
					}
					transfer = transfer.replace(transfer.find('R') + 1 - n, n, rep);
				}
				while (transfer.find("Z") != string::npos)   //将Z改写成若干0
				{
					string tem = transfer.substr(0, transfer.find('Z'));

					tem = tem.substr(tem.rfind(' '));
					int n = tem.size();
					int m = stoi(tem);
					string rep;
					for (int i = 0; i < m; i++)
					{
						rep = rep + " 0 ";
					}
					transfer = transfer.replace(transfer.find('Z') + 1 - n, n, rep);
				}
				while (transfer.find("+") != string::npos)   //将该行中的“+”改成“E”
				{
					transfer = transfer.replace(transfer.find('+'), 1, "E");
				}
				while (transfer.find("-") != string::npos)   //将改行中的“-”先改成“+”（为避免循环调用分为两步）
				{
					transfer = transfer.replace(transfer.find('-'), 1, "+");
				}
				while (transfer.find(" +") != string::npos)   //为避免误改动负号进行此操作
				{
					transfer = transfer.replace(transfer.find(" +"), 2, " -");
				}
				while (transfer.find("+") != string::npos)    //将‘-’改为“E-”
				{
					transfer = transfer.replace(transfer.find('+'), 1, "E-");
				}
				return transfer;
			}

			void readIn(vector<string> line)
			{
				int count = 0;
				int tem_i;
				double tem_d;
				do  //找到数据块19$$位置
				{
					count++;
				} while (line[count].find("19$$") == string::npos);
				count++;
				do  //读入幻字数据
				{
					istringstream record(transfer(line[count]));
					while (record >> tem_i)
					{
						magic.push_back(tem_i);
					}
					count++;
				} while (line[count].find("20**") == string::npos);
				count++;		
				//ofstream out4("test4");
				do  //读入各散射数据
				{
					istringstream record(transfer(line[count]));
					//out4 << line[count] << endl;
					while (record >> tem_d)
					{
						scdat.push_back(tem_d);
					}
					count++;
				} while (line[count].find("20T") == string::npos);
			}
			string toString()                      // 显示散射数据
			{

			}
		};

		vector<vector<scadat> > sca;                   // 群散射数据存储（nsrea,(nlege+1)）
		bool findPos(string tem)
		{
			return true;
		}
		string transfer(string line)  //将数据行中的R与Z识别并转换为浮点数，将-+号改换成可识别的符号，返回转换后的数据行
		{
			string transfer;
			transfer = line.substr(0, 74);
			while (transfer.find("R") != string::npos)  //将R改写成相应数值
			{
				string tem = transfer.substr(0, transfer.find('R'));

				tem = tem.substr(tem.rfind(' '));
				int n = tem.size();
				int m = stoi(tem);
				double x = stod(transfer.substr(transfer.find('R') + 1));
				ostringstream convert;
				convert << x;
				string rep;
				for (int i = 0; i < m - 1; i++)
				{
					rep = rep + convert.str() + "  ";
				}
				transfer = transfer.replace(transfer.find('R') + 1 - n, n, rep);
			}
			while (transfer.find("Z") != string::npos)   //将Z改写成若干0
			{
				string tem = transfer.substr(0, transfer.find('Z'));

				tem = tem.substr(tem.rfind(' '));
				int n = tem.size();
				int m = stoi(tem);
				string rep;
				for (int i = 0; i < m; i++)
				{
					rep = rep + " 0 ";
				}
				transfer = transfer.replace(transfer.find('Z') + 1 - n, n, rep);
			}
			while (transfer.find("+") != string::npos)   //将该行中的“+”改成“E”
			{
				transfer = transfer.replace(transfer.find('+'), 1, "E");
			}
			while (transfer.find("-") != string::npos)   //将改行中的“-”先改成“+”（为避免循环调用分为两步）
			{
				transfer = transfer.replace(transfer.find('-'), 1, "+");
			}
			while (transfer.find(" +") != string::npos)   //为避免误改动负号进行此操作
			{
				transfer = transfer.replace(transfer.find(" +"), 2, " -");
			}
			while (transfer.find("+") != string::npos)    //将‘-’改为“E-”
			{
				transfer = transfer.replace(transfer.find('+'), 1, "E-");
			}
			return transfer;
		}
		void readIn(vector<string> line)
		{
			vector<string> tem_str;
			vector<string> tem_str1;
			int tem_i;
			vector<int> tem_vi;
			double tem_d;
			vector<double> tem_vd;
			int count = 0;
			//读取核素基本信息
			nunam = line[0].substr(0, line[0].find("  "));
			istringstream record(line[2]);
			record >> nudat;
			//读取平均中子截面
			do  //找到平均中子截面数据块14**位置
			{
				count++;
			} while (line[count].find("14**") == string::npos);
			count++;
			do  //将数据块中的所有数据读入临时存储中
			{
				istringstream record(transfer(line[count]));
				while (record >> tem_d)
				{
					tem_vd.push_back(tem_d);
				}
				count++;
			} while (line[count].find("16$$") == string::npos);
			MG = 171;
			//cout << MG << endl;
			for (int i = 0; i < tem_vd.size()/(MG+1); i++)  //将平均中子截面按反应道存储
			{
				areac.push_back(tem_vd[i*(MG+1)]);
				vector<double> tem_vd1;
				for (int j = 0; j < MG; j++)
				{
					tem_vd1.push_back(tem_vd[i*(MG+1) + j+1]);
				}
				acdat.push_back(tem_vd1);
			}

			//读取中子散射截面
			count++;
			do   //读取16$$数据块中所有数据，对应散射基本参数信息
			{
				istringstream record(transfer(line[count]));
				while (record >> tem_i)
				{
					tem_vi.push_back(tem_i);
				}
				count = count + 1;
			} while (line[count].find("16T") == string::npos);
			for (int i = 0; i <tem_vi.size()/4; i++)  //将16$$数据块中散射反应道、勒让德参数以及幻数个数存储下来
			{
				sreac.push_back(tem_vi[i]);
				nlege.push_back(tem_vi[2*tem_vi.size()/ 4 + i]);
				vector<int> tem_vi2;
				for (int j = 0; j < nlege[i]+1; j++)
				{
					tem_vi2.push_back(tem_vi[tem_vi.size()/ 4 + i]);
				}
				nscd.push_back(tem_vi2);
			}

			count++;
			/*ofstream output("test1");*/
			vector<scadat> scatem;
			vector<vector<string> > tem_vvr;
			for (count; count < line.size(); count++)
			{
				tem_str.clear();
				scatem.clear();
				do
				{
					tem_str.push_back(line[count]);
					count++;
				} while (line[count - 1].find("20T") == string::npos&&count<line.size());
				count--;
				/*output << "*********************" << endl;
				for (int j = 0; j < tem_str.size(); j++)
				output << tem_str[j] << endl;*/
				tem_vvr.push_back(tem_str);
			}
			count = 0;
			for (int i = 0; i < sreac.size(); i++)
			{
				scatem.clear();
				for (int j = 0; j < nlege[i]+1; j++)
				{
					scadat tem;
					tem.readIn(tem_vvr[count]);
					count++;
					scatem.push_back(tem);
				}
				sca.push_back(scatem);
			}
			//ofstream out4("test4");
			//out4 << "**********" << endl;
			//for (int i = 0; i < sca.size();i++)
			//{
			//	out4 << sca[i].size() << endl;
			//	/*for (int j = 0; j < sca[i].size(); j++)
			//	{
			//		out4 << sca[i][j].scdat.size()<<sca[i][j].magic.size()<<endl;
			//	}*/
			//}
			/*scadat tem = scadat();
			tem.readIn(tem_str);
			scatem.push_back(tem);
			sca.push_back(scatem);*/
		}
		string toString()
		{

		}
	private:
	};

	vector<micrs> mic;   //核素截面（ncnum）
	vector<double> bon;   //精细能群边界（MG+1）
	int ncnum;
	MicLib() = default;
	bool readIn()   //读取输入库Inlib内数据
	{
		showTime("                       -----------开始读取截面库-----------");
		ifstream input("D:\\Composer\\C++\\Inlib",ifstream::in); //打开输入微观数据库文件
		if (input){
			showTime("Inlib打开成功 ");
			//将Inlib文件读入内存
			string tem_str;
			int i = 0;
			int tem_i = 0; 
			do
			{
				line_lib.push_back(tem_str); 
			} while (getline(input, tem_str));
			showTime("Inlib读取完毕 ");
			//读取截面库能群数
			i = 0;
			while (line_lib[i].find("2$$") == string::npos)
			{
				i++;
			}
			tem_str = transfer(line_lib[i+1]);
			istringstream record(tem_str);
			record >> tem_i;
			record >> tem_i;
			record >> MG;
			//读取截面库能群分布
			i = 0;
			while (line_lib[i].find("7**") == string::npos)
			{
				i++;
			}
			double tem_db;
			i++;
			do
			{
				istringstream record(transfer(line_lib[i]));
				while (record >> tem_db)
				{
					bon.push_back(tem_db);
				}
				i = i + 1;
			} while (line_lib[i].find("7T")==string::npos);
			/*cout << "能群数" << bon.size() << "\n" << "能群分布: " << endl;
			for (int i = 0; i < bon.size(); i++)
			{
				cout<<"第"<<i<<"个："<< bon[i] <<endl;
			}*/
			//for (int i = 0; i < line_lib.size(); i++)
			//{
			//	istringstream record(line_lib[i]);
			/*	if (line_lib[i].size() == 80)
				{
					cout << line_lib[i];
				}
				cout <<line_lib[i]<<endl;*/
			//}
			//读取截面库所含核素
			i = 0;
			while (line_lib[i].find("7**") == string::npos)
			{
				while (line_lib[i].find("3$$") == string::npos)
				{
					i++; 
					if (line_lib[i].find("7**") != string::npos)
						break;
				}
				if (line_lib[i].find("7**") != string::npos)
					break;
				tem_nunam.push_back(line_lib[i-1].substr(0,line_lib[i-1].find("  ")));
				istringstream record(line_lib[i+1]);
				record >> tem_i;
				tem_nudat.push_back(tem_i);
				i++;
			}
			/*ofstream out1("lib_nucleus"); //输出库中各核素名称
			for (int i = 0; i < tem_nunam.size(); i++)
			{
				out1 << tem_nunam[i] << endl;
				out1 << tem_nudat[i] << endl;
			}*/
			//判断截面库核素是否完全与输入卡匹配（需要结合compare函数与输入卡读取部分统一调试，尚未完成）
			vector<int> tem_vi = compare();
			if (!tem_vi.empty())
			{
				cout << "\n";
				cout << "*ERROR*:微观截面库文件Inlib缺少以下核素："<<endl;
				for (int i = 0; i < tem_vi.size(); i++)
				{
					cout << "        " <<tem_vi[i]<< endl;
				}
				return false;
			}
			//读取所需核素的各项截面参数
			vector<string> tem_nd;
			i = 0;
			do
			{
				i++;
			} while (line_lib[i].find("7T")==string::npos);
			i++;
			//ofstream out1("test");
			cout << "      核素名称		         核素标号" << endl;
			int count = 0;
			for (int j=i; j < line_lib.size(); j++)
			{
				micrs tem_mic = micrs();
				tem_nd.clear();
				do
				{
					tem_nd.push_back(line_lib[j]);
					/*out1 << line_lib[j]<<endl;*/
					j++;
				} while (line_lib[j+1].find("3$$") == string::npos && j<line_lib.size());
				j--;
				tem_mic.readIn(tem_nd);
				mic.push_back(tem_mic);
				count++;
				printf(" %3i  %-24s   %8i\n", count, tem_mic.nunam.c_str(), tem_mic.nudat);
				/*out1 << "*******" << tem_mic.nunam << "*********" << endl;
				for (int m = 0; m < tem_mic.nlege.size(); m++)
				{
					out1 << tem_mic.sreac[m]<<"   "<<tem_mic.sca[m].size() << endl;
				}*/
				//cout<<"	"<<tem_mic.nunam<<"		"<<tem_mic.nudat<<endl;
			}
			ncnum = mic.size();

			ofstream out2("test3");  //输出各核素截面信息到test3中查看（调试用）
			for (int i = 0; i < mic.size(); i++)
			{
				out2 << "*******"<<mic[i].nunam<<"*********" << endl;
				//for (int j = 0; j < mic[i].areac.size(); j++)  //输出平均中子截面数据
				//{
				//	out2 << "----" << mic[i].areac[j] << "-----" << endl;
				//	for (int m = 0; m < mic[i].acdat[j].size(); m++)
				//	{
				//		out2 << "   " << mic[i].acdat[j][m] << "   "<<endl;
				//	}
				//}
				for (int j = 0; j < mic[i].nlege.size(); j++)  //输出中子散射截面
				{
					/*out2 << mic[i].sreac[j] << "  ";
					out2 << mic[i].nlege[j] << "  ";
					out2 << mic[i].nscd[j][0] << endl;*/
					out2 << mic[i].sca[j].size() << endl;
				}
			}
		}
		else{
			cout << "\n";
			cout << "*ERROR*:没有发现微观截面库文件Inlib!\n";
			return false;
		}

		showTime("                       -----------截面库读取完毕-----------");
		return true;
	};
	int sizeOf()
	{
		return mic.size() + 1;
	};
	string toString()
	{

	};
	vector<int> compare()   
	//判断输入截面库中是否与输入卡定义核素匹配
	//截面库数据包括tem_nunam与tem_nudat
	//输入卡定义核素尚未定义
	{
		vector<int> lack;
		return lack;
	}
private:
	vector<string> line_lib;
	vector<string> tem_nunam;
	vector<int> tem_nudat;
};
class MacLib
{
public:
	struct Mac{
		int x;
		int y;
		int z;
		int Nuc_num;
		int Volume;
		vector<string> Nuc_name;
	};
	MacLib()
	{

	}
	void print()
	{
		system("echo 这是一个输出程序。\n");
	}
	void prepare()
	{

	}
	void output()
	{

	}
private:
	int i;
	int y;
	int z;
};

class StoreData
{

}; 
#endif