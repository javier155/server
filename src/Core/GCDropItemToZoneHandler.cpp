//////////////////////////////////////////////////////////////////////
//
// Filename    : GCDropItemToZoneHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCDropItemToZone.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCDropItemToZoneHandler::execute (GCDropItemToZone * pPacket , Player * pPlayer )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_CLIENT__

	//cout << pPacket->toString() << endl;
	
#elif __WINDOWS__

#endif

	__END_DEBUG_EX __END_CATCH
}
