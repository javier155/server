//----------------------------------------------------------------------
//
// Filename    : PCCorpse.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

#ifndef __PC_CORPSE_H__
#define __PC_CORPSE_H__

// include files
#include "Corpse.h"

//----------------------------------------------------------------------
// 크리처의 인벤토리에서 아이템을 꺼내서, 시체에 집어넣는다.
//----------------------------------------------------------------------
void PCCorpse::transportItems (Creature* pCreature) 
	throw (Error)
{
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string PCCorpse::toString () const 
	throw ()
{
	StringStream msg;

	msg << "PCCorpse()";

	return msg.toString();
}

