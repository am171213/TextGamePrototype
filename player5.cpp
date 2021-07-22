//Alexander Miller
//CSCI 330 9:30-10:45
//Program 5
//PlayerClass Implimentation

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <map>
#include <utility>
#include "player5.h"
#include "dice.h"
#include "gamespace.h"

using namespace std;
using namespace GameSpace;

enum Wounded {w = -1};
enum Killed {k = -2};

static const int STAT_AMT = 13; 		//Amount of statistics in PlayerStat array
static const int HEAL_AMT = 10;			//Amount To Heal Player For
static const int INIT_MOM = 0;			//Starting Momentum
static const int INIT_ROW = -1;			//Starting Position For Row
static const int INIT_COL = -1;			//Starting Position For Col	
static const int CRITWND_AMT = 10; 		//Amount Taken From Health During CriticalWound
static const int WILLPOWER_MAX = 12;	//Max Willpower

const int PlayerClass::IMP_TABLE[13][13] = 
	//				-	P	O	W	E	R	-
{	// 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12
	{  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1},	//0		|
	{  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1},	//1		D
	{  -1, -1,  0,  1,  2,  3,  4,  5,  6,  7,   8,   9,  10},	//2		I
	{  -1, -1,	1,  2,  3,  4,  5,  6,  7,  8,   9,  10,   w},	//3		C
	{  -1, -1,	2,  3,  4,  5,  6,  7,  8,  9,  10,   w,   w},	//4		E
	{  -1, -1,	3,  4,  5,  6,  7,  8,  9, 10,   w,   w,   w},	//5		|
	{  -1, -1,	4,  5,  6,  7,  8,  9, 10,  w,	 w,	  w,   w},	//6		R
	{  -1, -1,  5,  6,  7,  8,  9, 10,  w,  w,   w,   w,   w},	//7		O
	{  -1, -1,  6,  7,  8,  9, 10,  w,  w,  w,   w,   w,   w},	//8		L
	{  -1, -1,  7,  8,  9, 10,  w,  w,  w,  w,   w,   w,   w},	//9		L
	{  -1, -1,  8,  9, 10,  w,  w,  w,  w,  w,   w,   w,   w},	//10	|
	{  -1, -1,  9, 10,  w,  w,  w,  w,  w,  w,   w,   w,   w},	//11	|
	{  -1, -1, 10,  w,  w,  w,  w,  w,  w,  w,   w,   w,   w}	//12	|
};

const int PlayerClass::CRITWND_TABLE[13][13]=
	//				-W I L L P O W E R-
{  //  0|  1|  2|  3|  4|  5|  6|  7|  8|  9|  10|  11| 12 
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,  0},  //0 	|
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,  0}, //1	|
	{  0,  0,  k,  k,  k,  k,  k,  k,  k,  k,   k,   k, -1}, //2	|
	{  0,  0,  k,  k,  k,  k,  k,  k,  k,  k,   k,  -1, -1}, //3	D
	{  0,  0,  k,  k,  k,  k,  k,  k,  k,  k,  -1,  -1, -1}, //4	I
	{  0,  0,  k,  k,  k,  k,  k,  k,  k, -1,  -1,  -1, -1}, //5	C
	{  0,  0,  k,  k,  k,  k,  k,  k, -1, -1,  -1,  -1, -1}, //6 	E
	{  0,  0,  k,  k,  k,  k,  k, -1, -1, -1,  -1,  -1, -1}, //7	|	
	{  0,  0,  k,  k,  k,  k, -1, -1, -1, -1,  -1,  -1, -1}, //8	R
	{  0,  0,  k,  k,  k, -1, -1, -1, -1, -1,  -1,  -1, -1}, //9	O	
	{  0,  0,  k,  k, -1, -1, -1, -1, -1, -1,  -1,  -1, -1}, //10	L
	{  0,  0,  k, -1, -1, -1, -1, -1, -1, -1,  -1,  -1, -1}, //11	L
	{  0,  0, -1, -1, -1, -1, -1, -1, -1, -1,  -1,  -1, -1} //12	|
};

PlayerClass::~PlayerClass()
{	

}

