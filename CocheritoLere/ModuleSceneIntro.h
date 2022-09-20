#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "OBJ_Model.h"
#ifdef _DEBUG
#pragma comment (lib, "Bullet/libx86/BulletDynamics_debug.lib")
#pragma comment (lib, "Bullet/libx86/BulletCollision_debug.lib")
#pragma comment (lib, "Bullet/libx86/LinearMath_debug.lib")
#else
#pragma comment (lib, "Bullet/libx86/BulletDynamics.lib")
#pragma comment (lib, "Bullet/libx86/BulletCollision.lib")
#pragma comment (lib, "Bullet/libx86/LinearMath.lib")
#endif

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;
class Model;
class btHingeConstraint;
class btTypedConstraint;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	PhysBody3D* CreateSceneItem(float x, float y, float z, Type type, Cube* cube = nullptr);

	

public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	bool wireframeActive = false;


	

	Model* ReferenceCube;
	PhysBody3D* obstacle;
	PhysBody3D* roadPtr;

	
	Cube* leftPole;
	Cube* rightPole;
	Cube* topPole;

	Cube* cubes[5];
	Cube* podium[3];
	int currentTime = 0;
	int whatColor = 0;
	int lastTime = 0;
	Model* baseFloor;
	float counter = 0;
	bool arrived = false;

	bool loliMode = false;
	uint song01 = 0;
	uint song02 = 0;
	PhysBody3D* randomBall;

	/*Cube* cube;
	PhysBody3D* horse;*/
	p2List<PhysBody3D*> roadList;


	//lift
	PhysBody3D* lift;
	Cube* liftCube;
	float a;

	//spinner 1
	PhysBody3D* s1_base[4];
	PhysBody3D* s1_wall_1[4];
	PhysBody3D* s1_wall_2[4];
	Cube* s1_cube_base[4];
	Cube* s1_cube_1[4];
	Cube* s1_cube_2[4];

	btHingeConstraint* s1_hinge_1[4] = { nullptr };
	btHingeConstraint* s1_hinge_2[4] = {nullptr};

	float s_angle;

	PhysBody3D* c_base_1;
	PhysBody3D* c_chains_pb_1[5];
	Sphere* c_sph_1;
	Sphere* c_chains_1[5];


	btTypedConstraint* c_p2p_1[5] = { nullptr };

	PhysBody3D* c_base_2;
	PhysBody3D* c_chains_pb_2[5];
	Sphere* c_sph_2;
	Sphere* c_chains_2[5];


	btTypedConstraint* c_p2p_2[5] = { nullptr };

	PhysBody3D* c_base_3;
	PhysBody3D* c_chains_pb_3[5];
	Sphere* c_sph_3;
	Sphere* c_chains_3[5];


	btTypedConstraint* c_p2p_3[5] = { nullptr };

	PhysBody3D* c_base_4;
	PhysBody3D* c_chains_pb_4[5];
	Sphere* c_sph_4;
	Sphere* c_chains_4[5];


	btTypedConstraint* c_p2p_4[5] = { nullptr };



};
