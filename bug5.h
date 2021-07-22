//Alexander Miller
//CSCI 330 9:30-10:45
//Program 5
//Bug Header

#ifndef _BUG4H
#define _BUG4H
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <map>
#include "player5.h"

class Bug: public PlayerClass
{
	protected:
	//Narrative: Creates Bug instance by sending information to PlayerClass.
	//PreCondition: Information sent in from child class is valid.
	//Post-Condition: Bug Class created.
		Bug (const string NAME, 
			const int INIT_CONST_STATS[], 
			const int INIT_VAR_STATS[]);
	//Narrative: Provides a pointer to current instance
		virtual Bug* Clone() const = 0;
		
	public:
	//Narrative: Outputs child class data.
	//PreCondition: Child class created
	//Post-Condition: Calls PlayerClass Write
		virtual void Write (ostream& out) const; 
	//Narrative: Return whether passed in player is enemy or not
		virtual bool IsMyEnemy (const PlayerClass* p, bool beenHere) const = 0;
	//Narrative: Returns Type
		virtual string TypeStr () const = 0;
	//Narrative: deallocate Bug memory
		virtual ~Bug();
		
	private:
	//Default Bug Class created
		Bug();
};

#endif