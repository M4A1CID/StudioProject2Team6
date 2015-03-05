#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"
/******************************************************************************/
/*!
\brief
Default camera constructor
*/
/******************************************************************************/
Camera::Camera()
{
	Reset();
}
/******************************************************************************/
/*!
\brief
Default camera destructor
*/
/******************************************************************************/
Camera::~Camera()
{
}
/******************************************************************************/
/*!
\brief
Initialises the camera

\param pos - position of the camera
\param target - camera target
\param up - 
*/
/******************************************************************************/
void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
}
/******************************************************************************/
/*!
\brief
Resets the camera back to its default position
*/
/******************************************************************************/
void Camera::Reset()
{
	position.Set(1, 0, 0);
	target.Set(0, 0, 0);
	up.Set(0, 1, 0);
}
/******************************************************************************/
/*!
\brief
Updates the camera movement

\param dt - delta time
\param reverse - reverses camera controls if true
*/
/******************************************************************************/
void Camera::UpdateMovement(double dt, bool reverse)
{
	static const float CAMERA_SPEED = 200.f;
	if(Application::IsKeyPressed(VK_LEFT) || Application::IsKeyPressed('A'))
	{
		position.x -= (float)(CAMERA_SPEED * 0.2 * dt);
	}
	if(Application::IsKeyPressed(VK_RIGHT) || Application::IsKeyPressed('D'))
	{
		position.x += (float)(CAMERA_SPEED * 0.2 * dt);
	}
	if(Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed('W'))
	{
		position.y += (float)(CAMERA_SPEED * 0.2 * dt);
	}
	if(Application::IsKeyPressed(VK_DOWN) || Application::IsKeyPressed('S'))
	{
		position.y -= (float)(CAMERA_SPEED * 0.2 * dt);
	}
}
/******************************************************************************/
/*!
\brief
Updates the camera view

\param dt - delta time
\param reverse - reverses camera controls if true
*/
/******************************************************************************/
void Camera::UpdateView(double dt, bool reverse)
{

}