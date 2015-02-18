#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <string>

using std::string;
class CItem
{
public:
	CItem(void);
	CItem(string n, float p, int type);
	void setName(string n);
	void setPrice(float p);
	void setGeoType(int type);
	int getGeoType();
	~CItem(void);

private:
	string name;
	float price;
	int objectType;
};

#endif

