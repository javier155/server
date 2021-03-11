//////////////////////////////////////////////////////////////////////////////
// Filename    : GCModifyNickname.cpp 
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCModifyNickname.h"
#include "RaceWarInfo.h"
#include "LevelWarInfo.h"
#include "GuildWarInfo.h"
#include "Assert1.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
GCModifyNickname::GCModifyNickname() 
	
{
	__BEGIN_TRY 

	m_ObjectID = 0;

	__END_CATCH;
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
GCModifyNickname::~GCModifyNickname() 
	
{
	__BEGIN_TRY 

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GCModifyNickname::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	iStream.read(m_ObjectID);
	m_pNicknameInfo->read(iStream);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void GCModifyNickname::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	m_pNicknameInfo->write(oStream);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCModifyNickname::execute (Player * pPlayer) 
	 
{
	__BEGIN_TRY
		
	GCModifyNicknameHandler::execute(this , pPlayer);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCModifyNickname::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCModifyNickname(" ;
	msg << ")";

	return msg.toString();
		
	__END_CATCH
}


