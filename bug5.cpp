//Alexander Miller
//CSCI 330 9:30-10:45
//Program 5
//Bug Implimentation

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <map>
#include <utility>
#include "player5.h"
#include "bug5.h"

using namespace std;

const int DEF_CONST_STATS[10]=
{0,0,0,0,0,0,0,0,0,0};
const int DEF_VAR_STATS[4] =
{0,0,0,0};

Bug::Bug (const string NAME, const int INIT_CONST_STATS[], const int INIT_VAR_STATS[]):
PlayerClass(NAME,INIT_CONST_STATS,INIT_VAR_STATS)
{
	
}

Bug::Bug(): PlayerClass("DEFAULT",DEF_CONST_STATS,DEF_VAR_STATS)
{
	
}

void Bug:: Write (ostream& out) const
{
	PlayerClass::Write(out);
}

Bug::~Bug ()
{
	
}