PlayerClass& PlayerClass::operator= (const PlayerClass& p)
{
	if (this != &p) //Not self assigning
	{
		//Assign constant
		*(const_cast<const int **> (& STATS)) = p.STATS;
		*(const_cast<string*>(&NAME)) = p.NAME;
	
		//Copy stats Array to p.stats
		for (int i = 0; i < NUM_STATS; ++i)
			{stats[i] = p.stats[i];}
	}
	return *this;
}

PlayerClass::PlayerClass(string initPName, const int INIT_CONST_STATS[], const int INIT_VAR_STATS[]): 
						NAME(ValidateName(initPName)), STATS(NULL)	 
{	
	*const_cast<const int **> (& STATS) = INIT_CONST_STATS;
	for (int i = 0; i < NUM_STATS; ++i)
		{stats[i] = INIT_VAR_STATS[i];}
}

PlayerClass::PlayerClass():NAME("DEFAULT"), STATS(NULL)
{

}

string PlayerClass::Name() const
{
	return NAME;
}

string PlayerClass::ValidateName(string initPName) const
{	
	initPName = TrimStr(initPName);							//Trims String and reassigns it
	if (initPName.length() > MAX_NAME_SIZE)
	{
		initPName.erase(initPName.begin()+MAX_NAME_SIZE, initPName.end());
		initPName = TrimStr(initPName);	
	}
	if (Cmp(initPName, ""))									//If the string now is equal to an empty string
		throw GameSpace::INVALID_NAME;						//Set to default
	return initPName;
}

int PlayerClass::Row() const
{
	return stats[ROW];
}

int PlayerClass::Col() const
{
	return stats[COL];
}

GameSpace::DirType PlayerClass::Dir() const
{
	return DirType(stats[DIR]);
}
	
int PlayerClass::MaxHealth() const
{
	return STATS[MAX_HP];
}

int PlayerClass::Health()const
{
	return stats[HEALTH];
}

int PlayerClass::WillPower()const	
{
	return stats[WILLPOWER];
}

int PlayerClass::MaxSpeed()const
{
	return STATS[MAX_SPD];
}

int PlayerClass::CurrentSpeed()const
{
	return stats[SPEED];
}

int PlayerClass::Momentum() const
{
	return stats[MOMENTUM];
}

int PlayerClass::Power()const
{
	return stats[POWER];
}

int PlayerClass::RollPhysDam() const
{
	return RollDice(DAMAGE);	
}

int PlayerClass::Defense()const
{
	return stats[DEFENSE];
}

bool PlayerClass::IsAlive() const
{
	return(stats[HEALTH] > 0);
}

bool PlayerClass::IsDead() const
{
	return (stats[HEALTH] <= 0);	
}

bool PlayerClass::IsActive() const
{
	return (stats[ACTIVE]);
}

int PlayerClass::RollDice(RollType roll) const
{
	int diceRoll;
	if (roll == DAMAGE)
		{diceRoll = Dice::Roll(Name(),roll, STATS[PD_NUM_DIE], STATS[PD_FACES]);}
	else 
		{diceRoll = Dice::Roll(Name(),roll, 2, 6);}
	cout << Name() << " " << diceRoll << endl;
	return diceRoll;
}

int PlayerClass::Lookup_Impact() const
{
	int roll = RollDice(IMPACT);
	if (roll < 2 || roll > 12)						//If the roll is less than or above boundaries
			{throw GameSpace::INVALID_ROLL;}		//throw exception
	return IMP_TABLE[roll][Power()];
}

int PlayerClass::Lookup_Wound() const 
{
	int roll = RollDice(WOUND);
	if (roll < 2 || roll > 12)					//If roll out of bounds
		{throw GameSpace::INVALID_ROLL;}			//throw exception
	return CRITWND_TABLE[roll][WillPower()];
}

