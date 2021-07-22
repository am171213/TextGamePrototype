//Alexander Miller
//CSCI 330 9:30-10:45
//Program 4
//Warrior Implimentation

#include <iostream>
#include "Warrior.h"
#include "human5.h"

using namespace std;

const int Warrior::INIT_VAR_STATS[10] = {5,5,81,9,9,8,0,-1,-1,0};
const int Warrior::INIT_CONST_STATS[4] = {5,81,3,6};

const string Warrior::TYPE_STR = "WARRIOR";

Warrior::Warrior(string name): Human(name, INIT_CONST_STATS, INIT_VAR_STATS)
{
	
}

Warrior::Warrior(): Human("DEFAULT", INIT_CONST_STATS, INIT_VAR_STATS)
{

}

Warrior* Warrior::Clone() const
{
	return new Warrior (*this);
}

string Warrior::TypeStr() const
{
	return TYPE_STR;
}

void Warrior::Write(ostream& out) const
{
	out << TypeStr();
	Human::Write(out);
}

bool Warrior::IsMyEnemy(const PlayerClass* p, bool beenHere) const
{
	bool isEnemy = false;
	if (!p || p==this) return isEnemy;
	
	if (!beenHere)
	{
		beenHere= true;
		isEnemy = p->IsMyEnemy(this, beenHere);
	}
	const Human* myFriend = dynamic_cast<const Human*>(p);

	return (!myFriend || isEnemy);
}

