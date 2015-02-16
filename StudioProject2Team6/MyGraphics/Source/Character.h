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
	CItem inventory1;
	float money;
	int look_at_axis;
	int itemsHeld;
	int maxItemCapacity;
	bool inventoryIsOpened;
};

#endif

