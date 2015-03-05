#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <string>
/******************************************************************************/
/*!
		Class Item:
\brief	Defines item class
*/
/******************************************************************************/
using std::string;
class CItem
{
public:
	CItem(void);
	CItem(string n, float p, int type, float posX, float posY, float posZ);
	void setName(string n);
	void setPrice(float p);
	void setGeoType(int type);
	void setXpos(float posX);
	void setYpos(float posY);
	void setZpos(float posZ);
	void setActiveState(bool setActive);
	bool getActiveState();
	float getXpos();
	float getYpos();
	float getZpos();
	string getName();
	int getGeoType();
	float getPrice();
	~CItem(void);

private:
	string name;
	float price;
	int objectType;
	float x;
	float y;
	float z;
	bool active;
};

#endif

