//Alexander Miller
//CSCI 330 9:30-10:45
//Program 4
//PlayerClass Header

#ifndef _PLAYERH
#define _PLAYERH
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <map>
#include "gamespace.h"
#include "dice.h"

using namespace std;

//Player Class
class PlayerClass
{
	protected:
		//Narrative: Set instance attributes to the appropriate values for the PlayerType.
		//Pre-condition: None
		//Post-condition: New Player class created with given name.
		PlayerClass(const string NAME,
					const int INIT_CONST_STATS[],
					const int INIT_VAR_STATS[]);
		
		//Narrative:Rolls the dice.
		//Pre-condition: Type of roll is sent in.
		//Post-condition: Dice roll value is returned.
		int RollDice(GameSpace::RollType) const;
		
		//Narrative: Returns specific value in the Impact Table
		//Pre-condition: None
		//Post-condition: Number in table returned. 
		virtual int Lookup_Impact() const;
		
		//Narrative: Returns specific value in the CriticalWound Table
		//Pre-condition: None
		//Post-condition: Number in table returned. 
		int Lookup_Wound() const;
		
		static const int IMP_TABLE[13][13];
		static const int CRITWND_TABLE[13][13];	
	public: 
		virtual string TypeStr() const = 0;
	
		//Narrative: If p is not equal to this PlayerClass, copy all variables from p to this.
		//Pre-condition: Another player class is sent in
		//Post-condition: p = this PlayerClass
		PlayerClass& operator= (const PlayerClass& p);
		
		//Narrative: none
		//Pre-condition: none
		//Post-condition: none
		virtual ~PlayerClass();
		
		virtual PlayerClass* Clone() const = 0;
		
	//GETTERS
		//Narrative: Return the player’s name
		//Pre-condition: PlayerClass name is set and Name() is called.
		//Post-condition: Player name is returned.
		string Name() const;
		
		//Narrative: Return the player’s cell row.
		//Pre-condition: Row has a value already.
		//Post-condition: Row has been returned.
		int Row() const;
		
		//Narrative: Return the player’s cell column.
		//Pre-condition: Column has a value already.
		//Post-condition: Column has been returned.
		int Col() const;
		
		//Narrative: Return the direction the player is facing. 
		//Pre-condition: Direction has a value already.
		//Post-condition: Direction has been returned.
		GameSpace::DirType Dir() const;
		
		//Narrative: Return the players max health 
		//Pre-condition: Max Health has a value already.
		//Post-condition: Max Health has been returned.
		int MaxHealth() const;
		
		//Narrative: Return the players health. 
		//Pre-condition: Health has a value already.
		//Post-condition: Health has been returned.
		int Health()const;
		
		//Narrative: Return the players willpower. 
		//Pre-condition: Willpower has a value already.
		//Post-condition: Willpower has been returned.
		int WillPower()const;
		
		//Narrative: Return the players maximum speed. 
		//Pre-condition: Max Speed has a value already.
		//Post-condition: Max Speed has been returned.
		int MaxSpeed()const;
		
		//Narrative: Return the players current speed. 
		//Pre-condition: Current Speed has a value already.
		//Post-condition: Current Speed has been returned.
		int CurrentSpeed()const;
		
		//Narrative: Return the players momentum. 
		//Pre-condition: Momentum has a value already.
		//Post-condition: Momentum has been returned.
		int Momentum() const;
		
		//Narrative: Return the players power. 
		//Pre-condition: Power has a value already.
		//Post-condition: Power has been returned.
		int Power()const;
		
		//Narrative: Return the players physical damage. 
		//Pre-condition: The players noDice and diceFaces has a value already.
		//Post-condition: Physical damage is returned.
		int RollPhysDam() const;
		
		//Narrative: Return the players defense. 
		//Pre-condition: Defense has a value already.
		//Post-condition: Defense has been returned.
		int Defense()const;
		
		//Narrative: Return true if the player p is my enemy, false otherwise.
		//Pre-condition: A specific PlayerClass (p) exists and is sent into the method.
		//Post-condition: Whether or not the other player is an enemy is sent back.
		virtual bool IsMyEnemy(const PlayerClass* p, bool beenHere = false) const = 0;
		
		//Narrative: Return if player Health is greater than zero.
		//Pre-condition: Health has value 
		//Post-condition: Player alive-ness is returned
		bool IsAlive() const;
		
