//////////////////////////////////////////////////////////////////////////////
// Filename    : GCTeachSkillInfoHandler.cpp
// Written By  : 김성민 
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCTeachSkillInfo.h"

//////////////////////////////////////////////////////////////////////
// 클라이언트에서 서버로부터 메시지를 받았을때 실행되는 메쏘드이다.
//////////////////////////////////////////////////////////////////////
void GCTeachSkillInfoHandler::execute ( GCTeachSkillInfo * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	
#ifdef __GAME_CLIENT__
	//cout << pPacket->toString() << endl;
#endif

	__END_DEBUG_EX __END_CATCH
}
