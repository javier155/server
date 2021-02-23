//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCDeletePCError.cpp 
// Written By  : Reiot
// Description :
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "LCDeletePCError.h"

//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void LCDeletePCError::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read( m_ErrorID );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void LCDeletePCError::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_ErrorID );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void LCDeletePCError::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	LCDeletePCErrorHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string LCDeletePCError::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "LCDeletePCError( " << (int)m_ErrorID << ")";
	return msg.toString();

	__END_CATCH
}


