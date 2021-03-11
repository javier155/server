//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddEffect.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCAddEffect.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCAddEffect::GCAddEffect () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCAddEffect::~GCAddEffect () 
    
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCAddEffect::read (SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
    BYTE flag;
    iStream.read(flag);
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read(m_ObjectID);
	iStream.read(m_EffectID);
	iStream.read(m_Duration);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCAddEffect::write (SocketOutputStream & oStream ) 
     const 
{
	__BEGIN_TRY
//	oStream.write((BYTE)48);
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write(m_ObjectID);
	oStream.write(m_EffectID);
	oStream.write(m_Duration);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCAddEffect::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCAddEffectHandler::execute(this , pPlayer);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCAddEffect::toString () 
	const 
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCAddEffect("
		<< "ObjectID:"  << (int)m_ObjectID 
		<< ",EffectID:" << (int)m_EffectID
		<< ",Duration:" << (int)m_Duration
		<< ")";
	return msg.toString();

	__END_CATCH
}

