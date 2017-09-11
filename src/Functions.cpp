#include "stdio.h"
#include "math.h"
#include <string.h>
#include<stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
#include <iomanip>
#include "data.h"

int mplus(int a1, int b1)
{
	int a = a1;
	int b = b1;
	return(a + b);
}

void showTime(string tem)
{
	cout<<tem.c_str();
	for (int i = 0; i<68 - tem.size(); i++) cout << " ";
	printf("Time:%6.1fs\n", double(clock()) / 1000.00);
	//cout << "Time£º" << double(clock()) / 1000.00<<"s\n"<<endl;
};

double plege(int x, int y, int i)
{
	double plege;
	switch (x)
	{
	case(0):
		plege = 1.0;
	case(1):
		switch (y)
		{
		case(0) :
			plege = thl[i].cos;
		case(1) :
			plege = -thl[i]. sin;
		default:
			break;
		}
	case(2):
		switch (y)
		{
		case (0):
			plege = 1.5*thl[i]. cos*thl[i]. cos - 0.5;
		case (1):
			plege = -3.0*thl[i]. sin*thl[i]. cos;
		case (2) :
			plege = 3.0*thl[i]. sin*thl[i]. sin;
		default:
			break;
		}
	case(3):
		switch (y)
		{
		case(0) :
			plege = thl[i]. cos*(1.0 - 2.5*thl[i]. sin*thl[i]. sin);
		case (1) :
			plege = (7.5*thl[i]. sin*thl[i]. sin - 6.0)*thl[i]. sin;
		case (2) :
			plege = 15.0*thl[i]. sin*thl[i]. sin*thl[i]. cos;
		case (3) :
			plege = -15.0*thl[i]. sin*thl[i]. sin*thl[i]. sin;
		default:
			break;
		}
	default:
		break;
	}
	return plege;
}

long factorial(int n)
{
	long factor;
	factor = 1;
	for (int i = 1; i < n + 1; i++)
	{
		factor*=i;
	}
	return factor;
}