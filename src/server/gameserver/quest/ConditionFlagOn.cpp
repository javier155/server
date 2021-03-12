////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionFlagOn.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionFlagOn.h"
#include "PlayerCreature.h"
#include "FlagSet.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionFlagOn::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	FlagSet* pFlagSet = pPC->getFlagSet();

	if (pFlagSet->isOn(m_Index)) return true;

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionFlagOn::read (PropertyBuffer & propertyBuffer) 
	
{
	try
	{
		// read turn
		m_Index = propertyBuffer.getPropertyInt("Index");
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionFlagOn::toString () const 
	 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionFlagOn("
		<< "Index:" << (int)m_Index
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
