//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddHelicopterHandler.cpp
// Written By  : excel96
// Description :
// 슬레이어가 무전기를 사용해, 헬기를 호출했을 경우에 날아가는 패킷
//////////////////////////////////////////////////////////////////////////////

#include "GCAddHelicopter.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void GCAddHelicopterHandler::execute (GCAddHelicopter * pGCAddHelicopter , Player * pPlayer )
	 throw(Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_CLIENT__
	//cout << pGCAddHelicopter->toString() << endl;
#elif __WINDOWS__

#endif

	__END_DEBUG_EX __END_CATCH
}
