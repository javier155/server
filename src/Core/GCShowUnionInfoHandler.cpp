//////////////////////////////////////////////////////////////////////
//
// Filename    : GCShowUnionInfoHandler.cpp
// Written By  : 
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCShowUnionInfo.h"

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
void GCShowUnionInfoHandler::execute (GCShowUnionInfo * pPacket , Player * pPlayer )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	
#ifdef __GAME_CLIENT__
	//cout << pPacket->toString() << endl;
#endif

	__END_DEBUG_EX __END_CATCH
}
