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