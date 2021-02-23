////////////////////////////////////////////////////////////////////////////////
// Filename    : GCTradePrepare.cpp 
// Written By  : 김성민
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "GCTradePrepare.h"

////////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
////////////////////////////////////////////////////////////////////////////////
void GCTradePrepare::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read( m_TargetObjectID );
	iStream.read( m_Code );
		
	__END_CATCH
}

		    
////////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
////////////////////////////////////////////////////////////////////////////////
void GCTradePrepare::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	
	oStream.write( m_TargetObjectID );
	oStream.write( m_Code );

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// execute packet's handler
////////////////////////////////////////////////////////////////////////////////
void GCTradePrepare::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCTradePrepareHandler::execute( this , pPlayer );

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get packet's debug string
////////////////////////////////////////////////////////////////////////////////
string GCTradePrepare::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCTradePrepare("
		<< "TargetObjectID:" << (int)m_TargetObjectID
		<< ",CODE:" << (int)m_Code
		<< ")";
	return msg.toString();
		
	__END_CATCH
}


