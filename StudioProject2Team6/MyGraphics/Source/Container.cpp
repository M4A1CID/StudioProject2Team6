#include "Container.h"


CContainer::CContainer(void)
{
	name = "undefined";
	firstItemStock = -1;
	secondItemStock = -1;
	thirdItemStock = -1;
}
CContainer::CContainer(CItem first, CItem second, CItem third, string n, int firstStock, int secondStock, int thirdStock)
{
	item_first = first;
	item_second = second;
	item_third = third;
	name = n;
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