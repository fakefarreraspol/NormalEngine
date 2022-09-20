#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "OBJ_Model.h"

struct PhysVehicle3D;
class Model;

#define MAX_ACCELERATION 1500.0f
#define TURN_DEGREES 25.0f * DEGTORAD
#define BRAKE_POWER 35.0f
#define MAX_LIFES 3

enum PlayerState {
	ON_GROUND,
	ON_AIR,
	FLIPPED
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	btVector3 GetPosition();

	Model* carModel;
	
	btQuaternion orientation;
private:
	void Movement();
public:
	unsigned int score = 0;
	unsigned int lifes = MAX_LIFES;
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float maxVelocity = 100.0f;
	float brake;
	float pitch;
	float initialM[16];
	vec3 lastPosition;
	vec3 position;
	vec3 deltaPosition;
	int counter = 0;
	int lastTime = 0;
	btVector3 forwardVec;

	bool checkpointPassed = false;
	bool podium = false;
	
	float TurnSmoother = 0;


	PhysBody3D* hitBox = nullptr;

	PlayerState state;
};