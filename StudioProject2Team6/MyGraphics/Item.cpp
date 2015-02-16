#include "Item.h"

CItem::CItem(void)
{
	name = "undefined";
	price = -1.00;
}
CItem::CItem(string n, double p)
{
	name = n;
	price = p;
}


CItem::~CItem(void)
{
}
