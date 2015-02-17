#include "Item.h"

CItem::CItem(void)
{
	name = "undefined";
	price = -1.00;
}
CItem::CItem(string n, float p)
{
	name = n;
	price = p;
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