#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H
#include "Item.h"

class CContainer
{
public:
	CContainer(void);
	CContainer(CItem first, CItem second, CItem third, string n, int firstStock, int secondStock, int thirdStock,float posX, float posY, float posZ, float rotate);
	CContainer(CItem* first, CItem* second, CItem* third, string n, int firstStock, int secondStock, int thirdStock,float posX, float posY, float posZ, float rotate);
	~CContainer(void);
	int getFirstStock();
	int getSecondStock();
	int getThirdStock();
	void setItems(CItem a,CItem b,CItem c);
	float getXpos();
	float getYpos();
	float getZpos();
	float getRotation();
	CItem getTopItem();
	CItem getMiddleItem();
	CItem getBottomItem();
	void setPosition(float posX, float posY, float posZ);
	void setItemStock(int a, int b, int c);
	void setRotation(float r);

private:
	CItem item_first;
	CItem item_second;
	CItem item_third;

	float x;
	float y;
	float z;
	float rotation;
	string name;

	int firstItemStock;
	int secondItemStock;
	int thirdItemStock;
};

#endif

