#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <string>

using std::string;
class CItem
{
public:
	CItem(void);
	CItem(string n, float p);
	void setName(string n);
	void setPrice(float p);
	~CItem(void);

private:
	string name;
	float price;
};

#endif

