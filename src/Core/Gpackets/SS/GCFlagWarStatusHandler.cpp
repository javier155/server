//////////////////////////////////////////////////////////////////////
//
// Filename    : GCFlagWarStatusHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCFlagWarStatus.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCFlagWarStatusHandler::execute ( GCFlagWarStatus * pGCFlagWarStatus , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_CLIENT__

	//cout << pGCFlagWarStatus->toString() << endl;
	
#elif __WINDOWS__

#endif

	__END_DEBUG_EX __END_CATCH
}
