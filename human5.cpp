//Alexander Miller
//CSCI 330 9:30-10:45
//Program 5
//Human Implimentation

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <map>
#include <utility>
#include "player5.h"
#include "wpn.h"
#include "human5.h"

using namespace std;
const int DEF_CONST_STATS[10]=
{0,0,0,0,0,0,0,0,0,0};
const int DEF_VAR_STATS[4]=
{0,0,0,0};

Human::Human(const string NAME, const int INIT_CONST_STATS[], const int INIT_VAR_STATS[]): 
PlayerClass(NAME, INIT_CONST_STATS, INIT_VAR_STATS), PACK(new PackClass(CarryWeight())), currWpn(NULL), wpnSkill(0)
{

}

Human::Human(const Human& h): PlayerClass(h), PACK(new PackClass(*h.PACK)), currWpn(NULL) 
{
	pastSkills = h.pastSkills;
	wpnSkill = h.wpnSkill;
	if (currWpn)
	{
		delete currWpn;
		currWpn = NULL;
	}

	if (h.currWpn)
		currWpn = new Weapon(*(h.currWpn));
}

Human::Human(): PlayerClass("DEFAULT",DEF_CONST_STATS,DEF_VAR_STATS), currWpn(NULL), PACK(new PackClass(CarryWeight()))
{
	
}

Human& Human::operator=(const Human & h)
{
	if(this != &h)
	{
		if (currWpn)
			delete currWpn;
		if (h.currWpn)
			currWpn = new Weapon(*(h.currWpn));
		wpnSkill = h.wpnSkill;
		pastSkills = h.pastSkills;
		*PACK = *h.PACK;
		PlayerClass::operator = (h);
	}
}

Human::~Human()
{		
	delete PACK;
	delete currWpn;
}

void Human::Write (ostream& out) const
{
	//Dylan Whitehead assisted me with ordering of out statements
	PlayerClass::Write(out);
	if (HasWeapon() || !pastSkills.empty())
		out << '\t' << WeaponNameAndNum() << '#' ; 
	if (wpnSkill != 0)
		out << wpnSkill;	

	if (!pastSkills.empty())
	{
		PastSkillsType::const_iterator iter;
		for (iter = pastSkills.begin(); iter != pastSkills.end(); ++iter)
		{
			out << '#' << Ucase(iter->first) << '#' << iter->second;
		}
		out << endl;
	}
}

int Human::Impact() const
{
	int imp = 0;
	if (IsActive())
	{imp = Lookup_Impact();}							  //search table
	return imp;
}

int Human::Lookup_Impact() const
{
	int roll = RollDice(IMPACT);
	if (roll < 2 || roll > 12)						//If the roll is less than or above boundaries
		{throw GameSpace::INVALID_ROLL;}		//throw exceptions
		
	int impact;
	if (HasWeapon() && currWpn->IsRange())
		{impact = IMP_TABLE[roll][currWpn->Power()];}
	else 
		{impact =IMP_TABLE[roll][Power()];}
	return impact;
}

int Human::HitDamage() const
{

	int hitDamage = 0;
	if (IsActive())
	{
		if (HasWeapon())										//Has Weapon
			hitDamage = wpnSkill + currWpn->RollWeaponDamage(Name()); //hitDamage is wpnSkill + RollForWeaponDamage
		else										
			hitDamage = Power() +  RollPhysDam();				//hitDamage is power + RollPhysDam
	}
	return hitDamage;
}

int Human::CarryWeight()const
{
	return (MAX_WEIGHT_MULT * RollPhysDam());
}

string Human::WeaponName() const
{
	string wpnName = "";
	if (currWpn)
		wpnName = currWpn->Name();
	return wpnName;
}

string Human::WeaponNameAndNum() const
{
	string wpnNameNum = "";
	if (currWpn)
		wpnNameNum = currWpn->NameAndNum();
	return wpnNameNum;
}

int Human::WeaponSkill() const
{
	return wpnSkill;
}

bool Human::HasWeapon() const
{
	return (currWpn != NULL);
}

vector<string> Human::Pack() const
{
	return PACK->PackInventory();
}

bool Human::IsMyEnemy(const PlayerClass* p, bool beenHere) const
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

Weapon* Human::GrabWeapon (Weapon* newWpn)
{
	Weapon* prevWpn = NULL;
	if (newWpn)
	{	
		if (IsActive())
		{
			prevWpn = currWpn;
			currWpn = newWpn;													//current value is now new weapon value	
			if (prevWpn)
			{
				if (PACK->AddWeapon(prevWpn))
					prevWpn = NULL;
			}																//previous weapon value is now current value
			
			if (pastSkills.find(Ucase(WeaponName())) == pastSkills.end())
			{
				wpnSkill = INIT_SKILL;											//wpnSkill is set to starting skill
				pastSkills.insert(make_pair(Ucase(currWpn->Name()), INIT_SKILL));  //Insert new weapon into the map
			}
			
			else
			{
				wpnSkill = pastSkills[Ucase(newWpn->Name())]; 					//Else wpnSkill is set to pastSkill
			}
		}	
		else
		{
			prevWpn = newWpn;
		}	
	}
	else 							//If newWpn is NULL
		{throw GameSpace::INVALID_WPN;}	//throw exception
	return prevWpn;
}

Weapon* Human::DropWeapon()
{
	Weapon* droppedWpn = NULL;
	if (HasWeapon())
	{
		droppedWpn = currWpn;
		currWpn = NULL;
		wpnSkill = 0;
	}
	return droppedWpn;
}

bool Human::ImprovedSkill(int improvement)
{
	bool skillUpdate = false;
	if (IsActive() && HasWeapon() && improvement > 0)
	{
		skillUpdate = true;
		wpnSkill += improvement;
		pastSkills[Ucase(WeaponName())] += improvement;
	}	
	return skillUpdate;
}

Weapon* Human::ChangeWeapon (string wpnName)
{
	Weapon* prevWpn = NULL;
	Weapon* newWpn = NULL;
	if (IsActive())
	{
		if (Ucase(WeaponName()) != Ucase(wpnName))
		{
			if (PACK->InPack(Ucase(wpnName)))
			{	
				newWpn = PACK->RemoveWeapon(Ucase(wpnName));
				if (currWpn && !PACK->AddWeapon(currWpn))
				{
					prevWpn = currWpn;
				}
				currWpn = newWpn;
				wpnSkill = pastSkills[Ucase(wpnName)];
			}
		}
	}
	return prevWpn;
}