//////////////////////////////////////////////////////////////////////////////
// Filename    : GreenStalker.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GreenStalker.h"
#include "EffectGreenStalker.h"
#include "EffectProtectionFromPoison.h"
#include "Vampire.h"
#include "RankBonus.h"

#include "GCSkillToObjectOK1.h"
#include "GCSkillToObjectOK2.h"
#include "GCSkillToObjectOK3.h"
#include "GCSkillToObjectOK4.h"
#include "GCSkillToObjectOK5.h"
#include "GCSkillToObjectOK6.h"
#include "GCSkillToSelfOK1.h"
#include "GCSkillToSelfOK2.h"
#include "GCStatusCurrentHP.h"
#include "GCAddEffect.h"
#include "GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
GreenStalker g_GreenStalker;

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void GreenStalker::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NPC는 공격할 수가 없다.
		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !canAttack(pVampire, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;
		GCSkillToObjectOK6 _GCSkillToObjectOK6;

		SkillType_t SkillType  = pVampireSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		// Knowledge of Poison 이 있다면 hit bonus 10
		int HitBonus = 0;
		if (pVampire->hasRankBonus(RankBonus::RANK_BONUS_KNOWLEDGE_OF_POISON ) )
		{
			RankBonus* pRankBonus = pVampire->getRankBonus(RankBonus::RANK_BONUS_KNOWLEDGE_OF_POISON);
			Assert(pRankBonus != NULL);

			HitBonus = pRankBonus->getPoint();
		}

		int  RequiredMP  = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck  = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck = verifyDistance(pVampire, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pVampireSkillSlot, HitBonus);
		bool bCanHit     = canHit(pVampire, pTargetCreature, SkillType);
		bool bEffected   = pTargetCreature->isFlag(Effect::EFFECT_CLASS_GREEN_STALKER);

		ZoneCoord_t vampX   = pVampire->getX();
		ZoneCoord_t vampY   = pVampire->getY();
		ZoneCoord_t targetX = pTargetCreature->getX();
		ZoneCoord_t targetY = pTargetCreature->getY();

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bCanHit && !bEffected)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToObjectOK1);

			bool bCanSeeCaster = canSee(pTargetCreature, pVampire);

			SkillInput input(pVampire);
			SkillOutput output;
			computeOutput(input, output);

			// 이펙트 오브젝트를 생성해서 붙인다.
			EffectGreenStalker* pEffectGreenStalker = new EffectGreenStalker(pTargetCreature);
			pEffectGreenStalker->setDamage(output.Damage);
			pEffectGreenStalker->setLevel(pSkillInfo->getLevel()/2);
			pEffectGreenStalker->setDeadline(output.Duration);
			pEffectGreenStalker->setTick(output.Tick);
			pEffectGreenStalker->setNextTime(0);
			pEffectGreenStalker->setUserObjectID(pVampire->getObjectID());
			pEffectGreenStalker->setVampire();

			pTargetCreature->addEffect(pEffectGreenStalker);
			pTargetCreature->setFlag(Effect::EFFECT_CLASS_GREEN_STALKER);

			// 이펙트가 붙었으니, 붙었다고 브로드캐스팅해준다.
			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pTargetCreature->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_GREEN_STALKER);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(targetX, targetY, &gcAddEffect);

			if (bCanSeeCaster)
			{
				decreaseDurability(pVampire, pTargetCreature, pSkillInfo, &_GCSkillToObjectOK1, &_GCSkillToObjectOK2);
			}
			else
			{
				decreaseDurability(pVampire, pTargetCreature, pSkillInfo, &_GCSkillToObjectOK1, &_GCSkillToObjectOK6);
			}

			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(output.Duration);
			
			_GCSkillToObjectOK2.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
			_GCSkillToObjectOK2.setDuration(output.Duration);
											
			_GCSkillToObjectOK3.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK3.setSkillType(SkillType);
			_GCSkillToObjectOK3.setTargetXY(targetX, targetY);
															
			_GCSkillToObjectOK4.setSkillType(SkillType);
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);

			_GCSkillToObjectOK5.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK5.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setDuration(output.Duration);

			_GCSkillToObjectOK6.setXY(vampX, vampY);
			_GCSkillToObjectOK6.setSkillType(SkillType);
			_GCSkillToObjectOK6.setDuration(output.Duration);

			pPlayer->sendPacket(&_GCSkillToObjectOK1);

			if (pTargetCreature->isPC())
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);
				if (bCanSeeCaster) pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
				else pTargetPlayer->sendPacket(&_GCSkillToObjectOK6);
			}
			else
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				pMonster->addEnemy(pVampire);
			}

			list<Creature*> cList;
			cList.push_back(pVampire);
			cList.push_back(pTargetCreature);

			cList = pZone->broadcastSkillPacket(vampX, vampY,
				targetX, targetY, &_GCSkillToObjectOK5, cList);

			pZone->broadcastPacket(vampX, vampY,  &_GCSkillToObjectOK3 , cList);
			pZone->broadcastPacket(targetX, targetY,  &_GCSkillToObjectOK4 , cList);

			pVampireSkillSlot->setRunTime(output.Delay);
		} 
		else
		{
			executeSkillFailNormal(pVampire, getSkillType(), pTargetCreature);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void GreenStalker::execute(Monster* pMonster, Creature* pEnemy)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pMonster != NULL);
	Assert(pEnemy != NULL);

	try 
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;
		GCSkillToObjectOK6 _GCSkillToObjectOK6;

		SkillType_t SkillType  = SKILL_GREEN_STALKER;
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		bool bRangeCheck = verifyDistance(pMonster, pEnemy, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessMagic(pMonster, pSkillInfo);
		bool bCanHit     = canHit(pMonster, pEnemy, SkillType);
		bool bEffected   = pEnemy->isFlag(Effect::EFFECT_CLASS_GREEN_STALKER);

		ZoneCoord_t vampX   = pMonster->getX();
		ZoneCoord_t vampY   = pMonster->getY();
		ZoneCoord_t targetX = pEnemy->getX();
		ZoneCoord_t targetY = pEnemy->getY();

		if (bRangeCheck && bHitRoll && bCanHit && !bEffected)
		{
			bool bCanSeeCaster = canSee(pEnemy, pMonster);

			SkillInput input(pMonster);
			SkillOutput output;
			computeOutput(input, output);

			// 이펙트 오브젝트를 생성해서 붙인다.
			EffectGreenStalker* pEffectGreenStalker = new EffectGreenStalker(pEnemy);
			pEffectGreenStalker->setDamage(output.Damage);
			pEffectGreenStalker->setLevel(pSkillInfo->getLevel()/2);
			pEffectGreenStalker->setDeadline(output.Duration);
			pEffectGreenStalker->setTick(output.Tick);
			pEffectGreenStalker->setNextTime(0);
			pEffectGreenStalker->setUserObjectID(pMonster->getObjectID());
			pEnemy->addEffect(pEffectGreenStalker);
			pEnemy->setFlag(Effect::EFFECT_CLASS_GREEN_STALKER);

			// 이펙트가 붙었으니, 붙었다고 브로드캐스팅해준다.
			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pEnemy->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_GREEN_STALKER);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(targetX, targetY, &gcAddEffect);

			if (bCanSeeCaster)
			{
				decreaseDurability(pMonster, pEnemy, pSkillInfo, NULL, &_GCSkillToObjectOK2);
			}
			else
			{
				decreaseDurability(pMonster, pEnemy, pSkillInfo, NULL, &_GCSkillToObjectOK6);
			}

			_GCSkillToObjectOK2.setObjectID(pMonster->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
			_GCSkillToObjectOK2.setDuration(output.Duration);
											
			_GCSkillToObjectOK3.setObjectID(pMonster->getObjectID());
			_GCSkillToObjectOK3.setSkillType(SkillType);
			_GCSkillToObjectOK3.setTargetXY(targetX, targetY);
															
			_GCSkillToObjectOK4.setSkillType(SkillType);
			_GCSkillToObjectOK4.setTargetObjectID(pEnemy->getObjectID());

			_GCSkillToObjectOK5.setObjectID(pMonster->getObjectID());
			_GCSkillToObjectOK5.setTargetObjectID(pEnemy->getObjectID());
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setDuration(output.Duration);

			_GCSkillToObjectOK6.setXY(vampX, vampY);
			_GCSkillToObjectOK6.setSkillType(SkillType);
			_GCSkillToObjectOK6.setDuration(output.Duration);

			if (pEnemy->isPC())
			{
				Player* pTargetPlayer = pEnemy->getPlayer();
				if (pTargetPlayer == NULL)
				{
					//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
					return;
				}
				if (bCanSeeCaster) pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
				else pTargetPlayer->sendPacket(&_GCSkillToObjectOK6);
			}
			else
			{
				Monster* pTargetMonster = dynamic_cast<Monster*>(pEnemy);
				pTargetMonster->addEnemy(pMonster);
			}

			list<Creature*> cList;
			cList.push_back(pMonster);
			cList.push_back(pEnemy);

			cList = pZone->broadcastSkillPacket(vampX, vampY,
				targetX, targetY, &_GCSkillToObjectOK5, cList);

			pZone->broadcastPacket(vampX, vampY,  &_GCSkillToObjectOK3 , cList);
			pZone->broadcastPacket(targetX, targetY,  &_GCSkillToObjectOK4 , cList);
		} 
		else
		{
			executeSkillFailNormal(pMonster, getSkillType(), pEnemy);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

