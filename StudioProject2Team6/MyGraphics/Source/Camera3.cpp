#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"
#include "SceneSP.h"
/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera3::Camera3()
{
}
/******************************************************************************/
/*!
\brief
Default destructor
*/
/******************************************************************************/
Camera3::~Camera3()
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
void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	limiter = 45;
	CAMERA_SPEED = 150.f;
}
/******************************************************************************/
/*!
\brief
Updates the camera movement

\param dt - delta time
\param reverse - reverses camera controls if true
*/
/******************************************************************************/
void Camera3::UpdateMovement(double dt, bool reverse)
{
	float runMultiplyer;
	if(!Application::IsKeyPressed(VK_SHIFT)) //Check if player is sprinting
	{
		runMultiplyer =0.2f;
	}
	else
	{
		runMultiplyer = 0.5f;
	}
	if(Application::IsKeyPressed('A') )
	{
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		if(reverse)
		{
			position += right * CAMERA_SPEED *runMultiplyer* dt;
			target += right * CAMERA_SPEED *runMultiplyer* dt;
		}else
		{
		position -= right * CAMERA_SPEED*runMultiplyer * dt;
		target -= right * CAMERA_SPEED*runMultiplyer * dt;
		}
	}
	if(Application::IsKeyPressed('D'))
	{
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		if(reverse)
		{
			position -= right * CAMERA_SPEED*runMultiplyer * dt;
			target -= right * CAMERA_SPEED*runMultiplyer * dt;
		}else
		{
		position += right * CAMERA_SPEED *runMultiplyer* dt;
		target += right * CAMERA_SPEED *runMultiplyer* dt;
		}
	}
	if(Application::IsKeyPressed('W'))
	{
		Vector3 view = (target - position).Normalized();
		view.y = 0;
		if(reverse)
		{
			position -= view * CAMERA_SPEED *runMultiplyer* dt;
			target -= view * CAMERA_SPEED*runMultiplyer * dt;
		}else
		{
			position += view * CAMERA_SPEED *runMultiplyer* dt;
			target += view * CAMERA_SPEED*runMultiplyer * dt;
		}
	}
	if(Application::IsKeyPressed('S'))
	{
		Vector3 view = (target - position).Normalized();
		view.y = 0;
		if(reverse)
		{
			position += view * CAMERA_SPEED *runMultiplyer* dt;
			target += view * CAMERA_SPEED*runMultiplyer * dt;
		}else
		{
			position -= view * CAMERA_SPEED *runMultiplyer* dt;
			target -= view * CAMERA_SPEED*runMultiplyer * dt;
		}
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
void Camera3::UpdateView(double dt, bool reverse)
{
	
	if(Application::IsKeyPressed(VK_LEFT)&& !Application::IsKeyPressed('R'))
	{
		float yaw;
		Vector3 view = (target - position).Normalized();
		if(reverse)
			yaw = (float)(-CAMERA_SPEED * dt);
		else
			yaw = (float)(CAMERA_SPEED * dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		up = rotation * up;
		target = view + position;
	}
	if(Application::IsKeyPressed(VK_RIGHT)&& !Application::IsKeyPressed('R'))
	{
		float yaw;
		Vector3 view = (target - position).Normalized();
		if(reverse)
			yaw = (float)(CAMERA_SPEED * dt);
		else
			yaw = (float)(-CAMERA_SPEED * dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		up = rotation * up;
		target = view + position;
	}
	if(Application::IsKeyPressed(VK_UP)&& !Application::IsKeyPressed('R'))
	{
		if(limiter < 80)
		{
			float pitch = (float)(CAMERA_SPEED * dt);
			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			view = rotation * view;
			target = view + position;
			limiter +=2;
		}

	}
	if(Application::IsKeyPressed(VK_DOWN)&& !Application::IsKeyPressed('R'))
	{
		if(limiter>10)
		{
			float pitch = (float)(-CAMERA_SPEED * dt);
			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			view = rotation * view;
			target = view + position;
			limiter -=2;
		}
	}
}
/******************************************************************************/
/*!
\brief
Resets the camera back to its default position
*/
/******************************************************************************/
void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}