#include "Npc.h"

/******************************************************************************/
/*!
\brief
Default NPC constructor
*/
/******************************************************************************/
CNpc::CNpc(void)
{

}
/******************************************************************************/
/*!
\brief
Overloaded NPC constructor

\param posX - X position of npc
\param posY - Y position of npc
\param posZ - Z position of npc
\param head - npc head type
\param arm - npc arm type
\param leg - npc leg type
\param state - npc character state
\param type - npc animation type
\param job - npc job
\param active - npc active state
*/
/******************************************************************************/
CNpc::CNpc(float posX, float posY, float posZ, int head, int arm, int leg, int state, int type, int job,bool active)
{
	setXpos(posX);
	setYpos(posY);
	setZpos(posZ);
	GeoHeadType = head;
	GeoArmType = arm;
	GeoLegType = leg;
	setCharacterJob(job);
	setCharacterState(state);
	setAnimationType(type);

	Yrotation = 0.0f;
	Xrotation = 0.0f;
	Zrotation = 0.0f;
	rotateLeftArm = 90.f;
	rotateRightArm = 270.f;
	rotateLeftLeg = 0.f;
	rotateRightLeg = 0.f;
	moveSpd = 5.0f;
	NPCTimer = 0.0f;
	IsActive = active;
	legRotDir = false;
}

/******************************************************************************/
/*!
\brief
Default destructor
*/
/******************************************************************************/
CNpc::~CNpc(void)
{
}
/******************************************************************************/
/*!
\brief
Accessor function for arm type

\return npc arm type
*/
/******************************************************************************/
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
float CNpc::getYRotation()
{
	return Yrotation;
}
float CNpc::getXRotation()
{
	return Xrotation;
}
float CNpc::getZRotation()
{
	return Zrotation;
}
float CNpc::getmoveSpd()
{
	return moveSpd;
}
float CNpc::getNPCTimer()
{
	return NPCTimer;
}
bool CNpc::getActive()
{
	return IsActive;
}
bool CNpc::getlegRotDir()
{
	return legRotDir;
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
void CNpc::setYRotation(float r)
{
	Yrotation = r;
}
void CNpc::setXRotation(float r)
{
	Xrotation = r;
}
void CNpc::setZRotation(float r)
{
	Zrotation = r;
}
void CNpc::setmoveSpd(float r)
{
	moveSpd = r;
}
void CNpc::setNPCTimer(float timer)
{
	NPCTimer = timer;
}
void CNpc::setActive(bool active)
{
	IsActive = active;
}
void CNpc::setlegRotDir(bool dir)
{
	legRotDir = dir;
}