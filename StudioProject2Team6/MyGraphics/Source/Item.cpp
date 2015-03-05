/******************************************************************************/
/*!
\file	Item.cpp
\author Edmund Ang
\brief
File for Item class
*/
/******************************************************************************/
#include "Item.h"
/******************************************************************************/
/*!
\brief
Default item constructor
*/
/******************************************************************************/
CItem::CItem(void)
{
	name = "undefined";
	price = -1.00;
	objectType = -1;
}
/******************************************************************************/
/*!
\brief
Overloaded item constructor

\param n - name of item
\param p - price of item
\param type - type of item
\param posX - x position of item
\param posY - y position of item
\param posZ - z position of item
*/
/******************************************************************************/
CItem::CItem(string n, float p, int type, float posX, float posY, float posZ)
{
	name = n;
	price = p;
	objectType = type;
	x = posX;
	y = posY;
	z = posZ;
	active = true;
}

/******************************************************************************/
/*!
\brief
Default destructor
*/
/******************************************************************************/
CItem::~CItem(void)
{
}
/******************************************************************************/
/*!
\brief
Mutator function to set the item name

\param n - set item name
*/
/******************************************************************************/
void CItem::setName(string n)
{
	name = n;
}
/******************************************************************************/
/*!
\brief
Mutator function to set the item price

\param n - set item price
*/
/******************************************************************************/
void CItem::setPrice(float p)
{
	price = p;
}
/******************************************************************************/
/*!
\brief
Mutator function to set the item geometry type

\param type - set item geometry type
*/
/******************************************************************************/
void CItem::setGeoType(int type)
{
	objectType = type;
}
/******************************************************************************/
/*!
\brief
Mutator function to set the active state of the item

\param setActive - set active state of item
*/
/******************************************************************************/
void CItem::setActiveState(bool setActive)
{
	active = setActive;
}
/******************************************************************************/
/*!
\brief
Mutator function to set the x position of the item

\param posX - set item X position
*/
/******************************************************************************/
void CItem::setXpos(float posX)
{
	x = posX;
}
/******************************************************************************/
/*!
\brief
Mutator function to set the y position of the item

\param posX - set item Y position
*/
/******************************************************************************/
void CItem::setYpos(float posY)
{
	y = posY;
}
/******************************************************************************/
/*!
\brief
Mutator function to set the z position of the item

\param posX - set item Z position
*/
/******************************************************************************/
void CItem::setZpos(float posZ)
{
	z = posZ;
}
/******************************************************************************/
/*!
\brief
Accessor function for item active state

\return item active state
*/
/******************************************************************************/
bool CItem::getActiveState()
{
	return active;
}
/******************************************************************************/
/*!
\brief
Accessor function for item geometry type

\return item geometry type
*/
/******************************************************************************/
int CItem::getGeoType()
{
	return objectType;
}
/******************************************************************************/
/*!
\brief
Accessor function for item x position

\return item X position
*/
/******************************************************************************/
float CItem::getXpos()
{
	return x;
}
/******************************************************************************/
/*!
\brief
Accessor function for item y position

\return item Yposition
*/
/******************************************************************************/
float CItem::getYpos()
{
	return y;
}
/******************************************************************************/
/*!
\brief
Accessor function for item Zposition

\return item Z position
*/
/******************************************************************************/
float CItem::getZpos()
{
	return z;
}
/******************************************************************************/
/*!
\brief
Accessor function for item name

\return item name
*/
/******************************************************************************/
string CItem::getName()
{
	return name;
}
/******************************************************************************/
/*!
\brief
Accessor function for item price

\return item price
*/
/******************************************************************************/
float CItem::getPrice()
{
	return price;
}