//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAttackHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCAttack.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAttackHandler::execute (GCAttack * pGCAttack , Player * pPlayer )
	 throw(Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCAttack->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox(pGCAttack->toString().c_str());

#endif

	__END_DEBUG_EX __END_CATCH
}
