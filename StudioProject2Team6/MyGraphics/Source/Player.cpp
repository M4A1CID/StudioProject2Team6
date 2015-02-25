#include "Player.h"


CPlayer::CPlayer(void)
{
	money = -1.0f;
	itemsHeld = 0;
	maxItemCapacity = 8;
	setCharacterState(IDLE);
}
CPlayer::CPlayer(float setMoney, int setItemsHeld, int setMaxItemCapacity)
{
	money = setMoney;
	itemsHeld = setItemsHeld;
	maxItemCapacity = setMaxItemCapacity;
	setCharacterState(IDLE);
}


CPlayer::~CPlayer(void)
{
}
CItem* CPlayer::getItem(int i)
{
	return myInventoryList[i];
}
float CPlayer::getMoney()
{
	return money;
}
int CPlayer::getItemHeld()
{
	return myInventoryList.size();
}
int CPlayer::getMaxItemCapacity()
{
	return maxItemCapacity;
}
void CPlayer::setInventory(CItem* pickedUp)
{
	myInventoryList.push_back(pickedUp);
}
void CPlayer::setInventory(CItem* pickedUp, int slot)
{
	myInventoryList[slot] = pickedUp;
}
std::vector<CItem*> CPlayer::getVector()
{
	return myInventoryList;
}