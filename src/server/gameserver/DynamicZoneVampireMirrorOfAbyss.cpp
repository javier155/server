/////////////////////////////////////////////////////////////////////////////
// DynamicZoneVampireMirrorOfAbyss.cpp
/////////////////////////////////////////////////////////////////////////////

#include "DynamicZoneVampireMirrorOfAbyss.h"
#include "DynamicZoneInfo.h"
#include "Zone.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "PCManager.h"
#include "MonsterManager.h"
#include "EffectKillTimer.h"
#include "GQuestManager.h"
#include "Assert.h"

#include "Gpackets/GCSystemMessage.h"

#include <stdio.h>
#include <stdlib.h>

enum VAMPIRE_MIRROR_OF_ABYSS
{
	WAIT_FOR_PC,
	ADD_MONO,
	WAIT_FOR_COMPLETE,
	CLEAR_MONO,
	WAIT_FOR_CLEAR,
	VAMPIRE_MIRROR_OF_ABYSS_END,

	VAMPIRE_MIRROR_OF_ABYSS_MAX
};

DynamicZoneVampireMirrorOfAbyss::DynamicZoneVampireMirrorOfAbyss()
{
	m_MonoObjectID = 0;
}

DynamicZoneVampireMirrorOfAbyss::~DynamicZoneVampireMirrorOfAbyss()
{
}

void DynamicZoneVampireMirrorOfAbyss::init()
{
	Assert( m_pZone != NULL );

	m_VMOAStatus = WAIT_FOR_PC;
	getCurrentTime( m_Deadline );
	m_Deadline.tv_sec += 60;
	getCurrentTime( m_EndTime );
	m_EndTime.tv_sec += 10 * 60;
}

void DynamicZoneVampireMirrorOfAbyss::heartbeat()
{
	switch ( m_VMOAStatus )
	{
	case WAIT_FOR_PC:
		if ( checkPC() )
		{
			processEntering();
			m_VMOAStatus = ADD_MONO;
			cout << "-----------------------ADD_MONO" << endl;
		}
		break;

	case ADD_MONO:
		if ( addMono() )
		{
			m_VMOAStatus = WAIT_FOR_COMPLETE;
			cout << "-----------------------WAIT_FOR_COMPLETE" << endl;
		}
		break;

	case WAIT_FOR_COMPLETE:
		if ( checkComplete() )
		{
			openGateToOut();
			m_VMOAStatus = CLEAR_MONO;
			cout << "-----------------------CLEAR_MONO" << endl;
		}

		if ( !checkMono() )
		{
			killPC();
		}

		break;

	case CLEAR_MONO:
		if ( clearMono() )
		{
			m_VMOAStatus = WAIT_FOR_CLEAR;
			cout << "-----------------------WAIT_FOR_CLEAR" << endl;
		}
		break;

	case WAIT_FOR_CLEAR:
		if ( !checkPC() && !checkMono() )
		{
			m_VMOAStatus = VAMPIRE_MIRROR_OF_ABYSS_END;
			m_Status = DYNAMIC_ZONE_STATUS_READY;
			cout << "-----------------------READY" << endl;
		}
		break;
	}

	if ( !checkPC() )
	{
		if ( m_VMOAStatus == WAIT_FOR_PC )
		{
			Timeval current;
			getCurrentTime( current );

			if ( current > m_Deadline )
			{
				m_VMOAStatus = CLEAR_MONO;
				cout << "-----------------------Time out" << endl;
			}
		}
		else if ( m_VMOAStatus == WAIT_FOR_COMPLETE )
		{
			m_VMOAStatus = CLEAR_MONO;
		}
	}
}

bool DynamicZoneVampireMirrorOfAbyss::checkPC()
{
	Assert( m_pZone != NULL );

	// PC �� üũ
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}

