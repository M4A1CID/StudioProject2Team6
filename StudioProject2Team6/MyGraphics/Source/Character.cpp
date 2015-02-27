#include "Character.h"
CCharacter::CCharacter(void)
{

}
CCharacter::CCharacter(float posX, float posY, float posZ, int state, int job)
{
	x = posX;
	y = posY;
	z = posZ;
	characterState = state;
	characterJob = job;
}

CCharacter::~CCharacter(void)
{
}
int CCharacter::getCharacterJob()
{
	return characterJob;
}
int CCharacter::getCharacterState()
{
	return characterState;
}
float CCharacter::getXpos()
{
	return x;
}
float CCharacter::getYpos()
{
	return y;
}
float CCharacter::getZpos()
{
	return z;
}
void CCharacter::setXpos(float posX)
{
	x = posX;
}
void CCharacter::setYpos(float posY)
{
	y = posY;
}
void CCharacter::setZpos(float posZ)
{
	z = posZ;
}
void CCharacter::setCharacterState(int state)
{
	characterState = state;
}
void CCharacter::setCharacterJob(int jobNum)
{
	characterJob = jobNum;
}
