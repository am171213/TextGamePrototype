//Alexander Miller
//CSCI 330 9:30-10:45
//Program 5
//Barbarian Implimentation

#include <iostream>
#include "Barbarian.h"
#include "human5.h"
#include "math.h"

using namespace std;

const int Barbarian::INIT_VAR_STATS[10] = {4,4,100,11,11,10,0,-1,-1,0};
const int Barbarian::INIT_CONST_STATS[4] = {4,100,4,6};

const string Barbarian::TYPE_STR = "BARBARIAN";

Barbarian::Barbarian(string name): Human(name, INIT_CONST_STATS, INIT_VAR_STATS)
{
	
}

Barbarian::Barbarian(): Human("DEFAULT", INIT_CONST_STATS, INIT_VAR_STATS)
{

}

Barbarian* Barbarian::Clone() const
{
	return new Barbarian (*this);
}

string Barbarian::TypeStr() const
{
	return TYPE_STR;
}

void Barbarian::Write(ostream& out) const
{
	out << TypeStr();
	Human::Write(out);
}

bool Barbarian::IsMyEnemy(const PlayerClass* p, bool beenHere) const
{
	return (p && p != this); 
}

bool Barbarian::Heal()
{
	bool playerHealed = true;
	if(IsActive() && !IsDead())
	{
		Invigorate(BARB_HEAL_AMT);
		ResetCurrentSpeed();
	}		
	else										
		playerHealed = false;
	return playerHealed;
}

int Barbarian::HitDamage() const
{
	int hitDamage = 0;
	
	if (IsActive())
	{
		hitDamage = (Human::HitDamage());
	}
	return (hitDamage*DamageMultiplier());
}

int Barbarian::DamageMultiplier() const
{
	return ((WillPower()%2) + (WillPower()/2));
}