void PlayerClass::Write (ostream& out) const
{
	out << '#' << IsActive() << '#' << Name() << '#' << '(' << stats[ROW] << ',' << stats[COL] << ',';
	out << DIR_CHAR[stats[DIR]] << ")#" << STATS[MAX_HP] << '#' << stats[HEALTH] << '#' << stats[WILLPOWER] << '#';
	out << stats[POWER] << '#' << STATS[MAX_SPD] << '#' << stats[SPEED] << '#' << stats[MOMENTUM] << '#';
	out << STATS[PD_NUM_DIE] << 'd' << STATS[PD_FACES] << '#' << stats[DEFENSE] << endl;
}

bool PlayerClass::MakeActive()
{
	bool madeActive = true;
	if (IsDead())
	{
		madeActive = false;
		MakeInActive();
	}
	else
		stats[ACTIVE] = 1;
	return madeActive;
}

bool PlayerClass::MakeInActive()
{
	stats[ACTIVE] = 0;
	return (true);
}

bool PlayerClass::MakeDead()
{
	MakeInActive();
	stats[HEALTH] = DEAD_AMT;
	stats[WILLPOWER] = DEAD_AMT;
	stats[SPEED] = DEAD_AMT;
	stats[MOMENTUM] = DEAD_AMT;
	return true;
}

int PlayerClass::Wounded(int damage)
{
	if (IsActive() && damage > 0)			
	{														//If active and damage is greater than 0
		stats[HEALTH] = stats[HEALTH] - damage;	//damage is deducted from health
		if (stats[HEALTH] <= 0)						//if health is now less than 0
		{
			MakeDead();										//Kill player
			MakeInActive();									//No longer active
		}
	}
	return stats[HEALTH];
}

int PlayerClass::Invigorate(int vigor)
{
	if (IsActive()	&& vigor > 0)							
		stats[HEALTH] = vigor + stats[HEALTH];	
	if (STATS[MAX_HP] < stats[HEALTH])			//if the new health is greater than the max health
		{stats[HEALTH] = stats[HEALTH] - (stats[HEALTH] - STATS[MAX_HP]);} 
	return stats[HEALTH];	
}

bool PlayerClass::Heal()
{
	bool playerHealed = true;
	if(IsActive() && !IsDead())								//If player is active and not dead
	{	
		stats[HEALTH] = stats[HEALTH] + HEAL_AMT;//health + heal is new health
		if (STATS[MAX_HP] < stats[HEALTH])		//if the new health is greater than the max health
		{stats[HEALTH] = stats[HEALTH] - (stats[HEALTH] - STATS[MAX_HP]);} 
		stats[SPEED] = STATS[MAX_SPD];		//(health - max health) - health = new health
	}			
	else													//If player is inactive or dead
		playerHealed = false;								//return false
	return playerHealed;
}

int PlayerClass::SlowDown(int hazard)
{
	if (IsActive() && hazard > 0)
	{
		stats[SPEED] = stats[SPEED] - hazard;
		if (stats[SPEED] < 0)
		{
			stats[SPEED] = 0;
		}
	}
	if (stats[SPEED] < stats[MOMENTUM])
	{
		stats[MOMENTUM] = stats[SPEED];
	}
	return stats[SPEED];	
}

int PlayerClass::ResetCurrentSpeed()
{
	if (IsActive())
	{
		stats[SPEED] = STATS[MAX_SPD];
	}	
	return stats[SPEED];
}

int PlayerClass::ResetMomentum()
{	
	if (IsActive())
		stats[MOMENTUM] = stats[SPEED];
	return stats[MOMENTUM];
}

int PlayerClass::UseMomentum(int amount)
{
	if (IsActive() && amount > 0)
		stats[MOMENTUM] = stats[MOMENTUM] - amount;
	if (stats[MOMENTUM] < 0)
		stats[MOMENTUM] = 0;
	return stats[MOMENTUM];
}

bool PlayerClass::SetCell (int newRow, int newCol)
{
	bool cellsSet = true;
	if (newRow > GameSpace::NUMROWS || newCol > GameSpace::NUMCOLS)
	{cellsSet = false;}
	else if (newRow < -1 || newCol < -1)
	{cellsSet = false;}
	else if ((newRow == -1 && newCol != -1) || (newCol == -1 && newRow != -1))
	{cellsSet = false;}
	else 
	{
		stats[ROW] = newRow;
		stats[COL] = newCol;
	}
	return cellsSet;	
}

