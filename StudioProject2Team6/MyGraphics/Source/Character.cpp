#include "Character.h"
/******************************************************************************/
/*!
\brief
Default character constructor
*/
/******************************************************************************/
CCharacter::CCharacter(void)
{

}
/******************************************************************************/
/*!
\brief
Overloaded character constructor

\param posX - X position of character
\param posY - Y position of character
\param posZ - Z position of character
\param state - character state
\param job - character job
*/
/******************************************************************************/
CCharacter::CCharacter(float posX, float posY, float posZ, int state, int job)
{
	x = posX;
	y = posY;
	z = posZ;
	characterState = state;
	characterJob = job;
}
/******************************************************************************/
/*!
\brief
Default destructor
*/
/******************************************************************************/
CCharacter::~CCharacter(void)
{
}
/******************************************************************************/
/*!
\brief
Accessor function for character job

\return character job
*/
/******************************************************************************/
int CCharacter::getCharacterJob()
{
	return characterJob;
}
/******************************************************************************/
/*!
\brief
Accessor function for character state

\return character state
*/
/******************************************************************************/
int CCharacter::getCharacterState()
{
	return characterState;
}
/******************************************************************************/
/*!
\brief
Accessor function for character animation type

\return character animation type
*/
/******************************************************************************/
int CCharacter::getAnimationType()
{
	return animationType;
}
/******************************************************************************/
/*!
\brief
Accessor function for character x position

\return x position of the character
*/
/******************************************************************************/
float CCharacter::getXpos()
{
	return x;
}
/******************************************************************************/
/*!
\brief
Accessor function for character Y position

\return Y position of the character
*/
/******************************************************************************/
float CCharacter::getYpos()
{
	return y;
}
/******************************************************************************/
/*!
\brief
Accessor function for character Z position

\return Z position of the character
*/
/******************************************************************************/
float CCharacter::getZpos()
{
	return z;
}
/******************************************************************************/
/*!
\brief
Mutator function to set x pos of character

\param posX - X position of character
*/
/******************************************************************************/
void CCharacter::setXpos(float posX)
{
	x = posX;
}
/******************************************************************************/
/*!
\brief
Mutator function to set y pos of character

\param posY - Y position of character
*/
/******************************************************************************/
void CCharacter::setYpos(float posY)
{
	y = posY;
}
/******************************************************************************/
/*!
\brief
Mutator function to set z pos of character

\param posZ - Z position of character
*/
/******************************************************************************/
void CCharacter::setZpos(float posZ)
{
	z = posZ;
}
/******************************************************************************/
/*!
\brief
Mutator function to set character state

\param state - character state
*/
/******************************************************************************/
void CCharacter::setCharacterState(int state)
{
	characterState = state;
}
/******************************************************************************/
/*!
\brief
Mutator function to set character job

\param jobNum - character job
*/
/******************************************************************************/
void CCharacter::setCharacterJob(int jobNum)
{
	characterJob = jobNum;
}
/******************************************************************************/
/*!
\brief
Mutator function to set character animation type

\param type - character animation type
*/
/******************************************************************************/
void CCharacter::setAnimationType(int type)
{
	animationType = type;
}
