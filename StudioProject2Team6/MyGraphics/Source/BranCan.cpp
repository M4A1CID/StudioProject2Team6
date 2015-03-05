/******************************************************************************/
/*!
\file	BranCan.cpp
\author Edmund Ang, Jeffrey Teo
\brief
File for Bran Can item
*/
/******************************************************************************/
#include "BranCan.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
CBranCan::CBranCan(void)
{
	setName("Bran Can");
	setPrice(3.0f);
	setGeoType(GEO_CAN_BRAN);
}

/******************************************************************************/
/*!
\brief
Default destructor
*/
/******************************************************************************/
CBranCan::~CBranCan(void)
{
}