bool PlayerClass::SetDir(GameSpace::DirType newDir)
{
	bool directionSet = true;
	if (int(newDir) < 0)
		directionSet = false;
	else if (int(newDir) >= GameSpace::NUM_DIRTYPE)
		directionSet = false;
	else 
	{
		stats[DIR] = newDir;
		directionSet = true;
	}
	return directionSet;
}

int PlayerClass::Fortify(int boost)
{
	if (IsActive() && boost > 0)
		stats[DEFENSE] = boost + Defense();
	return stats[DEFENSE];
}

int PlayerClass::Expose(int decline)
{
	if (IsActive() && decline > 0)
		stats[DEFENSE] = Defense() - decline;
	if (stats[DEFENSE] < 0)
		stats[DEFENSE] = 0;
	return stats[DEFENSE];
}

int PlayerClass::WillPowerAdj(int adjustment)
{
	if (IsActive())
		stats[WILLPOWER] = WillPower() + adjustment;
	if (WillPower() > 12)
		stats[WILLPOWER] = 12;
	if (WillPower() < 0)
	{
		stats[WILLPOWER] = 0;
		MakeDead();
	}
	return stats[WILLPOWER];
}

int PlayerClass::HitScore() const
{
	int hitScore = 0;
	if (IsActive())
	{
		hitScore = RollDice(HITSCORE);
		if (hitScore > 12 || hitScore < 2)						//if roll isnt in boundaries
			throw GameSpace::INVALID_ROLL;						//throw exception
	}
	return hitScore;
}

int PlayerClass::HitDamage() const
{
	int hitDamage = 0;
	if (IsActive())
	{
		hitDamage = Power() +  RollPhysDam();				//hitDamage is power + RollPhysDam
	}
	return hitDamage;
}

int PlayerClass::Impact() const
{
	int imp = 0;

	if (IsActive())
	{imp = Lookup_Impact();}							  //search table
	return imp;
}

bool PlayerClass::CriticalWound()
{
	if (IsActive())
	{
		if (stats[HEALTH] - CRITWND_AMT <= 0 || WillPower() - 1 <= 0)
		{MakeDead();}	//If CRITWND_AMT will be too much or Willpower will = 0, kill player
		else 
		{
			if (WillPower() > WILLPOWER_MAX)						//If WillPower is too high
			{stats[WILLPOWER] = WILLPOWER_MAX;}				//Set back to max
			int roll = Lookup_Wound();
			if (roll == k)									//If table search is k
			{MakeDead();}											//kill player
			else if(roll == -1)								//If table search is -1
			{WillPowerAdj(roll);}							//Adjust willpower
		}
		Wounded(CRITWND_AMT);										//Adjust health
		SlowDown(stats[SPEED]/2+stats[SPEED]%2);//Adjust CurrentSpeed
	}
	return IsAlive();
}


//Overload equal bool operator 
bool PlayerClass::operator == (const PlayerClass& p) const	
	{return (Ucase(Name()) == Ucase(p.Name()));}
	
//OVerload not equal bool operator	
bool PlayerClass::operator != (const PlayerClass& p) const
	{return (Ucase(Name()) != Ucase(p.Name()));}

//Overload less than or equal to bool operator
bool PlayerClass::operator <= (const PlayerClass& p) const
	{return (Ucase(Name()) <= Ucase(p.Name()));}
	
//Overload greater than or equal to bool operator	
bool PlayerClass::operator >= (const PlayerClass& p) const
	{return (Ucase(Name()) >= Ucase(p.Name()));}
	
//Overload greater than bool operator	
bool PlayerClass::operator > (const PlayerClass& p) const
	{return (Ucase(Name()) > Ucase(p.Name()));}
	
//Overload less than bool operator	
bool PlayerClass::operator < (const PlayerClass& p) const
	{return (Ucase(Name()) < Ucase(p.Name()));}

ostream& operator<< (ostream& out, const PlayerClass* p)
{
	if (p)
		p->Write(out);
	return out;
}
