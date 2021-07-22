//Alexander Miller
//CSCI 330 9:30-10:45
//Program 5
//KillerAnt Implimentation

#include <iostream>
#include "KillerAnt.h"
#include "bug5.h"

using namespace std;

const int KillerAnt::INIT_CONST_STATS[4] = {2,20,2,6};
const int KillerAnt::INIT_VAR_STATS[10] = {2,2,20,7,5,10,0,-1,-1,0};
const string KillerAnt::TYPE_STR = "KILLERANT";

KillerAnt::KillerAnt(string name): Bug(name, INIT_CONST_STATS, INIT_VAR_STATS)
{
	
}

KillerAnt::KillerAnt(): Bug("DEFAULT", INIT_CONST_STATS, INIT_VAR_STATS)
{
	
}

KillerAnt* KillerAnt::Clone() const
{
	return new KillerAnt (*this);
}

string KillerAnt::TypeStr() const
{
	return TYPE_STR;
}

void KillerAnt::Write(ostream& out) const
{
	out << TypeStr();
	Bug::Write(out);
}


bool KillerAnt::IsMyEnemy(const PlayerClass* p, bool beenHere) const
{
	bool isEnemy = false;
	if (p)
	{
		if (dynamic_cast<const KillerAnt*>(p))
		{
			isEnemy = false;
		}
		else
			isEnemy = true;
	}
	return isEnemy;
}

