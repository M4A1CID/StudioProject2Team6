#pragma once
#include "Character.h"
class CNpc : public CCharacter
{
public:
	CNpc(void);
	CNpc(float posX, float posY, float posZ, int head, int arm, int leg, int state,int type, int job);
	~CNpc(void);

	int getHeadType();
	int getLegType();
	int getArmType();

	float getRotation();
	float getLeftArm();
	float getRightArm();
	float getLeftLeg();
	float getRightLeg();
	float getmoveSpd();
	bool getActive();

	void setRotation(float r);
	void setLeftArm(float r);
	void setRightArm(float r);
	void setLeftLeg(float r);
	void setRightLeg(float r);
	void setmoveSpd(float r);
	void setActive(bool active);

private:
	int GeoHeadType;
	int GeoArmType;
	int GeoLegType;
	float rotation;
	float rotateLeftArm;
	float rotateRightArm;
	float rotateLeftLeg;
	float rotateRightLeg;
	float moveSpd;
	bool IsActive;
};

