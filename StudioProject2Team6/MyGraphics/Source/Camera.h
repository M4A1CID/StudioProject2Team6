#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
/******************************************************************************/
/*!
		Class Camera:
\brief	Defines the Camera class
*/
/******************************************************************************/
class Camera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;

	Camera();
	~Camera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Reset();
	virtual void UpdateMovement(double dt, bool reverse);
	virtual void UpdateView(double dt, bool reverse);
};

#endif