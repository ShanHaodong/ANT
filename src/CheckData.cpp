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

bool checkData(MicLib tem)
{
	if (tem.ncnum != ncnum)
	{
		cout << "\n";
		cout <<"*ERROR*:΢�۽�����к�����Ŀ����!";
		cout << "\n" << "--------��Ҫ������Ŀ��" << ncnum << "��\tʵ�ʺ��к�����Ŀ��" << tem.ncnum << "\n\n";
		return false;
	}
}