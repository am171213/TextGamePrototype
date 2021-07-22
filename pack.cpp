//Alexander Miller
// pack.cpp

#include "pack.h"

//***********************************************Constr/destr/assignment
PackClass::PackClass():MAX_WT(0)
{
}

PackClass::PackClass(int wt): MAX_WT(wt)
{
}

PackClass::PackClass(const PackClass & p):MAX_WT(p.MAX_WT)
{
	CopyPack(p);  
}

PackClass::~PackClass( )
{
	EmptyPack( );
}

PackClass& PackClass::operator=(const PackClass& p)
{
	if (this != &p)
		CopyPack(p);

	return *this;
}

void PackClass::CopyPack(const PackClass & p)
{  
	// must create a FULL COPY of each weapon in p
	// add add to packVec
	EmptyPack();
	*const_cast<int *>(&MAX_WT) = p.MAX_WT;
	int length = p.packVec.size();
	Weapon* w=NULL;

	for (int i = 0; i < length; ++i)
	{
		w = new Weapon(*(p.packVec.at(i)));
		bool canAdd = AddWeapon(w);
		if (!canAdd)
			throw INVALID_MISC;
	}     
} 

//***********************************************Transformers

bool PackClass::AddWeapon(Weapon* w)
{
	// be sure weapon can be added 
	// add weapon ptr to the packVec
	bool canAdd = false;
	if (w == NULL)
		throw INVALID_WPN;
	int newWgt = Wt() + w->Wt();

	if (newWgt <= MAX_WT)
	{
		canAdd = true; 
		packVec.push_back(w);
	}

	return canAdd;
}

Weapon * PackClass::RemoveWeapon(string wName)
{
	Weapon * ret_w = NULL;
	if (InPack(Ucase(wName)))
	{
		ret_w = *(FindWeapon(wName));
		packVec.erase(FindWeapon(wName));
	}
	return ret_w;
}

void PackClass::EmptyPack( )  
{
	// Empty the packVec - 
	// be sure to actually deallocate all the weapons!!
	int length = packVec.size();

	vector<Weapon*>::iterator iter;
	for (iter = packVec.begin(); iter != packVec.end(); ++iter)
	{
		delete(*iter);
	}
	packVec.clear();
}  

//***********************************************Observers

bool PackClass::InPack(string wName) const
{	
	bool found = false;
	int length = packVec.size();
	
	for(int iter = 0; iter < length && !found; ++iter)
	{
		if (Ucase(packVec[iter]->Name()) == Ucase(wName))
		{
			found = true;	
		}
	}
	return (found); 
}

vector<Weapon *>::iterator PackClass::FindWeapon(string wName)
{	
	// Find the weapon in the packVec and return 
	// the iterator to the first instance of that weapon
	//   if not found - return packVec.end()
	bool found = false;
	vector<Weapon *>::iterator ret_iter, iter; 

	for(iter = packVec.begin(); iter != packVec.end() && !found; ++iter)
	{
		if (Ucase((*iter)->Name()) == Ucase(wName))
		{
			ret_iter = iter;
			found = true;	
		}
	}
	
	if (!found)
		{ret_iter = packVec.end();}
	
	return (ret_iter); 
}

int PackClass::Size( ) const
{
	return packVec.size();
}

int PackClass::Wt( ) const
{	
	// Calculate the weight of the pack
	int wgt = 0;
	int length = Size();
	for (int i = 0; i < length; ++i)
	{
		wgt += packVec.at(i)->Wt();
	}
	return wgt;
}

int PackClass::MaxWt( ) const
{
	return MAX_WT;
}

bool PackClass::IsEmpty( ) const
{
	return (packVec.size()==0);
}

bool PackClass::IsFull( ) const
{
	// pack is full if weight is at the MAX_WT
	return (Wt() == MaxWt());
}

vector<string> PackClass::PackInventory( ) const
{
	// return a vector of weapon names in the pack
	vector<string> wpnNames;
	int length = packVec.size();
	for (int i = 0; i < length; ++i)
	{
		wpnNames.push_back(packVec.at(i)->NameAndNum());
	}
	return wpnNames;
}

void PackClass::Write(ostream & out ) const
{
	// outputs the weapons to the out ostream
	// uses Weapon::Write(out) - each on a new line.
	int length = packVec.size();
	
	for (int i = 0; i < length; ++i)
	{
		out << '\t';
		packVec.at(i)->Write(out);
		out << endl;
	}
}

Weapon& PackClass::operator[](int i)
{
	Weapon *thisWpn = NULL;
	vector<Weapon *>::iterator iter; 
	
	if (packVec.at(i))
	{
		for (iter = packVec.begin(); iter != packVec.end(); ++iter)
		{
			if (Ucase(packVec.at(i)->Name()) == Ucase((*iter)->Name()))
				{thisWpn = *iter;}
		}
	}
	return *thisWpn; 
}
