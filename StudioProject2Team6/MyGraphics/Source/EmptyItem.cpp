/******************************************************************************/
/*!
\file	EmptyItem.cpp
\author Edmund Ang
\brief
 File for EmptyItem item
*/
/******************************************************************************/
#include "EmptyItem.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
CEmptyItem::CEmptyItem(void)
{
	setName("Empty");
	setPrice(0.0f);
	setGeoType(0);
}

/******************************************************************************/
/*!
\brief
Default destructor
*/
/******************************************************************************/
CEmptyItem::~CEmptyItem(void)
{
}
