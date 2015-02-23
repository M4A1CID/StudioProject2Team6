#include "Character.h"
CCharacter::CCharacter(void)
{
	money = -1.0f;
	look_at_axis = 0;
	itemsHeld = 0;
	maxItemCapacity = 10;
	inventoryIsOpened = false;
}
CCharacter::CCharacter(float setMoney, int setAxis, int setItemsHeld, int setMaxItemCapacity, bool setInventoryOpened)
{
	money = setMoney;
	look_at_axis = setAxis;
	itemsHeld = setItemsHeld;
	maxItemCapacity = setMaxItemCapacity;
	inventoryIsOpened = setInventoryOpened;
}

CCharacter::~CCharacter(void)
{
}

float CCharacter::getMoney()
{
	return money;
}