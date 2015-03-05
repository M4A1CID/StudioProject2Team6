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
/******************************************************************************/
/*!
\brief
Accessor function for head type

\return npc head type
*/
/******************************************************************************/
int CNpc::getHeadType()
{
	return GeoHeadType;
}
/******************************************************************************/
/*!
\brief
Accessor function for leg type

\return npc leg type
*/
/******************************************************************************/
int CNpc::getLegType()
{
	return GeoLegType;
}
/******************************************************************************/
/*!
\brief
Accessor function for left arm roation

\return npc left arm roation
*/
/******************************************************************************/
float CNpc::getLeftArm()
{
	return rotateLeftArm;
}
/******************************************************************************/
/*!
\brief
Accessor function for right arm roation

\return npc right arm roation
*/
/******************************************************************************/
float CNpc::getRightArm()
{
	return rotateRightArm;
}
/******************************************************************************/
/*!
\brief
Accessor function for left leg roation

\return npc left leg roation
*/
/******************************************************************************/
float CNpc::getLeftLeg()
{
	return rotateLeftLeg;
}
/******************************************************************************/
/*!
\brief
Accessor function for right leg roation

\return npc right leg roation
*/
/******************************************************************************/
float CNpc::getRightLeg()
{
	return rotateRightLeg;
}
/******************************************************************************/
/*!
\brief
Accessor function for npc y rotation

\return npc y rotation
*/
/******************************************************************************/
float CNpc::getYRotation()
{
	return Yrotation;
}
/******************************************************************************/
/*!
\brief
Accessor function for npc x rotation

\return npc x rotation
*/
/******************************************************************************/
float CNpc::getXRotation()
{
	return Xrotation;
}
/******************************************************************************/
/*!
\brief
Accessor function for npc z rotation

\return npc z rotation
*/
/******************************************************************************/
float CNpc::getZRotation()
{
	return Zrotation;
}
/******************************************************************************/
/*!
\brief
Accessor function for npc move speed

\return npc move speed
*/
/******************************************************************************/
float CNpc::getmoveSpd()
{
	return moveSpd;
}
/******************************************************************************/
/*!
\brief
Accessor function for npc interaction timer

\return npc interaction timer
*/
/******************************************************************************/
float CNpc::getNPCTimer()
{
	return NPCTimer;
}
/******************************************************************************/
/*!
\brief
Accessor function for npc active state

\return npc active state
*/
/******************************************************************************/
bool CNpc::getActive()
{
	return IsActive;
}
/******************************************************************************/
/*!
\brief
Accessor function for npc leg rotation direction

\return npc leg rotation direction
*/
/******************************************************************************/
bool CNpc::getlegRotDir()
{
	return legRotDir;
}

/******************************************************************************/
/*!
\brief
Mutator function to set rotation of left npc arm

\param r - rotation of left npc arm
*/
/******************************************************************************/
void CNpc::setLeftArm(float r)
{
	rotateLeftArm = r;
}
/******************************************************************************/
/*!
\brief
Mutator function to set rotation of right npc arm

\param r - rotation of right npc arm
*/
/******************************************************************************/
void CNpc::setRightArm(float r)
{
	rotateRightArm = r;
}
/******************************************************************************/
/*!
\brief
Mutator function to set rotation of left npc leg

\param r - rotation of left npc leg
*/
/******************************************************************************/
void CNpc::setLeftLeg(float r)
{
	rotateLeftLeg = r;
}
/******************************************************************************/
/*!
\brief
Mutator function to set rotation of right npc leg

\param r - rotation of right npc leg
*/
/******************************************************************************/
void CNpc::setRightLeg(float r)
{
	rotateRightLeg = r;
}
/******************************************************************************/
/*!
\brief
Mutator function to set y rotation of npc

\param r - Y rotation of npc
*/
/******************************************************************************/
void CNpc::setYRotation(float r)
{
	Yrotation = r;
}
/******************************************************************************/
/*!
\brief
Mutator function to set x rotation of npc

\param r - X rotation of npc
*/
/******************************************************************************/
void CNpc::setXRotation(float r)
{
	Xrotation = r;
}
/******************************************************************************/
/*!
\brief
Mutator function to set z rotation of npc

\param r - Z rotation of npc
*/
/******************************************************************************/
void CNpc::setZRotation(float r)
{
	Zrotation = r;
}
/******************************************************************************/
/*!
\brief
Mutator function to set the movement speed of npc

\param r - move speed of npc
*/
/******************************************************************************/
void CNpc::setmoveSpd(float r)
{
	moveSpd = r;
}
/******************************************************************************/
/*!
\brief
Mutator function to set the interaction of the npc

\param timer -  interaction of npc
*/
/******************************************************************************/
void CNpc::setNPCTimer(float timer)
{
	NPCTimer = timer;
}
/******************************************************************************/
/*!
\brief
Mutator function to set the active state of the npc

\param active -  active state of npc
*/
/******************************************************************************/
void CNpc::setActive(bool active)
{
	IsActive = active;
}
/******************************************************************************/
/*!
\brief
Mutator function to set the leg roation direction of the npc

\param dir -  leg roation direction of npc
*/
/******************************************************************************/
void CNpc::setlegRotDir(bool dir)
{
	legRotDir = dir;
}