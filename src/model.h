#ifndef model
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

struct GemModel
{

};
struct MocModel :GemModel
{

};
struct MatModel:GemModel
{

};
struct MacModel:MatModel
{

};
struct CalModel:MatModel
{

};
#endif // !model
