#include "Globals.h"
#include "Application.h"
#include "PhysBody3D.h"
#include "ModuleCamera3D.h"
#include "ModulePhysics3D.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 5.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);
	
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;

	freecam = false;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	
	if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
	{
		freecam = !freecam;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT)
	{
		cview = right;
	}
	else if (App->input->GetKey(SDL_SCANCODE_H) == KEY_REPEAT)
	{
		cview = behind;
	}
	else if (App->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT)
	{
		cview = left;
	}
	else
	{
		cview = normal;
	}
	
	if (App->player->podium == true)
	{
		cview = behind;
	}

	if (freecam)
		DebugMode(dt);
	else
		FollowVehicle();

	// Recalculate matrix -------------
	CalculateViewMatrix();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const vec3 &Spot)
{
	Reference = Spot;
	
	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);
	
	

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec3 &Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return &ViewMatrix;
}

void ModuleCamera3D::FollowVehicle()
{
	btVector3 playerPosition = App->player->GetPosition();
	vec3 playerForwardVec = { App->player->forwardVec.getX(),App->player->forwardVec.getY(),App->player->forwardVec.getZ() };
	vec3 playerPos = { playerPosition.getX(),playerPosition.getY(),playerPosition.getZ() };

	vec3 cameraOffset = { 0, 0, 0 };
	if (cview == left)
	{
		cameraOffset = { -15, 5, 0 };
		Position = playerPos;
		Position.z += cameraOffset.z;
		Position.x += cameraOffset.x;
		Position.y += cameraOffset.y;
	}
	else if(cview == right)
	{
		cameraOffset = { 15, 5, 0 };
		Position = playerPos - playerForwardVec ;
		Position.z += cameraOffset.z;
		Position.x += cameraOffset.x;
		Position.y += cameraOffset.y;
	}
	else if (cview == normal)
	{
		cameraOffset = { 0, 5, 15 };
		Position = playerPos - playerForwardVec * cameraOffset.z;
		Position.y += cameraOffset.y;
	}
	else if (cview == behind)
	{
		cameraOffset = { 0, 5, -15 };
		Position = playerPos - playerForwardVec * cameraOffset.z;
		Position.y += cameraOffset.y;
	}

	vec3 playerDir = App->player->position - App->player->lastPosition;
	playerDir = normalize(playerDir);


	Reference.x = playerPos.x;
	Reference.y = playerPos.y;
	Reference.z = playerPos.z;


	
	
	

	CalculateViewMatrix();
	LookAt(playerPos);
}

void ModuleCamera3D::DebugMode(float dt)
{
	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!

	vec3 newPos(0, 0, 0);
	float speed = 3.0f * dt;
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = 12.0f * dt;

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT) newPos.y += speed;
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) newPos.y -= speed;

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= Z * speed;
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += Z * speed;


	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= X * speed;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += X * speed;

	Position += newPos;
	Reference += newPos;

	// Mouse motion ----------------

	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{
		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

		float Sensitivity = 0.25f;
		
		Position -= Reference;

		if (dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity;

			X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		}

		if (dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity;

			Y = rotate(Y, DeltaY, X);
			Z = rotate(Z, DeltaY, X);

			if (Y.y < 0.0f)
			{
				Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = cross(Z, X);
			}
		}

		Position = Reference + Z * length(Position);
	}

}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}