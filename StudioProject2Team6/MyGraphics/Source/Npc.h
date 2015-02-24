#pragma once
#include "Character.h"
class CNpc : public CCharacter
{
public:
	CNpc(void);
	CNpc(float posX, float posY, float posZ, int head, int arm, int leg, int state, int job);
	~CNpc(void);

	int getHeadType();
	int getLegType();
	int getArmType();

private:
	int GeoHeadType;
	int GeoArmType;
	int GeoLegType;
};

