#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H
#include "Item.h"

class CContainer
{
public:
	CContainer(void);
	CContainer(CItem first, CItem second, CItem third, string n, int firstStock, int secondStock, int thirdStock);
	int getFirstStock();
	int getSecondStock();
	int getThirdStock();
	~CContainer(void);

private:
	CItem item_first;
	CItem item_second;
	CItem item_third;

	string name;

	int firstItemStock;
	int secondItemStock;
	int thirdItemStock;
};

#endif

