//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddNickname.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCAddNickname.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCAddNickname::GCAddNickname () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCAddNickname::~GCAddNickname () 
    
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCAddNickname::read (SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY

	m_NicknameInfo.read(iStream);
		
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCAddNickname::write (SocketOutputStream & oStream ) 
     const 
{
	__BEGIN_TRY

	m_NicknameInfo.write(oStream);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCAddNickname::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCAddNicknameHandler::execute(this , pPlayer);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCAddNickname::toString () 
	const 
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCAddNickname("
		<< ")";
	return msg.toString();

	__END_CATCH
}

