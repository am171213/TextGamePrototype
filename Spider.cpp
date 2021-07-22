//Alexander Miller
//CSCI 330 9:30-10:45
//Program 4
//Spider Implimentation

#include <iostream>
#include "Spider.h"
#include "bug5.h"

using namespace std;

const int Spider::INIT_CONST_STATS[4] = {15,50,2,6};
const int Spider::INIT_VAR_STATS[10] = {15,15,50,8,11,7,0,-1,-1,0};
const string Spider::TYPE_STR = "SPIDER";

Spider::Spider(string name): Bug(name, INIT_CONST_STATS, INIT_VAR_STATS)
{
}

Spider::Spider(): Bug("DEFAULT", INIT_CONST_STATS, INIT_VAR_STATS)
{
}

Spider* Spider::Clone() const
{
	return new Spider (*this);
}

string Spider::TypeStr() const
{
	return TYPE_STR;
}

void Spider::Write(ostream& out) const
{
	out << TypeStr();
	Bug::Write(out);
}

bool Spider::IsMyEnemy(const PlayerClass* p, bool beenHere) const
{
	bool isEnemy = false;
	if (p)
	{
		if (dynamic_cast<const Spider*>(p))
		{
			isEnemy = false;
		}
		else
			isEnemy = true;
	}
	return isEnemy;
}

