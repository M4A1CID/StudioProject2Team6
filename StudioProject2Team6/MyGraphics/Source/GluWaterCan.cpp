/******************************************************************************/
/*!
\file	GluWaterCan.cpp
\author Edmund Ang, Jeffrey Teo
\brief
File for GluWaterCan item
*/
/******************************************************************************/
#include "GluWaterCan.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
CGluWaterCan::CGluWaterCan(void)
{
	setName("GluWater Can");
	setPrice(2.0f);
	setGeoType(GEO_CAN_GLUWATER);
}

/******************************************************************************/
/*!
\brief
Default destructor
*/
/******************************************************************************/
CGluWaterCan::~CGluWaterCan(void)
{
}
