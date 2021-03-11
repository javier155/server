//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRemoveFromGear.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCRemoveFromGear.h"




//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCRemoveFromGear::GCRemoveFromGear () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCRemoveFromGear::~GCRemoveFromGear () 
    
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCRemoveFromGear::read (SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_SlotID);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCRemoveFromGear::write (SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY

	oStream.write(m_SlotID);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCRemoveFromGear::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY

	GCRemoveFromGearHandler::execute (this , pPlayer);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// toString()
//////////////////////////////////////////////////////////////////////
string GCRemoveFromGear::toString () const
    
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCRemoveFromGear("
		<< "Part:" << (int)m_SlotID
		<< " )";
	return msg.toString();

	__END_CATCH
}

