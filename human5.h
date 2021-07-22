//Alexander Miller
//CSCI 330 9:30-10:45
//Program 5
//Human Header

#ifndef _HUMAN4H
#define _HUMAN4H
#include <iostream>
#include "player5.h"
#include "wpn.h" 
#include "pack.h"

class Human: public PlayerClass
{
	protected:
	//Narrative: Creates Human instance by sending information to PlayerClass.
	//PreCondition: Information sent in from child class is valid.
	//Post-Condition: Human Class created.
		Human (const string NAME, 
			const int INIT_CONST_STATS[], 
			const int INIT_VAR_STATS[]);
			
		Human (const Human& h);
		
		Human& operator= (const Human& h);
		
	//Narrative: Roll the Dice and use either the weapon power or player power to find Impact value
		int Lookup_Impact() const;
		
	public:
//DESTRUCTOR---------------------------------------------------------------------------
	//Narrative: Deallocates Human memory
		virtual ~Human();
//OBSERVERS----------------------------------------------------------------------------		
	//Narrative: Provides a pointer to current instance
		virtual Human* Clone() const = 0;
	//Narrative: Calls LookUp_Impact if the Player is active
		virtual int Impact() const;
	//Narrative: Return whether passed in player is enemy or not
		virtual bool IsMyEnemy (const PlayerClass* p, bool beenHere = false) const = 0;
	//Narrative: Returns Type
		virtual string TypeStr () const = 0;
	//Narrative: Outputs child class data.
		void Write (ostream& out) const; 
	//Narrative: The damage inflicted is returned, other wise 0 is returned. Damage is
	//calculated by using the Weapon Skill for the weapon or player’s power if no weapon; add the score
	//from the Damage Value of the weapon used or roll the Physical Damage of player if no weapon.
		virtual int HitDamage() const;
	//Narrative: Calculates the max size of the pack class
		int CarryWeight() const;	
	//Narrative: Return the name of the weapon. Return empty string if there is no weapon
	//Pre-condition: none
	//Post-condition: currWpn->Name() is returned
		string WeaponName() const;
	//Narrative: Return the name of the weapon name and serial number. Return empty string if there is no weapon.
	//Pre-condition: none 
	//Post-condition: currWpn->NameAndNum returned
		string WeaponNameAndNum() const;
	//Narrative: returns current weapons skill	
		int WeaponSkill() const;
	//Narrative: Returns whether the player has a current weapon or one in the pack
		bool HasWeapon() const;
	//Narrative: Returns the vector Pack
		vector<string> Pack() const;
//TRANSFORMERS-------------------------------------------------------------------------
	//Narrative: Updates weapon skill
		bool ImprovedSkill(int improvement);			
	////Narrative:An active human grabs a new weapon
	//Pre-condition: A pointer to a weapon is sent in to an active human player.
	//Post-condition: If player already has weapon, no changes. If player doesn’t have a weapon,
	//the weapon is attached to player. If the player has skill with the weapon the weapons skill 
	//replaces the current weapons skill, if not, the weaponSkill is set to 1. The current weapon is returned.
		Weapon* GrabWeapon (Weapon* weapon);
	//Narrative: An active player drops their weapon and leaves the player with no weapon. The method returns
	//the weapon dropped, or NULL if the player is not active or there was no weapon to drop. 
		Weapon* DropWeapon ();
	//Narrative: Change currWpn to Weapon with passed in name. Return prevWpn.
		Weapon* ChangeWeapon(string wpnName);

	private:
	//Narrative: Default values assigned
		Human();						
		static const int INIT_SKILL = 1;	//Starting WeaponSkill
		static const int MAX_WEIGHT_MULT = 10;
		Weapon* currWpn;
		int wpnSkill;
		PackClass *const PACK;
		typedef map<string, int> PastSkillsType;
		PastSkillsType pastSkills;			//Map For Weapon Skills
		
};

#endif