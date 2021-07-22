//Alexander Miller
//CSCI 330 9:30-10:45
//Program 5
//Barbarian Header

#ifndef _BARBARIANH
#define _BARBARIANHH
#include <iostream>
#include "human5.h"

class Barbarian: public Human
{	
	public:
	//"BARBARIAN"
		static const string TYPE_STR;
		
	//Narrative: Calls Parent parameterized constructors with class stats.
	//PreCon: Name sent in
	//PostCon: Human constructor called.
		Barbarian (string name);
	//Narrative: Provides a pointer to current instance
		Barbarian* Clone() const;
		
	//Narrative: Returns Type as a string.
		string TypeStr() const;
	//Narrative: Output TypeStr and call parents Write.
		void Write (ostream& out) const;
	//Narrative: Return whether passed in player is enemy or not
		bool IsMyEnemy(const PlayerClass* p, bool beenHere = false) const;
	//Narrative: Damage is calculated by DiceRoll and multiplied by DamageMultiplier
		int HitDamage() const;
	//Narrative: Returns the Willpower divided by 2, rounded up
		int DamageMultiplier() const;
	//Narrative: Heals the player health by 5 and resets currentspeed
		bool Heal();

	private:
	//Narrative: Default values assigned
		Barbarian();
	//Amount To Heal Player For	
		static const int BARB_HEAL_AMT = 5;		
	//Initial Constant Stats
		static const int INIT_CONST_STATS[4];
	//Initial Dynamic Stats
		static const int INIT_VAR_STATS[10];
};
#endif