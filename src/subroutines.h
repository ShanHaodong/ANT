#ifndef subroutines
#define subroutines
int mplus(int a, int b);

bool readMicData(MicLib);
void readInp();
bool checkData(MicLib tem);
void geometryPreprocess();
void staticCalculate();
void burnUp();
void selfShielding();
void showTime(string tem);
double plege(int x,int y,int i);
long factorial(int n);
#endif