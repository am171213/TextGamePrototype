//Alexander Miller
//CSCI 330 9:30-10:45
//Program 4
//Spider Header

#ifndef _SPIDERH
#define _SPIDERH
#include <iostream>
#include "bug5.h"

class Spider: public Bug
{	
	public:
	//"SPIDER"
		static const string TYPE_STR;
		
	//Narrative: Calls Parent parameterized constructors with class stats.
	//PreCon: Name sent in
	//PostCon: Bug constructor called.	
		Spider (string name);
	//Narrative: Provides a pointer to current instance	
		Spider* Clone() const;
		
	//Narrative: Returns Type as a string.	
		string TypeStr() const;	
	//Narrative: Output TypeStr and call parents Write.
	//PreCon: None
	//PostCon: Class data outputted.
		void Write (ostream& out) const;
	//Narrative: Return whether passed in player is enemy or not	
		bool IsMyEnemy(const PlayerClass* p, bool beenHere = false) const;
		
	private:
	//Narrative: Default values assigned
		Spider();

		static const int INIT_CONST_STATS[4];
		static const int INIT_VAR_STATS[10];
};

#endif