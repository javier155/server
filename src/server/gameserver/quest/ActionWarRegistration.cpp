////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionWarRegistration.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionWarRegistration.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "GuildWar.h"
#include "WarScheduler.h"
#include "GuildManager.h"
#include "Guild.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "PlayerCreature.h"
#include "VariableManager.h"
#include "Properties.h"
#include "CastleInfoManager.h"

#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCModifyInformation.h"

#include "SystemAvailabilitiesManager.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionWarRegistration::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
		// read script id
		m_ZoneID = propertyBuffer.getPropertyInt("ZoneID");
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionWarRegistration::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	SYSTEM_RETURN_IF_NOT( SYSTEM_GUILD_WAR );

	GCNPCResponse gcNPCResponse;

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>( pCreature2 );
	GuildID_t guildID = pPC->getGuildID();

	if ( !g_pVariableManager->isWarActive() || !g_pVariableManager->isActiveGuildWar() )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_WAR_UNAVAILABLE );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
		return;
	}

	if ( !g_pGuildManager->isGuildMaster( guildID, pPC ) )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_NOT_GUILD_MASTER );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
		return;
	}

	Gold_t warRegistrationFee = g_pVariableManager->getVariable( WAR_REGISTRATION_FEE );
	if ( pPC->getGold() < warRegistrationFee )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_NOT_ENOUGH_MONEY );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
		return;
	}

	Zone* pZone = getZoneByZoneID( m_ZoneID );
	Assert( pZone != NULL );
	Assert( pZone->isCastle() );

	WarScheduler* pWarScheduler = pZone->getWarScheduler();
	Assert( pWarScheduler != NULL );

	// 이미 성을 소유한 길드인가?
	if ( g_pGuildManager->hasCastle( guildID ) )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_ALREADY_HAS_CASTLE );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
		return;
	}

//	ServerID_t serverID;
//	ZoneID_t zoneID;
//	bool bHasCastle = g_pGuildManager->hasCastle( guildID , serverID , zoneID );

//	if ( bHasCastle && serverID == g_pConfig->getPropertyInt( "ServerID" ) && zoneID == m_ZoneID )

	CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_ZoneID );
	GuildID_t ownerGuildID = pCastleInfo->getGuildID();

	if ( guildID == ownerGuildID )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_ALREADY_HAS_CASTLE );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
		return;
	}

	// 이미 전쟁 신청을 했는가?
	if ( g_pGuildManager->hasWarSchedule( guildID ) )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_WAR_ALREADY_REGISTERED );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
		return;
	}

	// 전쟁 스케쥴이 다 찼는가?
	if ( !pWarScheduler->canAddWar( WAR_GUILD ) )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_WAR_SCHEDULE_FULL );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
		return;
	}

	GuildWar* pWar = new GuildWar( m_ZoneID, guildID, War::WAR_STATE_WAIT );

	pWar->setRegistrationFee( warRegistrationFee );

	if ( !pWarScheduler->addWar( pWar ) )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_WAR_SCHEDULE_FULL );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );

		SAFE_DELETE( pWar );
		return;
	}

	pPC->decreaseGoldEx( warRegistrationFee );

	GCModifyInformation gcMI;
	gcMI.addLongData( MODIFY_GOLD, pPC->getGold() );
	pPC->getPlayer()->sendPacket( &gcMI );

	gcNPCResponse.setCode( NPC_RESPONSE_WAR_REGISTRATION_OK );
	pPC->getPlayer()->sendPacket( &gcNPCResponse );
	return;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionWarRegistration::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionWarRegistration("
	    << ",ZoneID:"  << (int)m_ZoneID
	    << ")";

	return msg.toString();

	__END_CATCH
}
