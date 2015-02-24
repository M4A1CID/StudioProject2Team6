#include "Npc.h"


CNpc::CNpc(void)
{

}
CNpc::CNpc(float posX, float posY, float posZ, int head, int arm, int leg, int state, int job)
{
	setXpos(posX);
	setYpos(posY);
	setZpos(posZ);
	GeoHeadType = head;
	GeoArmType = arm;
	GeoLegType = leg;
	setCharacterJob(job);
	setCharacterState(state);

	rotateLeftArm = 90.f;
	rotateRightArm = 270.f;
	rotateLeftLeg = 0.f;
	rotateRightLeg = 0.f;
}


CNpc::~CNpc(void)
{
}

int CNpc::getArmType()
{
	return GeoArmType;
}
int CNpc::getHeadType()
{
	return GeoHeadType;
}
int CNpc::getLegType()
{
	return GeoLegType;
}
float CNpc::getLeftArm()
{
	return rotateLeftArm;
}
float CNpc::getRightArm()
{
	return rotateRightArm;
}
float CNpc::getLeftLeg()
{
	return rotateLeftLeg;
}
float CNpc::getRightLeg()
{
	return rotateRightLeg;
}

void CNpc::setLeftArm(float r)
{
	rotateLeftArm = r;
}
void CNpc::setRightArm(float r)
{
	rotateRightArm = r;
}
void CNpc::setLeftLeg(float r)
{
	rotateLeftLeg = r;
}
void CNpc::setRightLeg(float r)
{
	rotateRightLeg = r;
}