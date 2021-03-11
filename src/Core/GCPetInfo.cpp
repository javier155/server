//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPetInfo.cpp 
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCPetInfo.h"
#include "RaceWarInfo.h"
#include "LevelWarInfo.h"
#include "GuildWarInfo.h"
#include "Assert1.h"

#ifdef __GAME_SERVER__
#include "PetItem.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
GCPetInfo::GCPetInfo() 
	
{
	__BEGIN_TRY 

	m_pPetInfo = NULL;
	m_ObjectID = 0;

	__END_CATCH;
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
GCPetInfo::~GCPetInfo() 
	
{
	__BEGIN_TRY 

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GCPetInfo::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	m_pPetInfo = new PetInfo;
	m_pPetInfo->read(iStream);
	iStream.read(m_ObjectID);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void GCPetInfo::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	if (m_pPetInfo == NULL )
	{
		PetType_t PetType = PET_NONE;
		oStream.write(PetType);
	}
	else
	{
		m_pPetInfo->setSummonInfo(m_IsSummonInfo);
		m_pPetInfo->write(oStream);
	}

	oStream.write(m_ObjectID);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCPetInfo::execute (Player * pPlayer) 
	 
{
	__BEGIN_TRY
		
	GCPetInfoHandler::execute(this , pPlayer);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCPetInfo::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCPetInfo(" ;
	msg << ")";

	return msg.toString();
		
	__END_CATCH
}

ObjectID_t PetInfo::getItemObjectID() const
{
#ifdef __GAME_SERVER__
	if (m_pPetItem == NULL ) return 0;
		return m_pPetItem->getObjectID();
#else
	return 0;
#endif
}