bool DynamicZoneVampireMirrorOfAbyss::addMono()
{
	Assert( m_pZone != NULL );

	// �̼��� ������ �����Ѵ�.
	Monster* pMonster = new Monster( 792 );
	Assert( pMonster != NULL );

	pMonster->setName( "����֮��ӡ" );
	pMonster->setClanType(33);

	try
	{
		m_pZone->addCreature( pMonster, 15, 15, 2 );
		m_pZone->getMonsterManager()->addEnemy(NULL,pMonster);

		m_MonoObjectID = pMonster->getObjectID();
	}
	catch ( EmptyTileNotExistException& )
	{
		SAFE_DELETE( pMonster );
	}

	return true;
}

bool DynamicZoneVampireMirrorOfAbyss::clearMono()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pCreature = pMonsterManager->getCreature( m_MonoObjectID );
	if ( pCreature != NULL )
	{
		if ( pCreature->isMonster() )
		{
			EffectKillTimer* pEffect = new EffectKillTimer( pCreature, true );
			pCreature->setFlag( pEffect->getEffectClass() );
			pEffect->setDeadline(50);
			pCreature->addEffect( pEffect );
		}
	}

	return true;
}

bool DynamicZoneVampireMirrorOfAbyss::openGateToOut()
{
	Assert( m_pZone != NULL );

    // ����Ʈ�� �����Ų��.
    hash_map<ObjectID_t, Creature*>::const_iterator itr = m_pZone->getPCManager()->getCreatures().begin();
    hash_map<ObjectID_t, Creature*>::const_iterator endItr = m_pZone->getPCManager()->getCreatures().end();

    for ( ; itr != endItr; ++itr )
    {
        Assert( itr->second != NULL );

        if ( itr->second->isPC() )
        {
            PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(itr->second);
            Assert( pPC != NULL );

            pPC->getGQuestManager()->clearDynamicZone(m_TemplateZoneID);
        }
    }

	return true;
}

bool DynamicZoneVampireMirrorOfAbyss::checkComplete()
{
	Timeval current;
	getCurrentTime( current );
	if ( current > m_EndTime )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void DynamicZoneVampireMirrorOfAbyss::processEntering()
{
	Assert( m_pZone != NULL );

    // ����Ʈ ���� �������� �˸���.
    hash_map<ObjectID_t, Creature*>::const_iterator itr = m_pZone->getPCManager()->getCreatures().begin();
    hash_map<ObjectID_t, Creature*>::const_iterator endItr = m_pZone->getPCManager()->getCreatures().end();

    for ( ; itr != endItr; ++itr )
    {
        Assert( itr->second != NULL );

        if ( itr->second->isPC() )
        {
            PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(itr->second);
            Assert( pPC != NULL );

            pPC->getGQuestManager()->enterDynamicZone(m_TemplateZoneID);
        }
    }
}

bool DynamicZoneVampireMirrorOfAbyss::checkMono()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pCreature = pMonsterManager->getCreature( m_MonoObjectID );
	return pCreature != NULL;
}

void DynamicZoneVampireMirrorOfAbyss::killPC()
{
	Assert( m_pZone != NULL );

    // PC �� ���δ�.
    hash_map<ObjectID_t, Creature*>::const_iterator itr = m_pZone->getPCManager()->getCreatures().begin();
    hash_map<ObjectID_t, Creature*>::const_iterator endItr = m_pZone->getPCManager()->getCreatures().end();

    for ( ; itr != endItr; ++itr )
    {
        Assert( itr->second != NULL );

        if ( itr->second->isPC() )
        {
            PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(itr->second);
            Assert( pPC != NULL );

			if ( pPC->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
				Assert( pSlayer != NULL );

				pSlayer->setHP(0);
			}
			else if ( pPC->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
				Assert( pVampire != NULL );

				pVampire->setHP(0);
			}
			else if ( pPC->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
				Assert( pOusters != NULL );

				pOusters->setHP(0);
			}
        }
    }
}


DEFINE_DYNAMIC_ZONE_FACTORY( DynamicZoneVampireMirrorOfAbyss, DYNAMIC_ZONE_VAMPIRE_MIRROR_OF_ABYSS )

