#include "Character.h"
CCharacter::CCharacter(void)
{
	money = -1.0f;
	look_at_axis = 0;
	itemsHeld = 0;
	maxItemCapacity = 8;
	inventoryIsOpened = false;
	characterState = IDLE;
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
int CCharacter::getItemHeld()
{
	return myInventoryList.size();
}
int CCharacter::getMaxItemCapacity()
{
	return maxItemCapacity;
}
void CCharacter::setInventory(CItem* pickedUp)
{
	myInventoryList.push_back(pickedUp);
}
std::vector<CItem*> CCharacter::getVector()
{
	return myInventoryList;
}