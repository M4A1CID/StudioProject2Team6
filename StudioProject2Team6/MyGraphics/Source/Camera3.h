#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"
/******************************************************************************/
/*!
		Class Camera3:
\brief	Defines the Camera3 class
*/
/******************************************************************************/
class Camera3 : public Camera
{
public:

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	Camera3();
	~Camera3();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void UpdateMovement(double dt, bool reverse);
	virtual void UpdateView(double dt, bool reverse);
	bool Limit(Vector3& position, Vector3& target, int edge, float speed);
	bool tableCollision(Vector3& position, Vector3& target, float speed);
	virtual void Reset();
	int limiter;
	float CAMERA_SPEED;
};

#endif