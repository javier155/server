//////////////////////////////////////////////////////////////////////////////
// Filename    : CGWithdrawPet.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGWithdrawPet.h"

void CGWithdrawPet::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY 
		
	iStream.read(m_ObjectID);
	iStream.read(m_Index);

	__END_CATCH
}

void CGWithdrawPet::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_Index);

	__END_CATCH
}

void CGWithdrawPet::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGWithdrawPetHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGWithdrawPet::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGWithdrawPet("
		<< " ObjectID : " << (int)m_ObjectID
		<< " Index : "    << (int)m_Index
		<< ")";
	return msg.toString();

	__END_CATCH
}
