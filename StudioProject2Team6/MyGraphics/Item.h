#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <string>

using std::string;
class CItem
{
public:
	CItem(void);
	CItem(string n, double p);
	~CItem(void);

private:
	string name;
	double price;
};

#endif

