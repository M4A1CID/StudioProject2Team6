/******************************************************************************/
/*!
\file	SodaFestCan.cpp
\author Edmund Ang, Jeffrey Teo
\brief
File for SodaFestCan item
*/
/******************************************************************************/
#include "SodaFestCan.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
CSodaFestCan::CSodaFestCan(void)
{
	setName("SodaFest Can");
	setPrice(2.0f);
	setGeoType(GEO_CAN_SODAFEST);
}

/******************************************************************************/
/*!
\brief
Default destructor
*/
/******************************************************************************/
CSodaFestCan::~CSodaFestCan(void)
{
}
