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
extern clock_t begin_main, end_main, begin_readIn, end_readIn;    //��¼��������ʱ��


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
struct mic_general   //ͨ�û������ؽ���������
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
		vector<vector<double> > scdat;                   // Ⱥɢ�������棨nscd��  
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
		//cout << "Time��" << double(clock()) / 1000.00 << "s\n" << endl;
	};
	string transfer(string line)  //���������е�R��Zʶ��ת��Ϊ����������-+�ŸĻ��ɿ�ʶ��ķ��ţ�����ת�����������
	{
		string transfer;
		transfer = line.substr(0, 74);
		while (transfer.find("R") != string::npos)  //��R��д����Ӧ��ֵ
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
		while (transfer.find("Z") != string::npos)   //��Z��д������0
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
		while (transfer.find("+") != string::npos)   //�������еġ�+���ĳɡ�E��
		{
			transfer = transfer.replace(transfer.find('+'), 1, "E");
		}
		while (transfer.find("-") != string::npos)   //�������еġ�-���ȸĳɡ�+����Ϊ����ѭ�����÷�Ϊ������
		{
			transfer = transfer.replace(transfer.find('-'), 1, "+");
		}
		while (transfer.find(" +") != string::npos)   //Ϊ������Ķ����Ž��д˲���
		{
			transfer = transfer.replace(transfer.find(" +"), 2, " -");
		}
		while (transfer.find("+") != string::npos)    //����-����Ϊ��E-��
		{
			transfer = transfer.replace(transfer.find('+'), 1, "E-");
		}
		return transfer;
	}

	struct micrs :mic_general     //AMPX��ʽ�µ�mic����
	{
		string nunam;                                  // ��������                              
		int nusym;                                     // ����CITATION���                      
		int nudat;                                     // ����������������������                
		int nsig0;                                     // ���׽������                          
		int ntemp;                                     // �¶ȸ���                              
		int nreac;                                     // ��Ӧ������                            
		int narea;                                     // ƽ�����ӽ��淴Ӧ���͸���              
		int nsrea;                                     // Ⱥɢ�䷴Ӧ���͸���                    
		vector<double> sig0;                           // ���׽���                              
		vector<double> temp;                           // �¶�                                  
		vector<int> reac;                              // ��Ӧ���ͱ��    
		vector<vector<double> > idcs;                  // ����ϡ�ͽ��棨nreac,MG��              
		vector<vector<vector<vector<double> > > > boda;// ����������ӣ�nreac,nsig0,ntemp,MG��                        
		vector<int>areac;                              // ƽ�����ӽ��淴Ӧ����(narea)           
		vector<vector<double> > acdat;                 // ƽ�����ӽ�������(narea,MG)            
		vector<int> sreac;                             // Ⱥɢ�䷴Ӧ���ͱ�ţ�nsrea��           
		vector<int> nlege;                             // Ⱥɢ��������õ½�����nsrea��         
		vector<vector<int> > nmagi;                    // Ⱥɢ����ָ�����nsrea,(nlege+1)��     
		vector<vector<int> > nscd;                     // Ⱥɢ�����Ԫ�ظ�����nsrea,(nlege+1)�� 

		struct scadat
		{
			vector<int> magic;                     // Ⱥɢ����֣�nmagi��                
			vector<int> manum;                     // �����ִ���ɢ�����������ɻ��־����� 
			vector<int> cdnum;                     // ɢ�����������Ϊmannum(:)���ܺͣ� 
			vector<double> scdat;                   // Ⱥɢ�������棨nscd��  
			string transfer(string line)  //���������е�R��Zʶ��ת��Ϊ����������-+�ŸĻ��ɿ�ʶ��ķ��ţ�����ת�����������
			{
				string transfer;
				transfer = line.substr(0, 74);
				while (transfer.find("R") != string::npos)  //��R��д����Ӧ��ֵ
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
				while (transfer.find("Z") != string::npos)   //��Z��д������0
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
				while (transfer.find("+") != string::npos)   //�������еġ�+���ĳɡ�E��
				{
					transfer = transfer.replace(transfer.find('+'), 1, "E");
				}
				while (transfer.find("-") != string::npos)   //�������еġ�-���ȸĳɡ�+����Ϊ����ѭ�����÷�Ϊ������
				{
					transfer = transfer.replace(transfer.find('-'), 1, "+");
				}
				while (transfer.find(" +") != string::npos)   //Ϊ������Ķ����Ž��д˲���
				{
					transfer = transfer.replace(transfer.find(" +"), 2, " -");
				}
				while (transfer.find("+") != string::npos)    //����-����Ϊ��E-��
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
				do  //�ҵ����ݿ�19$$λ��
				{
					count++;
				} while (line[count].find("19$$") == string::npos);
				count++;
				do  //�����������
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
				do  //�����ɢ������
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
			string toString()                      // ��ʾɢ������
			{

			}
		};

		vector<vector<scadat> > sca;                   // Ⱥɢ�����ݴ洢��nsrea,(nlege+1)��
		bool findPos(string tem)
		{
			return true;
		}
		string transfer(string line)  //���������е�R��Zʶ��ת��Ϊ����������-+�ŸĻ��ɿ�ʶ��ķ��ţ�����ת�����������
		{
			string transfer;
			transfer = line.substr(0, 74);
			while (transfer.find("R") != string::npos)  //��R��д����Ӧ��ֵ
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
			while (transfer.find("Z") != string::npos)   //��Z��д������0
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
			while (transfer.find("+") != string::npos)   //�������еġ�+���ĳɡ�E��
			{
				transfer = transfer.replace(transfer.find('+'), 1, "E");
			}
			while (transfer.find("-") != string::npos)   //�������еġ�-���ȸĳɡ�+����Ϊ����ѭ�����÷�Ϊ������
			{
				transfer = transfer.replace(transfer.find('-'), 1, "+");
			}
			while (transfer.find(" +") != string::npos)   //Ϊ������Ķ����Ž��д˲���
			{
				transfer = transfer.replace(transfer.find(" +"), 2, " -");
			}
			while (transfer.find("+") != string::npos)    //����-����Ϊ��E-��
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
			//��ȡ���ػ�����Ϣ
			nunam = line[0].substr(0, line[0].find("  "));
			istringstream record(line[2]);
			record >> nudat;
			//��ȡƽ�����ӽ���
			do  //�ҵ�ƽ�����ӽ������ݿ�14**λ��
			{
				count++;
			} while (line[count].find("14**") == string::npos);
			count++;
			do  //�����ݿ��е��������ݶ�����ʱ�洢��
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
			for (int i = 0; i < tem_vd.size()/(MG+1); i++)  //��ƽ�����ӽ��水��Ӧ���洢
			{
				areac.push_back(tem_vd[i*(MG+1)]);
				vector<double> tem_vd1;
				for (int j = 0; j < MG; j++)
				{
					tem_vd1.push_back(tem_vd[i*(MG+1) + j+1]);
				}
				acdat.push_back(tem_vd1);
			}

			//��ȡ����ɢ�����
			count++;
			do   //��ȡ16$$���ݿ����������ݣ���Ӧɢ�����������Ϣ
			{
				istringstream record(transfer(line[count]));
				while (record >> tem_i)
				{
					tem_vi.push_back(tem_i);
				}
				count = count + 1;
			} while (line[count].find("16T") == string::npos);
			for (int i = 0; i <tem_vi.size()/4; i++)  //��16$$���ݿ���ɢ�䷴Ӧ�������õ²����Լ����������洢����
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

	vector<micrs> mic;   //���ؽ��棨ncnum��
	vector<double> bon;   //��ϸ��Ⱥ�߽磨MG+1��
	int ncnum;
	MicLib() = default;
	bool readIn()   //��ȡ�����Inlib������
	{
		showTime("                       -----------��ʼ��ȡ�����-----------");
		ifstream input("D:\\Composer\\C++\\Inlib",ifstream::in); //������΢�����ݿ��ļ�
		if (input){
			showTime("Inlib�򿪳ɹ� ");
			//��Inlib�ļ������ڴ�
			string tem_str;
			int i = 0;
			int tem_i = 0; 
			do
			{
				line_lib.push_back(tem_str); 
			} while (getline(input, tem_str));
			showTime("Inlib��ȡ��� ");
			//��ȡ�������Ⱥ��
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
			//��ȡ�������Ⱥ�ֲ�
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
			/*cout << "��Ⱥ��" << bon.size() << "\n" << "��Ⱥ�ֲ�: " << endl;
			for (int i = 0; i < bon.size(); i++)
			{
				cout<<"��"<<i<<"����"<< bon[i] <<endl;
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
			//��ȡ�������������
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
			/*ofstream out1("lib_nucleus"); //������и���������
			for (int i = 0; i < tem_nunam.size(); i++)
			{
				out1 << tem_nunam[i] << endl;
				out1 << tem_nudat[i] << endl;
			}*/
			//�жϽ��������Ƿ���ȫ�����뿨ƥ�䣨��Ҫ���compare���������뿨��ȡ����ͳһ���ԣ���δ��ɣ�
			vector<int> tem_vi = compare();
			if (!tem_vi.empty())
			{
				cout << "\n";
				cout << "*ERROR*:΢�۽�����ļ�Inlibȱ�����º��أ�"<<endl;
				for (int i = 0; i < tem_vi.size(); i++)
				{
					cout << "        " <<tem_vi[i]<< endl;
				}
				return false;
			}
			//��ȡ������صĸ���������
			vector<string> tem_nd;
			i = 0;
			do
			{
				i++;
			} while (line_lib[i].find("7T")==string::npos);
			i++;
			//ofstream out1("test");
			cout << "      ��������		         ���ر��" << endl;
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

			ofstream out2("test3");  //��������ؽ�����Ϣ��test3�в鿴�������ã�
			for (int i = 0; i < mic.size(); i++)
			{
				out2 << "*******"<<mic[i].nunam<<"*********" << endl;
				//for (int j = 0; j < mic[i].areac.size(); j++)  //���ƽ�����ӽ�������
				//{
				//	out2 << "----" << mic[i].areac[j] << "-----" << endl;
				//	for (int m = 0; m < mic[i].acdat[j].size(); m++)
				//	{
				//		out2 << "   " << mic[i].acdat[j][m] << "   "<<endl;
				//	}
				//}
				for (int j = 0; j < mic[i].nlege.size(); j++)  //�������ɢ�����
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
			cout << "*ERROR*:û�з���΢�۽�����ļ�Inlib!\n";
			return false;
		}

		showTime("                       -----------������ȡ���-----------");
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
	//�ж������������Ƿ������뿨�������ƥ��
	//��������ݰ���tem_nunam��tem_nudat
	//���뿨���������δ����
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
		system("echo ����һ���������\n");
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