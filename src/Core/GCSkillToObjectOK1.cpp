//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToObjectOK1.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCSkillToObjectOK1.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCSkillToObjectOK1::GCSkillToObjectOK1 () 
     
{
	__BEGIN_TRY

	m_Grade = 0;

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCSkillToObjectOK1::~GCSkillToObjectOK1 () 
    
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCSkillToObjectOK1::read (SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read(m_SkillType);
	iStream.read(m_CEffectID);
	iStream.read(m_TargetObjectID);
	iStream.read(m_Duration);
	iStream.read(m_Grade);

	ModifyInfo::read(iStream);
	
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCSkillToObjectOK1::write (SocketOutputStream & oStream ) 
     const 
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write(m_SkillType);
	oStream.write(m_CEffectID);
	oStream.write(m_TargetObjectID);
	oStream.write(m_Duration);
	oStream.write(m_Grade);
	ModifyInfo::write(oStream);
	
	__END_CATCH
}
//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCSkillToObjectOK1::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCSkillToObjectOK1Handler::execute(this , pPlayer);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCSkillToObjectOK1::toString () 
	const 
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCSkillToObjectOK1("
		<< "SkillType:"         << (int)m_SkillType 
		<< ",CEffectID:"        << (int)m_CEffectID 
		<< ",TargetObjectID : " << (int)m_TargetObjectID 
		<< ",Duration: "        << (int)m_Duration
		<< ",Grade: "        << (int)m_Grade;
	msg << ModifyInfo::toString();
    msg << ")";
	return msg.toString();

	__END_CATCH
}


