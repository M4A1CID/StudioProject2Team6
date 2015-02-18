#include "Item.h"

CItem::CItem(void)
{
	name = "undefined";
	price = -1.00;
	objectType = -1;
}
CItem::CItem(string n, float p, int type)
{
	name = n;
	price = p;
	objectType = type;
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