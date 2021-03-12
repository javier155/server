////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionHasEnoughFamilyCoin.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionHasEnoughFamilyCoin.h"
#include "PlayerCreature.h"
#include "Inventory.h"
#include "FlagSet.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionHasEnoughFamilyCoin::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);

	Inventory* pInventory = pPC->getInventory();
	if (pInventory == NULL ) return false;

	return pInventory->hasEnoughNumItem(Item::ITEM_CLASS_EVENT_ETC, 18, 9);

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionHasEnoughFamilyCoin::read (PropertyBuffer & propertyBuffer) 
	
{
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionHasEnoughFamilyCoin::toString () const 
	 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionHasEnoughFamilyCoin("
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
