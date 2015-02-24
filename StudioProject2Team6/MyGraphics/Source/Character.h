#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Item.h"
#include "DefineEnum.h"
#include <vector>
class CCharacter
{
public:
	CCharacter(void);
	CCharacter(float setMoney, int setAxis, int setItemsHeld, int setMaxItemCapacity, bool setInventoryOpened);
	~CCharacter(void);

	float getMoney();
	int getMaxItemCapacity();
	int getItemHeld();
	std::vector<CItem*> getVector();
	void setInventory(CItem* pickedUp);

private:
	std::vector<CItem*> myInventoryList;
	float money;
	int look_at_axis;
	int itemsHeld;
	int maxItemCapacity;
	bool inventoryIsOpened;
	float x;
	float y;
	float z;
	unsigned int characterState;
	unsigned int characterJob;
};

#endif

