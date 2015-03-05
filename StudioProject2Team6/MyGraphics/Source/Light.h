#ifndef _LIGHT_H
#define _LIGHT_H

#include "Vertex.h"
/******************************************************************************/
/*!
		Struct Light:
\brief	Defines a light source
*/
/******************************************************************************/
struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	Light()
	{
	}
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;

};

#endif