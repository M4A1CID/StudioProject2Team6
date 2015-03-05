#include "Container.h"

/******************************************************************************/
/*!
\brief
Default container constructor
*/
/******************************************************************************/
CContainer::CContainer(void)
{
	name = "undefined";
	x = 0;
	y = 0;
	z = 0;
	rotation = 0;
	firstItemStock = -1;
	secondItemStock = -1;
	thirdItemStock = -1;
}
/******************************************************************************/
/*!
\brief
Overloaded container constructor

\param first - first item in container
\param second - second item in container
\param third - third item in container
\param n - name
\param firstStock - first item stock in container
\param secondStock - second item stock in container
\param thirdStock - third item stock in container
\param posX - x position of container
\param posY - y position of container
\param posZ - z position of container
\param rotate - rotation of container
*/
/******************************************************************************/
CContainer::CContainer(CItem first, CItem second, CItem third, string n, int firstStock, int secondStock, int thirdStock,float posX, float posY, float posZ, float rotate)
{
	x = posX;
	y = posY;
	z = posZ;
	item_first = first;
	item_second = second;
	item_third = third;
	name = n;
	rotation = rotate;
	firstItemStock = firstStock;
	secondItemStock = secondStock;
	thirdItemStock = thirdStock;
}
/******************************************************************************/
/*!
\brief
Overloaded container constructor

\param first - first item in container
\param second - second item in container
\param third - third item in container
\param n - name
\param firstStock - first item stock in container
\param secondStock - second item stock in container
\param thirdStock - third item stock in container
\param posX - x position of container
\param posY - y position of container
\param posZ - z position of container
\param rotate - rotation of container
*/
/******************************************************************************/
CContainer::CContainer(CItem* first, CItem* second, CItem* third, string n, int firstStock, int secondStock, int thirdStock,float posX, float posY, float posZ, float rotate)
{
	x = posX;
	y = posY;
	z = posZ;
	item_first = *first;
	item_second = *second;
	item_third = *third;
	name = n;
	rotation = rotate;
	firstItemStock = firstStock;
	secondItemStock = secondStock;
	thirdItemStock = thirdStock;
}

/******************************************************************************/
/*!
\brief
Default destructor
*/
/******************************************************************************/
CContainer::~CContainer(void)
{
}
/******************************************************************************/
/*!
\brief
Accessor function for first item stock in container

\return first item stock
*/
/******************************************************************************/
int CContainer::getFirstStock(void)
{
	return firstItemStock;
}
/******************************************************************************/
/*!
\brief
Accessor function for second item stock in container

\return second item stock
*/
/******************************************************************************/
int CContainer::getSecondStock(void)
{
	return secondItemStock;
}
/******************************************************************************/
/*!
\brief
Accessor function for third item stock in container

\return first third stock
*/
/******************************************************************************/
int CContainer::getThirdStock(void)
{
	return thirdItemStock;
}
/******************************************************************************/
/*!
\brief
Accessor function for container x position

\return container x position
*/
/******************************************************************************/
float CContainer::getXpos() 
{
	return x;	//Get X position of container
} 
/******************************************************************************/
/*!
\brief
Accessor function for container y position

\return container y position
*/
/******************************************************************************/
float CContainer::getYpos() 
{
	return y;	//Get Y position of container
} 
/******************************************************************************/
/*!
\brief
Accessor function for container z position

\return container z position
*/
/******************************************************************************/
float CContainer::getZpos()	
{
	return z;	//Get Z position of container
} 
/******************************************************************************/
/*!
\brief
Accessor function for container rotation

\return container rotation
*/
/******************************************************************************/
float CContainer::getRotation()
{
	return rotation;
}
/******************************************************************************/
/*!
\brief
Accessor function for container top row item

\return container top row item
*/
/******************************************************************************/
CItem CContainer::getTopItem()
{
	return item_first;
}
/******************************************************************************/
/*!
\brief
Accessor function for container middle row item

\return container middle row item
*/
/******************************************************************************/
CItem CContainer::getMiddleItem()
{
	return item_second;
}
/******************************************************************************/
/*!
\brief
Accessor function for container botttom row item

\return container bottom row item
*/
/******************************************************************************/
CItem CContainer::getBottomItem()
{
	return item_third;
}
/******************************************************************************/
/*!
\brief
Mutator function to set rotation of container

\param r - roation of container
*/
/******************************************************************************/
void CContainer::setRotation(float r)
{
	rotation = r;
}
/******************************************************************************/
/*!
\brief
Mutator function to set all items in container

\param a - set first item in container
\param b - set second item in container
\param c - set third item in container
*/
/******************************************************************************/
void CContainer::setItems(CItem a,CItem b,CItem c)
{
	item_first = a;	//Set first item
	item_second = b;//Set second item
	item_third = c;	//Set third item
}
/******************************************************************************/
/*!
\brief
Mutator function to set container position

\param posX - set x position of container
\param posY - set y position of container
\param posZ - set z position of container
*/
/******************************************************************************/
void CContainer::setPosition(float posX, float posY, float posZ)
{
	x = posX;	//Set X
	y = posY;	//Set Y
	z = posZ;	//Set Z
}
/******************************************************************************/
/*!
\brief
Mutator function to set the stock of all items in container

\param a - set stock of first item in container
\param b - set stock of second item in container
\param c - set stock of third item in container
*/
/******************************************************************************/
void CContainer::setItemStock(int a, int b, int c)
{
	firstItemStock = a;
	secondItemStock = b;
	thirdItemStock = c;
}
