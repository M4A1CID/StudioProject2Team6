#include "Item.h"

CItem::CItem(void)
{
	name = "undefined";
	price = -1.00;
	objectType = -1;
}
CItem::CItem(string n, float p, int type, float posX, float posY, float posZ)
{
	name = n;
	price = p;
	objectType = type;
	x = posX;
	y = posY;
	z = posZ;
}


CItem::~CItem(void)
{
}
void CItem::setName(string n)
{
	name = n;
}
void CItem::setPrice(float p)
{
	price = p;
}
void CItem::setGeoType(int type)
{
	objectType = type;
}
int CItem::getGeoType()
{
	return objectType;
}
void CItem::setXpos(float posX)
{
	x = posX;
}
void CItem::setYpos(float posY)
{
	y = posY;
}
void CItem::setZpos(float posZ)
{
	z = posZ;
}
float CItem::getXpos()
{
	return x;
}
float CItem::getYpos()
{
	return y;
}
float CItem::getZpos()
{
	return z;
}
string CItem::getName()
{
	return name;
}
float CItem::getPrice()
{
	return price;
}