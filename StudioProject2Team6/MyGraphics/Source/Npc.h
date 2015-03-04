#pragma once
#include "Character.h"
class CNpc : public CCharacter
{
public:
	CNpc(void);
	CNpc(float posX, float posY, float posZ, int head, int arm, int leg, int state,int type, int job,bool active);
	~CNpc(void);

	int getHeadType();
	int getLegType();
	int getArmType();

	float getYRotation();
	float getXRotation();
	float getZRotation();
	float getLeftArm();
	float getRightArm();
	float getLeftLeg();
	float getRightLeg();
	float getmoveSpd();
	float getNPCTimer();
	bool getActive();
	bool getlegRotDir();

	void setYRotation(float r);
	void setXRotation(float r);
	void setZRotation(float r);
	void setLeftArm(float r);
	void setRightArm(float r);
	void setLeftLeg(float r);
	void setRightLeg(float r);
	void setmoveSpd(float r);
	void setActive(bool active);
	void setlegRotDir(bool dir);
	void setNPCTimer(float timer);

private:
	int GeoHeadType;
	int GeoArmType;
	int GeoLegType;
	float Yrotation;
	float Xrotation;
	float Zrotation;
	float rotateLeftArm;
	float rotateRightArm;
	float rotateLeftLeg;
	float rotateRightLeg;
	float moveSpd;
	float NPCTimer;
	bool IsActive;
	bool legRotDir;
};
