/**
*	created:		2012-6-30   1:06
*	filename: 		IMonster
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "ICreature.h"
//------------------------------------------------------------------------
// 接口定义
struct IMonster : public ICreature
{
	// 取得怪物ID
	virtual DWORD			GetMonsterID(void) = NULL;
};
//------------------------------------------------------------------------