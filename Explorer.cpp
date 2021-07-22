//Alexander Miller
//CSCI 330 9:30-10:45
//Program 5
//Explorer Implimentation

#include <iostream>
#include "Explorer.h"
#include "human5.h"

using namespace std;

const int Explorer::INIT_VAR_STATS[10] = {8,8,42,7,6,0,0,-1,-1,0};
const int Explorer::INIT_CONST_STATS[4] = {8,42,1,6};
const string Explorer::TYPE_STR = "EXPLORER";

Explorer::Explorer(string NAME): Human(NAME, INIT_CONST_STATS, INIT_VAR_STATS)
{

}

Explorer::Explorer(): Human("DEFAULT", INIT_CONST_STATS, INIT_VAR_STATS)
{

}

Explorer* Explorer::Clone() const
{
	return new Explorer (*this);
}

string Explorer::TypeStr() const
{
	return TYPE_STR;
}

void Explorer::Write(ostream& out) const
{
	out << TypeStr();
	Human::Write(out);
}


bool Explorer::IsMyEnemy(const PlayerClass* p, bool beenHere) const
{
	bool isEnemy = false;
	if (p)
	{
		if (dynamic_cast<const Human*>(p))
		{
			if (p->TypeStr() == "BARBARIAN")
				isEnemy = true;
			else
				isEnemy = false;
		}
		else
			isEnemy = true;
	}
	return isEnemy;
}

