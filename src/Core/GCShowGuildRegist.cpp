//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowGuildRegist.cpp 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCShowGuildRegist.h"


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCShowGuildRegist::read (SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_RegistrationFee);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCShowGuildRegist::write (SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_RegistrationFee);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCShowGuildRegist::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCShowGuildRegistHandler::execute(this , pPlayer);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCShowGuildRegist::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCShowGuildRegist("
		<< "RegistrationFee:" << m_RegistrationFee
		<< ")";
	
	return msg.toString();
		
	__END_CATCH
}

