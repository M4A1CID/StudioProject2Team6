#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Item.h"
#include "DefineEnum.h"
#include <vector>
/******************************************************************************/
/*!
		Class Character:
\brief	Defines the character class
*/
/******************************************************************************/
class CCharacter
{
public:
	CCharacter(void);
	CCharacter(float posX, float posY, float posZ, int state, int job);
	~CCharacter(void);
	int getCharacterState();
	int getAnimationType();
	float getXpos();
	float getYpos();
	float getZpos();
	int getCharacterJob();
	void setCharacterJob(int jobNum);
	void setCharacterState(int state);
	void setAnimationType(int type);
	void setXpos(float posX);
	void setYpos(float posY);
	void setZpos(float posZ);
	

private:
	
	float x;
	float y;
	float z;
	unsigned int characterState;
	unsigned int characterJob;
	unsigned int animationType;
};

#endif

