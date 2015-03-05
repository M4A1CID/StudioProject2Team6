#ifndef _MATERIAL_H
#define _MATERIAL_H
/******************************************************************************/
/*!
		Struct Component:
\brief	Defines a material component
*/
/******************************************************************************/
struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f)
	{
		Set(r, g, b);
	}
	void Set(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
};
/******************************************************************************/
/*!
		Struct Material:
\brief	Defines a material
*/
/******************************************************************************/
struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;
	Material()
	{
		kAmbient.Set(0.35f, 0.35f, 0.35f);
		kDiffuse.Set(0.3f, 0.3f, 0.3f);
		kSpecular.Set(0.1f, 0.1f, 0.1f);
		kShininess = 0.5f;
	}
};
#endif