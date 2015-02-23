#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Item.h"
class CCharacter
{
public:
	CCharacter(void);
	CCharacter(float setMoney, int setAxis, int setItemsHeld, int setMaxItemCapacity, bool setInventoryOpened);
	~CCharacter(void);

	float getMoney();

private:
	CItem inventory_first;
	CItem inventory_second;
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

