//Alexander Miller
//CSCI 330 9:30-10:45
//Program 5
//Hornet Implimentation

#include <iostream>
#include "Hornet.h"
#include "bug5.h"

using namespace std;

const int Hornet::INIT_CONST_STATS[4] = {8,60,3,6};
const int Hornet::INIT_VAR_STATS[10] = {8,8,60,9,10,8,0,-1,-1,0};
const string Hornet::TYPE_STR = "HORNET";

Hornet::Hornet(string name): Bug(name, INIT_CONST_STATS, INIT_VAR_STATS)
{
	
}

Hornet::Hornet(): Bug("DEFAULT", INIT_CONST_STATS, INIT_VAR_STATS)
{

}

Hornet* Hornet::Clone() const
{
	return new Hornet (*this);
}

string Hornet::TypeStr() const
{
	return TYPE_STR;
}

void Hornet::Write(ostream& out) const
{
	out << TypeStr();
	Bug::Write(out);
}

bool Hornet::IsMyEnemy(const PlayerClass* p, bool beenHere) const
{
	bool isEnemy = false;
	if (p)
	{
		if (dynamic_cast<const Hornet*>(p))
		{
			isEnemy = false;
		}
		else
			isEnemy = true;
	}
	return isEnemy;
}

