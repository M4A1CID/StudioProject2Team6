#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"
#include "SceneSP.h"

Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

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

/*bool Camera3::Limit( Vector3& position,Vector3& target, int edge, float speed)
{
	speed *= 0.02;

	if(position.x < -edge)
	{
		position.x += speed;
		target.x += speed;
	}

	if(position.x > edge)
	{
		position.x -= speed;
		target.x -= speed;
	}

	if(position.y < -edge)
	{
		position.y += speed;
		target.y += speed;
	}

	if(position.y > edge)
	{
		position.y -= speed;
		target.y -= speed;
	}

	if(position.z < -edge)
	{
		position.z += speed;
		target.z += speed;
	}

	if(position.z > edge)
	{
		position.z -= speed;
		target.z -= speed;
	}
	else
	{
		return true;
	}
}*/
void Camera3::UpdateMovement(double dt)
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

		//if(Limit(position,target, 150, CAMERA_SPEED)) //Limit to Skybox


		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		position -= right * CAMERA_SPEED*runMultiplyer * dt;
		target -= right * CAMERA_SPEED*runMultiplyer * dt;
	}
	if(Application::IsKeyPressed('D'))
	{
		//if(Limit(position,target,  150, CAMERA_SPEED)) //Limit to Skybox

		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		position += right * CAMERA_SPEED *runMultiplyer* dt;
		target += right * CAMERA_SPEED *runMultiplyer* dt;


	}
	if(Application::IsKeyPressed('W'))
	{
		//if(Limit(position,target,  150, CAMERA_SPEED)) //Limit to Skybox

		Vector3 view = (target - position).Normalized();
		view.y = 0;
		position += view * CAMERA_SPEED *runMultiplyer* dt;
		target += view * CAMERA_SPEED*runMultiplyer * dt;


	}
	if(Application::IsKeyPressed('S'))
	{

		//if(Limit(position,target,  150, CAMERA_SPEED)) //Limit to Skybox

		Vector3 view = (target - position).Normalized();
		view.y = 0;
		position -= view * CAMERA_SPEED *runMultiplyer* dt;
		target -= view * CAMERA_SPEED*runMultiplyer * dt;


	}
}

void Camera3::UpdateView(double dt)
{
	
	if(Application::IsKeyPressed(VK_LEFT)&& !Application::IsKeyPressed('R'))
	{
		Vector3 view = (target - position).Normalized();
		float yaw = (float)(CAMERA_SPEED * dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		up = rotation * up;
		target = view + position;

	}
	if(Application::IsKeyPressed(VK_RIGHT)&& !Application::IsKeyPressed('R'))
	{
		Vector3 view = (target - position).Normalized();
		float yaw = (float)(-CAMERA_SPEED * dt);
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

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}