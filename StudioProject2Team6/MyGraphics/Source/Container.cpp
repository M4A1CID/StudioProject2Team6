#include "Container.h"


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


CContainer::~CContainer(void)
{
}
int CContainer::getFirstStock(void)
{
	return firstItemStock;
}
int CContainer::getSecondStock(void)
{
	return secondItemStock;
}
int CContainer::getThirdStock(void)
{
	return thirdItemStock;
}
float CContainer::getXpos() 
{
	return x;	//Get X position of container
} 
float CContainer::getYpos() 
{
	return y;	//Get Y position of container
} 
float CContainer::getZpos()	
{
	return z;	//Get Z position of container
} 
float CContainer::getRotation()
{
	return rotation;
}
CItem CContainer::getTopItem()
{
	return item_first;
}
CItem CContainer::getMiddleItem()
{
	return item_second;
}
CItem CContainer::getBottomItem()
{
	return item_third;
}
void CContainer::setRotation(float r)
{
	rotation = r;
}
void CContainer::setItems(CItem a,CItem b,CItem c)
{
	item_first = a;	//Set first item
	item_second = b;//Set second item
	item_third = c;	//Set third item
}
void CContainer::setPosition(float posX, float posY, float posZ)
{
	x = posX;	//Set X
	y = posY;	//Set Y
	z = posZ;	//Set Z
}
void CContainer::setItemStock(int a, int b, int c)
{
	firstItemStock = a;
	secondItemStock = b;
	thirdItemStock = c;
}
