/******************************************************************************/
/*!
\file	Player.cpp
\author Edmund Ang
\brief
File for Player class
*/
/******************************************************************************/
#include "Player.h"

/******************************************************************************/
/*!
\brief
Default player constructor
*/
/******************************************************************************/
CPlayer::CPlayer(void)
{
	money = -1.0f;
	itemsHeld = 0;
	maxItemCapacity = 8;
	setCharacterState(IDLE);
}
/******************************************************************************/
/*!
\brief
Overloaded player constructor

\param setMoney - sets the players money
\param setItemsHeld - sets the number of items held by the players
\param setMaxItemCapacity - sets the max item capacity of the player
*/
/******************************************************************************/
CPlayer::CPlayer(float setMoney, int setItemsHeld, int setMaxItemCapacity)
{
	money = setMoney;
	itemsHeld = setItemsHeld;
	maxItemCapacity = setMaxItemCapacity;
	setCharacterState(IDLE);
}

/******************************************************************************/
/*!
\brief
Default destructor
*/
/******************************************************************************/
CPlayer::~CPlayer(void)
{
}
/******************************************************************************/
/*!
\brief
Accessor function for the items held by the player

\return item held
*/
/******************************************************************************/
CItem* CPlayer::getItem(int i)
{
	return myInventoryList[i];
}
/******************************************************************************/
/*!
\brief
Accessor function for the amount of money the player has

\return player's money
*/
/******************************************************************************/
float CPlayer::getMoney()
{
	return money;
}
/******************************************************************************/
/*!
\brief
Accessor function for the number of items the player is holding

\return number of items held
*/
/******************************************************************************/
int CPlayer::getItemHeld()
{
	return myInventoryList.size();
}
/******************************************************************************/
/*!
\brief
Accessor function for the max amount of items the player can have

\return max item capacity
*/
/******************************************************************************/
int CPlayer::getMaxItemCapacity()
{
	return maxItemCapacity;
}
/******************************************************************************/
/*!
\brief
Mutator function to add an item picked up by the player

\param pickedUp - adds the item picked up
*/
/******************************************************************************/
void CPlayer::setInventory(CItem* pickedUp)
{
	myInventoryList.push_back(pickedUp);
}
/******************************************************************************/
/*!
\brief
Mutator function to add an item picked up by the player to a specific inventory slot

\param pickedUp - adds the item picked up
\param slot - the inventory slot to add the item to
*/
/******************************************************************************/
void CPlayer::setInventory(CItem* pickedUp, int slot)
{
	myInventoryList[slot] = pickedUp;
}

std::vector<CItem*> CPlayer::getVector()
{
	return myInventoryList;
}
/******************************************************************************/
/*!
\brief
Mutator function to set the players current money

\param newMoney - the players new amount of money
*/
/******************************************************************************/
void CPlayer::setMoney(float newMoney)
{
	money = newMoney;
}