#pragma once
#include "Character.h"
class CPlayer : public CCharacter
{
private:
	
	int itemsHeld;
	int maxItemCapacity;
	float money;
	std::vector<CItem*> myInventoryList;


public:
	CPlayer(void);
	CPlayer(float setMoney, int setItemsHeld, int setMaxItemCapacity);
	~CPlayer(void);

	float getMoney();
	int getMaxItemCapacity();
	int getItemHeld();
	std::vector<CItem*> getVector();
	void setInventory(CItem* pickedUp);
	void setInventory(CItem* pickedUp, int slot);
	void setMoney(float newMoney);
	CItem* getItem(int i);

};

