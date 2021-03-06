/******************************************************************************/
/*!
\file	SodaCan.cpp
\author Edmund Ang, Jeffrey Teo
\brief
File for SodaCan item
*/
/******************************************************************************/
#include "SodaCan.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
CSodaCan::CSodaCan(void)
{
	setName("Soda Can");
	setPrice(2.0f);
	setGeoType(GEO_CAN_SODA);
}

/******************************************************************************/
/*!
\brief
Default destructor
*/
/******************************************************************************/
CSodaCan::~CSodaCan(void)
{
}