		//Narrative: Return if player Health is less than or equal to zero.
		//Pre-condition: Health has value 
		//Post-condition: Player alive-ness is returned
		bool IsDead() const;
		
		//Narrative: Return true if player is active, false otherwise. 
		//Pre-condition: None
		//Post-condition: Returns if player is active
		bool IsActive() const;
		
		//Narrative: Output the player data
		//Pre-condition: ostream is valid.   
		//Post-condition: Player is output to the screen.
		virtual void Write (ostream& out) const;
		
		//Narrative: Sets player to be active unless player is dead. 
		//Pre-condition: None
		//Post-condition: Return true if player is now active, false otherwise.
		bool MakeActive();
		
		//Narrative: Sets player to be inactive.
		//Pre-condition: Player is active.
		//Post-condition: Player is inActive
		bool MakeInActive();
		
		//Narrative: Sets the health, willpower, momentum, and current speed to zero to indicate a player is dead. 
		//Player is set to inactive. Return true indicating player is dead. (always returns true).
		//Pre-condition: IsAlive is true. 
		//Post-condition: Health, willpower, momentum and currspeed are set to 0 and MakeDead returns true.
		bool MakeDead();
		
		//Narrative: If the player is active and damage is greater than zero the damage is deducted from the health. 
		//If the player’s health drops to zero or below then the player is dead and no longer active. Return the health.
		//Pre-condition: IsActive() is true and the damage is greater than zero.
		//Post-condition: Damage is subtracted from current health.If health < or = 0, player is inactive and dead.
		int Wounded(int damage);
		
		//Narrative: If the player is active and vigor is great than zero the vigor is added to the health. Return the health
		//Pre-condition: Player is active and vigor is greater than zero.
		//Post-condition: Vigor is added to health, new health returned.
		int Invigorate(int vigor);
		
		//Narrative: If the player is active updates the appropriate values to indicate player has healed. Return true unless player could not be healed because the player is not active or dead.
		//Pre-condition: Player is active.
		//Post-condition: Health is increased.
		virtual	bool Heal();
		
		//Narrative: If the player is active and hazard is greater than zero the hazard is deducted from current speed. 
		//The current speed cannot drop below zero and momentum should never be above current speed. 
		//If necessary, reduce the momentum to the value of current speed. Return the current speed.
		//Pre-condition: Player is active and hazard is encountered.
		//Post-condition: Currentspeed has decreased due to hazard. If currentSpeed is now less than zero, it equals zero. 
		//If momentum exceeded currentSpeed, momentum is now set to currentSpeed. New currentSpeed returned.
		int SlowDown(int hazard);
		
		//Narrative: Checks if the player is active. If they are is then “curSpeed” is equal to “MAX_SPD”. 
		//If not then speed remains at 0.
		//Pre-condition: IsActive has been set and the players speed is at zero.
		//Post-condition: Returns currentSpeed either at 0 or at MAX_SPD.
		int ResetCurrentSpeed();
		
		//Narrative: If the player is active momentum is reset to the current speed. Return the momentum
		//Pre-condition: Players activity is set. Current speed is valid. 
		//Post-condition: Momentum is set to currentSpeed, momentum returned.
		int ResetMomentum();
			
		//Narrative: If the player is active and amount is greater than zero the amount is deducted from the momentum. The momentum cannot drop below zero. Return the momentum
		//Pre-condition: Amount is valid and player is active
		//Post-condition: New momentum is momentum minus the amount. If difference is below zero, momentum is 0.
		int UseMomentum(int amount);
		
		//Narrative: Updates the player’s current coordinates regardless of player’s state. 
		//If both newRow and newCol > - 1 then the coordinates are set. 
		//If both newRow and newCol are -1 then coordinates are set (indicates player not on board).
		//In all other cases, coordinates should not be set. If coordinates are set, return true.
		//In all other cases, return false
		//Pre-condition: newRow and newCol are valid.
		//Post-condition: row and col have been set to equal newRow and newCol.
		bool SetCell(int newRow, int newCell);
		
		//Narrative: Updates the player’s current direction regardless of player state. If the direction is updated return true, in all other cases, return false.
		//Pre-condition: dir is valid.
		//Post-condition: Player direction is updated.
		bool SetDir(GameSpace::DirType dir);
		
		//Narrative: If the player is active and boost is greater than zero the boost is added to the defense. Return the defense.
		//Pre-condition: boost is sent in
		//Post-condition: the defense is raised
		int Fortify(int boost);
		
