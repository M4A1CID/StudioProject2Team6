/******************************************************************************/
/*!
\file	RedMonsterCan.cpp
\author Edmund Ang, Jeffrey Teo
\brief
File for RedMonsterCan item
*/
/******************************************************************************/
#include "RedMonsterCan.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
CRedMonsterCan::CRedMonsterCan(void)
{
		setName("RedMonster Can");
	setPrice(2.0f);
	setGeoType(GEO_CAN_REDMONSTER);
}

/******************************************************************************/
/*!
\brief
Default destructor
*/
/******************************************************************************/
CRedMonsterCan::~CRedMonsterCan(void)
{
}
