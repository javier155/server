//////////////////////////////////////////////////////////////////////
//
// Filename    : GCActiveGuildListHandler.cpp
// Written By  : 
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCActiveGuildList.h"

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
void GCActiveGuildListHandler::execute ( GCActiveGuildList * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	
#ifdef __GAME_CLIENT__
	//cout << pPacket->toString() << endl;
#endif

	__END_DEBUG_EX __END_CATCH
}
