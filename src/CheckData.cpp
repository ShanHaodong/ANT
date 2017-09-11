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
		cout <<"*ERROR*:微观截面库中核素数目不足!";
		cout << "\n" << "--------需要核素数目：" << ncnum << "；\t实际含有核素数目：" << tem.ncnum << "\n\n";
		return false;
	}
}