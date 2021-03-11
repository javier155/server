//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddressListVerify.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GCAddressListVerify.h"

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GCAddressListVerify::read (SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY

	iStream.read(m_Code);
	iStream.read(m_Parameter);

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void GCAddressListVerify::write (SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY

	oStream.write(m_Code);
	oStream.write(m_Parameter);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCAddressListVerify::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCAddressListVerifyHandler::execute(this , pPlayer);
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCAddressListVerify::toString () const
       
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCAddressListVerify(" 
	    << "Code : " << (int)m_Code 
		<< "Parameter : " << (int)m_Parameter
	    << ")";
	return msg.toString();

	__END_CATCH
}