		//Narrative: If the player is active and decline is greater than zero the decline is deducted from the defense. If
		//the player’s defense drops below zero, set it to zero indicating the player cannot defend itself. Return the defense.
		//Pre-condition:decline is sent in
		//Post-condition: the defense is lowered
		int Expose(int decline);
		
		//Narrative: If the player is active the adjustment is applied Will Power. Valid will power is between 0 and 12.
		//If will power exceeds 12, reset will power to 12. If the player’s will power drops below zero, reset to 0 and
		//the player is dead and no longer active. Returned the will power. 
		//Pre-condition: adjustment is sent in
		//Post-condition: Willpower is adjusted
		int WillPowerAdj(int adjustment);
		
		//Narrative: If the player is active the hit score is rolled and returned, otherwise 0 is returned. 
		//Pre-condition: none
		//Post-condition: hit score returned
		int HitScore() const;
		
		//Narrative: If the player is active, the damage inflicted is returned, other wise 0 is returned. 
		//Damage is calculated by the Physical Damage of player
		//Pre-condition: none 
		//Post-condition: hit damage returned
		virtual int HitDamage() const; 
		
		//Narrative: If the player is active, the impact of a critical wound inflicted is returned, otherwise 0 is returned.
		//Impact is looked up in the table by Willpower. A player can inflict no critical wound if they are not active or 
		//have no weapon and player power is less than 2. Return -1 if the wound is a mortal wound (‘w’ in the strike table).
		//Pre-condition: Player is active
		//Post-condition: Value of impact damage on enemy is returned.
		virtual int Impact() const; 
		
		//Narrative: Applies the outcome of a critical wound on an active player. The player’s health is reduced by 10
		//points and the current speed is decreased by half (round down). If player is still alive then consult
		//the Critical Wound Table for the damage to the willpower or the life ending damage. Return true
		//if player is still alive and false if player is dead.
		//Pre-condition: none
		//Post-condition: The health is reduced by 10 and speed is halved. If health drops below 0 player is dead.
		bool CriticalWound();
		
		//Overload equal to sign to compare two PlayerClass's
		bool operator== (const PlayerClass& p) const;
		//Overload not equal to sign to compare two PlayerClass's
		bool operator!= (const PlayerClass& p) const;
		//Overload less than sign to compare two PlayerClass's
		bool operator<  (const PlayerClass& p) const;
		//Overload greater than sign to compare two PlayerClass's
		bool operator>  (const PlayerClass& p) const;
		//Overload less than or equal to sign to compare two PlayerClass's
		bool operator<= (const PlayerClass& p) const;
		//Overload greater than or equal to sign to compare two PlayerClass's
		bool operator>= (const PlayerClass& p) const;
		
		
		
	private:
		//Enums
		enum StatsIndex {SPEED, MOMENTUM, HEALTH, WILLPOWER, POWER, DEFENSE, ACTIVE, ROW, COL, DIR, MAX_VAR_STATS}; 
		enum ConstStatsIndex {MAX_SPD, MAX_HP, PD_NUM_DIE, PD_FACES, MAX_CONST_STATS};
		
		//Constant Variables
		static const int NUM_STATS = MAX_VAR_STATS;		//Max Rows
		static const int NUM_CONST_STATS = MAX_CONST_STATS;
		static const int DEAD_AMT = 0;					//Amount that Makes Player Considered Dead
		static const int MAX_NAME_SIZE = 10;		
		
		const string NAME;
		int stats [NUM_STATS];							//PlayerStats
		const int* const STATS;
		
		//Narrative: Determine if the sent in name meets the requirements by checking 
		//the length and capitalization.
		//Pre-condition: initPName is sent in with value.
		//Post-condition: initPName is sent back validated or an exception is thrown.
		string ValidateName(string initPName) const;
		
		//Narrative: Default race is EXPLORER; name is “DEFAULT”. Set the instance attributes appropriately.
		//Pre-condition: New Player instance is created.
		//Post-condition: Player instance created with type EXPLORER stats and name DEFAULT.
		PlayerClass();	
		
		//Narrative: All of p's values are equal to this PlayerClass's
		//Pre-condition: p is sent in
		//Post-condition: p = PlayerClass
		//PlayerClass (const PlayerClass& p);
};
 
 
//Narrative: Overloaded output operator to output all of the PlayerClass private data.
//Pre-condition: PlayerClass is sent in
//Post-condition: PlayerClass data is outputted
 ostream& operator<< (ostream& out, const PlayerClass* p);


#endif