#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include <gl/GL.h>
#include <gl/GLU.h>

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	Color c;
	c.a = 1;
	c.r = 0;
	c.g = 1;
	c.b = 0.8;

	leftPole = new Cube(1, 12, 1);
	leftPole->color = c;
	leftPole->SetPos(10,6,0);
	App->physics->AddBody(*leftPole, 0);

	rightPole = new Cube(1, 12, 1);
	rightPole->color = c;
	rightPole->SetPos(-10, 6, 0);
	App->physics->AddBody(*rightPole, 0);

	

	c.a = 1;
	c.r = 0;
	c.g = 1;
	c.b = 0.5;
	topPole = new Cube(20, 3, 1);
	topPole->color = c;
	topPole->SetPos(0, 10, 0);
	App->physics->AddBody(*topPole, 0);

	//test slider
	

	
	

	//Road Panels:
	//1
	CreateSceneItem(0, 1, 20, Type::FLOOR);
	//2
	roadPtr = CreateSceneItem(22, 1, 58, Type::FLOOR);
	btTransform transform = roadPtr->GetBody()->getWorldTransform();
	transform.setRotation({ 0.707107, 0, 0.707107, 0 });
	roadPtr->GetBody()->setWorldTransform(transform);
	roadPtr->prim->SetRotation(90, { 0,1,0 });
	//3
	roadPtr = CreateSceneItem(80, 1, 58, Type::FLOOR);
	transform = roadPtr->GetBody()->getWorldTransform();
	transform.setRotation({ 0.707107, 0, 0.707107, 0 });
	roadPtr->GetBody()->setWorldTransform(transform);
	roadPtr->prim->SetRotation(90, { 0,1,0 });
	//4
	CreateSceneItem(110, 1, 80, Type::FLOOR);
	//4.1
	CreateSceneItem(110, 1, 140, Type::FLOOR);
	//4.2
	CreateSceneItem(110, 1, 200, Type::FLOOR);
	liftCube = new Cube(26, 0.5, 60);
	lift = App->physics->AddBody(*liftCube, 0);
	
	
	
	c.a = 1;
	c.r = 1;
	c.g = 0.9;
	c.b = 0.8;
	liftCube->color = c;


	a = 0;
	
	//<level2>
	CreateSceneItem(66, 30, 250, Type::FLOOR);
	roadPtr = CreateSceneItem(88, 30, 225, Type::FLOOR);
	transform = roadPtr->GetBody()->getWorldTransform();
	transform.setRotation({ 0.707107, 0, 0.707107, 0 });
	roadPtr->GetBody()->setWorldTransform(transform);
	roadPtr->prim->SetRotation(90, { 0,1,0 });
	
	CreateSceneItem(110, 30, 195, Type::FLOOR);

	roadPtr = CreateSceneItem(88, 30, 160, Type::FLOOR);
	transform = roadPtr->GetBody()->getWorldTransform();
	transform.setRotation({ 0.707107, 0, 0.707107, 0 });
	roadPtr->GetBody()->setWorldTransform(transform);
	roadPtr->prim->SetRotation(90, { 0,1,0 });
	//CreateSceneItem(66, 30, 190, Type::FLOOR);
	CreateSceneItem(66, 30, 130, Type::FLOOR);
	//CreateSceneItem(66, 30, 100, Type::FLOOR);
	//CreateSceneItem(66, 30, 130, Type::FLOOR);
	roadPtr = CreateSceneItem(44, 30, 280, Type::FLOOR);
	transform = roadPtr->GetBody()->getWorldTransform();
	transform.setRotation({ 0.707107, 0, 0.707107, 0 });
	roadPtr->GetBody()->setWorldTransform(transform);
	roadPtr->prim->SetRotation(90, { 0,1,0 });
	
	CreateSceneItem(22, 30, 250, Type::FLOOR);
	CreateSceneItem(22, 30, 195, Type::FLOOR);

	roadPtr = CreateSceneItem(44, 1, 160, Type::FLOOR);
	transform = roadPtr->GetBody()->getWorldTransform();
	transform.setRotation({ 0.707107, 0, 0.707107, 0 });
	roadPtr->GetBody()->setWorldTransform(transform);
	roadPtr->prim->SetRotation(90, { 0,1,0 });
	
	roadPtr = CreateSceneItem(66, 35, 205, Type::RAMP);
	transform = roadPtr->GetBody()->getWorldTransform();
	transform.setRotation({ 0.984808, 0, 0, -0.173648 });
	roadPtr->GetBody()->setWorldTransform(transform);
	roadPtr->prim->SetRotation(20, { 1,0,0 });
	
	
	

	//</level2>
	
	//5
	roadPtr = CreateSceneItem(88, 1, 230, Type::FLOOR);
	transform = roadPtr->GetBody()->getWorldTransform();
	transform.setRotation({ 0.707107, 0, 0.707107, 0 });
	roadPtr->GetBody()->setWorldTransform(transform);
	roadPtr->prim->SetRotation(90, { 0,1,0 });
	
	//5.1
	CreateSceneItem(66, 1, 200 - 2, Type::FLOOR);

	//5.2
	CreateSceneItem(66, 1, 140 - 2, Type::FLOOR);
	
	//6
	roadPtr = CreateSceneItem(66, 5, 95, Type::RAMP);
	transform = roadPtr->GetBody()->getWorldTransform();
	transform.setRotation({ 0.984808, 0, 0, -0.173648 });
	roadPtr->GetBody()->setWorldTransform(transform);
	roadPtr->prim->SetRotation(20, { 1,0,0 });
	//7
	roadPtr = CreateSceneItem(66, 5, 33, Type::RAMP);
	transform = roadPtr->GetBody()->getWorldTransform();
	transform.setRotation({ 0.984808, 0, 0, 0.173648 });
	roadPtr->GetBody()->setWorldTransform(transform);
	roadPtr->prim->SetRotation(340, { 1,0,0 });
	//8
	CreateSceneItem(66, 1, -8, Type::FLOOR);
	//9
	CreateSceneItem(66, 1, -40, Type::FLOOR);
	//10
	roadPtr = CreateSceneItem(44, 1, -78, Type::FLOOR);
	transform = roadPtr->GetBody()->getWorldTransform();
	transform.setRotation({ 0.707107, 0, 0.707107, 0 });
	roadPtr->GetBody()->setWorldTransform(transform);
	roadPtr->prim->SetRotation(90, { 0,1,0 });
	//11
	roadPtr = CreateSceneItem(22, 1, -78, Type::FLOOR);
	transform = roadPtr->GetBody()->getWorldTransform();
	transform.setRotation({ 0.707107, 0, 0.707107, 0 });
	roadPtr->GetBody()->setWorldTransform(transform);
	roadPtr->prim->SetRotation(90, { 0,1,0 });
	//12
	CreateSceneItem(0, 1, -40, Type::FLOOR);

	//110, 1, 80
	//110, 1, 140
	//110, 1, 200
	//22, 30, 250
	//22, 30, 19
	//44, 1, 160
	//66, 5, 95

	/*ReferenceCube = new Model();
	ReferenceCube->model = App->models->LoadModel("Assets/Models/def_cube.obj");
	ReferenceCube->colB = 255;
	ReferenceCube->colG = 0;
	ReferenceCube->colR = 0;
	ReferenceCube->x = 5;
	ReferenceCube->y = 0;
	ReferenceCube->z = 0;
	
	
	
	baseFloor = new Model();
	baseFloor->model = App->models->LoadModel("Assets/Models/def_cube.obj");
	baseFloor->colR = 125;
	baseFloor->colG = 0;
	baseFloor->colB = 225;
	baseFloor->x = 0;
	baseFloor->y = 0;
	baseFloor->z = 15;
	baseFloor->scale = 2;*/

	Cube obstacleGeo(4, 4, 4);
	obstacle = App->physics->AddBody(obstacleGeo,0); //objects with 0 mass act as kinematic
	obstacle->SetPos(5, 0, 0);
	obstacle->type = SQUARE;
	obstacle->collision_listeners.add(this);

	Sphere ball(2);
	ball.SetPos(0, 0, 5);
	randomBall = App->physics->AddBody(ball, 0);
	randomBall->collision_listeners.add(this);
	randomBall->type = SPHERE;
	
	//road->model = App->models->LoadModel("Assets/Models/car_1.obj");

	//cube = App->modelLoader->LoadModel("Assets/Models/full_train.obj");
	//pyramid = App->modelLoader->LoadModel("Assets/Models/pyramid.obj");
	//tracks = App->modelLoader->LoadModel("Assets/Models/tracks.obj");
	//train = App->modelLoader->LoadModel("Assets/Models/full_train.obj");
	//mod_car = App->modelLoader->LoadModel("Assets/Models/car_1.obj");

	Color cubeColor;
	cubeColor.r = 0.0f;
	cubeColor.g = 0.5f;
	cubeColor.b = 1.0f;
	cubes[0] = new Cube(5, 150, 750);
	cubes[0]->SetPos(-20, 75, 30);
	cubes[1] = new Cube(150, 150, 5);
	cubes[1]->SetPos(50, 75, -95);
	cubes[2] = new Cube(5, 150, 750);
	cubes[2]->SetPos(125, 75, 30);
	cubes[3] = new Cube(150, 150, 5);
	cubes[3]->SetPos(50, 75, 300);
	cubes[4] = new Cube(150, 1, 750);
	cubes[4]->SetPos(50, 0, 30);
	cubes[4]->color = cubeColor;


	App->audio->PlayMusic("Assets/Audio/Music/song1.ogg");
	
	//podium 
	podium[0] = new Cube(8, 4, 4);
	podium[0]->SetPos(30, 2.5, 0);
	podium[1] = new Cube(8, 2, 4);
	podium[1]->SetPos(30, 1.5, 4);
	podium[2] = new Cube(8, 1, 4);
	podium[2]->SetPos(30, 1, -4);
	Cube podium(8, 4, 4);
	obstacle = App->physics->AddBody(podium, 0); //objects with 0 mass act as kinematic
	obstacle->SetPos(30, 2.5, 0);
	obstacle->type = SQUARE;
	obstacle->collision_listeners.add(this);


	




	//cubeA = new Cube(1, 1, 1);
	//cubeA->SetPos(-1, 6, 0);
	//testA = App->physics->AddBody(*cubeA, 0);
	//
	//cubeB = new Cube(1, 1, 1);
	//cubeB->SetPos(1, 6, 0);
	//testB = App->physics->AddBody(*cubeB , 1);

	//110, 1, 140
	float base_pos[3] = { 110,2,140 };

	s1_cube_base[0] = new Cube(1, 1, 1);
	s1_cube_base[0]->SetPos(base_pos[0], base_pos[1], base_pos[2]);
	s1_base[0] = App->physics->AddBody(*s1_cube_base[0], 0);

	s1_cube_1[0] = new Cube(3, 6, 0.25f);
	s1_cube_1[0]->SetPos(base_pos[0] - 3, base_pos[1] + 8, base_pos[2]);
	s1_wall_1[0] = App->physics->AddBody(*s1_cube_1[0], 1);

	s1_cube_2[0] = new Cube(3, 6, 0.25f);
	s1_cube_2[0]->SetPos(base_pos[0] - 3, base_pos[1] + 8, base_pos[2]);
	s1_wall_2[0]= App->physics->AddBody(*s1_cube_2[0], 1);
	

	s1_hinge_1[0] = App->physics->AddConstraintHinge(*s1_base[0], *s1_wall_1[0], { 0,3,0 }, { -1,0,0 }, { 0,1,0 }, { 0,1,0 }, true);
	s1_hinge_1[0]->enableAngularMotor(true, 1, 5);
			  
	s1_hinge_1[0] = App->physics->AddConstraintHinge(*s1_base[0], *s1_wall_2[0], { 0,3,0 }, { 1,0,0 }, { 0,1,0 }, { 0,1,0 }, true);
	s1_hinge_1[0]->enableAngularMotor(true, 1, 5);

	//110, 1, 200
	base_pos[0] = 110;
	base_pos[1] = 2;
	base_pos[2] = 200;

	s1_cube_base[1] = new Cube(1, 1, 1);
	s1_cube_base[1]->SetPos(base_pos[0], base_pos[1], base_pos[2]);
	s1_base[1] = App->physics->AddBody(*s1_cube_base[1], 0);

	s1_cube_1[1] = new Cube(3, 6, 0.25f);
	s1_cube_1[1]->SetPos(base_pos[0] - 3, base_pos[1] + 8, base_pos[2]);
	s1_wall_1[1] = App->physics->AddBody(*s1_cube_1[1], 1);

	s1_cube_2[1] = new Cube(3, 6, 0.25f);
	s1_cube_2[1]->SetPos(base_pos[0] - 3, base_pos[1] + 8, base_pos[2]);
	s1_wall_2[1] = App->physics->AddBody(*s1_cube_2[1], 1);


	s1_hinge_1[1] = App->physics->AddConstraintHinge(*s1_base[1], *s1_wall_1[1], { 0,3,0 }, { -1,0,0 }, { 0,1,0 }, { 0,1,0 }, true);
	s1_hinge_1[1]->enableAngularMotor(true, 1, 5);

	s1_hinge_1[1] = App->physics->AddConstraintHinge(*s1_base[1], *s1_wall_2[1], { 0,3,0 }, { 1,0,0 }, { 0,1,0 }, { 0,1,0 }, true);
	s1_hinge_1[1]->enableAngularMotor(true, 1, 5);

	//80, 1, 58
	base_pos[0] = 80;
	base_pos[1] = 2;
	base_pos[2] = 58;

	s1_cube_base[2] = new Cube(1, 1, 1);
	s1_cube_base[2]->SetPos(base_pos[0], base_pos[1], base_pos[2]);
	s1_base[2] = App->physics->AddBody(*s1_cube_base[2], 0);

	s1_cube_1[2] = new Cube(3, 6, 0.25f);
	s1_cube_1[2]->SetPos(base_pos[0] - 3, base_pos[1] + 8, base_pos[2]);
	s1_wall_1[2] = App->physics->AddBody(*s1_cube_1[2], 1);

	s1_cube_2[2] = new Cube(3, 6, 0.25f);
	s1_cube_2[2]->SetPos(base_pos[0] - 3, base_pos[1] + 8, base_pos[2]);
	s1_wall_2[2] = App->physics->AddBody(*s1_cube_2[2], 1);


	s1_hinge_1[2] = App->physics->AddConstraintHinge(*s1_base[2], *s1_wall_1[2], { 0,3,0 }, { -1,0,0 }, { 0,1,0 }, { 0,1,0 }, true);
	s1_hinge_1[2]->enableAngularMotor(true, 1, 5);

	s1_hinge_1[2] = App->physics->AddConstraintHinge(*s1_base[2], *s1_wall_2[2], { 0,3,0 }, { 1,0,0 }, { 0,1,0 }, { 0,1,0 }, true);
	s1_hinge_1[2]->enableAngularMotor(true, 1, 5);

	//22, 1, 58
	base_pos[0] = 22 + 4;
	base_pos[1] = 2;
	base_pos[2] = 58 - 3;

	s1_cube_base[3] = new Cube(1, 1, 1);
	s1_cube_base[3]->SetPos(base_pos[0], base_pos[1], base_pos[2]);
	s1_base[3] = App->physics->AddBody(*s1_cube_base[3], 0);

	s1_cube_1[3] = new Cube(3, 6, 0.25f);
	s1_cube_1[3]->SetPos(base_pos[0] - 3, base_pos[1] + 8, base_pos[2]);
	s1_wall_1[3] = App->physics->AddBody(*s1_cube_1[3], 10);

	s1_cube_2[3] = new Cube(3, 6, 0.25f);
	s1_cube_2[3]->SetPos(base_pos[0] - 3, base_pos[1] + 8, base_pos[2]);
	s1_wall_2[3] = App->physics->AddBody(*s1_cube_2[3], 10);


	s1_hinge_1[3] = App->physics->AddConstraintHinge(*s1_base[3], *s1_wall_1[3], { 0,3,0 }, { -1,0,0 }, { 0,1,0 }, { 0,1,0 }, true);
	s1_hinge_1[3]->enableAngularMotor(true, 1, 5);

	s1_hinge_1[3] = App->physics->AddConstraintHinge(*s1_base[3], *s1_wall_2[3], { 0,3,0 }, { 1,0,0 }, { 0,1,0 }, { 0,1,0 }, true);
	s1_hinge_1[3]->enableAngularMotor(true, 1, 5);
	
	s_angle = 0;

	
	//22, 30, 250
	//22, 30, 19
	//44, 1, 160
	//66, 5, 95

	//66, 5, 95
	base_pos[0] = 66;
	base_pos[1] = 30;
	base_pos[2] = 95 - 30;

	c_sph_1 = new Sphere(2.5f);
	c_sph_1->SetPos(base_pos[0], base_pos[1], base_pos[2]);
	c_base_1 = App->physics->AddBody(*c_sph_1, 0);

	for (int i = 0; i < 5; i++)
	{
		c_chains_1[i] = new Sphere(2.5f);
		c_chains_1[i]->SetPos(base_pos[0], base_pos[1] - 2.5f * i, base_pos[2]);
		c_chains_pb_1[i] = App->physics->AddBody(*c_sph_1, 10);
	}

	c_p2p_1[0] = App->physics->AddConstraintP2P(*c_base_1, *c_chains_pb_1[0], { 0,-2.5f ,0 }, { 0,2.5f,0 });

	for (int i = 1; i < 5; i++)
	{
		
		c_p2p_1[i] = App->physics->AddConstraintP2P(*c_chains_pb_1[i - 1], *c_chains_pb_1[i], { 0,-2.5f,0 }, { 0,2.5f,0 });
	}

	//66, 1, 200
	base_pos[0] = 66;
	base_pos[1] = 30;
	base_pos[2] = 180;

	c_sph_2 = new Sphere(2.5f);
	c_sph_2->SetPos(base_pos[0], base_pos[1], base_pos[2]);
	c_base_2 = App->physics->AddBody(*c_sph_2, 0);


	for (int i = 0; i < 5; i++)
	{
		c_chains_2[i] = new Sphere(2.5f);
		c_chains_2[i]->SetPos(base_pos[0], base_pos[1] - 2.5f * i, base_pos[2]);
		c_chains_pb_2[i] = App->physics->AddBody(*c_sph_2, 10);
	}

	c_p2p_2[0] = App->physics->AddConstraintP2P(*c_base_2, *c_chains_pb_2[0], { 0,-2.5f ,0 }, { 0,2.5f,0 });

	for (int i = 1; i < 5; i++)
	{

		c_p2p_2[i] = App->physics->AddConstraintP2P(*c_chains_pb_2[i - 1], *c_chains_pb_2[i], { 0,-2.5f,0 }, { 0,2.5f,0 });
	}

	//110, 30, 195
	base_pos[0] = 110;
	base_pos[1] = 60;
	base_pos[2] = 195;

	c_sph_3 = new Sphere(2.5f);
	c_sph_3->SetPos(base_pos[0], base_pos[1], base_pos[2]);
	c_base_3 = App->physics->AddBody(*c_sph_3, 0);


	for (int i = 0; i < 5; i++)
	{
		c_chains_3[i] = new Sphere(2.5f);
		c_chains_3[i]->SetPos(base_pos[0], base_pos[1] - 2.5f * i, base_pos[2]);
		c_chains_pb_3[i] = App->physics->AddBody(*c_sph_3, 10);
	}

	c_p2p_3[0] = App->physics->AddConstraintP2P(*c_base_3, *c_chains_pb_3[0], { 0,-2.5f ,0 }, { 0,2.5f,0 });

	for (int i = 1; i < 5; i++)
	{

		c_p2p_3[i] = App->physics->AddConstraintP2P(*c_chains_pb_3[i - 1], *c_chains_pb_3[i], { 0,-2.5f,0 }, { 0,2.5f,0 });
	}

	//44, 30, 280
	base_pos[0] = 44;
	base_pos[1] = 60;
	base_pos[2] = 280;

	c_sph_4 = new Sphere(2.5f);
	c_sph_4->SetPos(base_pos[0], base_pos[1], base_pos[2]);
	c_base_4 = App->physics->AddBody(*c_sph_4, 0);


	for (int i = 0; i < 5; i++)
	{
		c_chains_4[i] = new Sphere(2.5f);
		c_chains_4[i]->SetPos(base_pos[0], base_pos[1] - 2.5f * i, base_pos[2]);
		c_chains_pb_4[i] = App->physics->AddBody(*c_sph_4, 10);
	}

	c_p2p_4[0] = App->physics->AddConstraintP2P(*c_base_4, *c_chains_pb_4[0], { 0,-2.5f ,0 }, { 0,2.5f,0 });

	for (int i = 1; i < 5; i++)
	{

		c_p2p_4[i] = App->physics->AddConstraintP2P(*c_chains_pb_4[i - 1], *c_chains_pb_4[i], { 0,-2.5f,0 }, { 0,2.5f,0 });
	}

	//hingeTest = App->physics->AddConstraintHinge(*testA, *testB, { 0,2,0 }, { -1,0,0 }, { 0,1,0 }, { 0,1,0 }, true);
	//
	//hingeTest->enableAngularMotor(true, 1, 5);

	App->physics->debug = true;
	
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	delete leftPole;
	delete rightPole;
	delete topPole;
	roadList.clear();
	/*delete ReferenceCube;
	delete road;
	delete baseFloor;*/

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	a += dt;
	s_angle -= 2.5f;
	for (size_t i = 0; i < 4; i++)
	{
		s1_cube_1[i]->SetRotation(s1_hinge_1[i]->getRigidBodyB().getOrientation().getAngle(), { 0,1,0 });
		s1_cube_2[i]->SetRotation(s_angle, { 0,1,0 });


		s1_cube_base[i]->Render(); 
		s1_cube_1[i]->Render();
		s1_cube_2[i]->Render();
		
	}


	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	lift->SetPos(6 - 5, 16 + 15 * sinf(a * 0.3f), 180);
	liftCube->SetPos(6 - 5, 16 + 15 * sinf(a * 0.3f), 180);
	liftCube->Render();


	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	{
		wireframeActive = !wireframeActive;
	}

	if (App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
	{
		if (!loliMode)
		{
			App->audio->PlayMusic("Assets/Audio/Music/song2.ogg");
			loliMode = true;
		}
		else
		{
			App->audio->PlayMusic("Assets/Audio/Music/song1.ogg");
			loliMode = false;
		}
		
	}


	Color colors;
	currentTime = SDL_GetTicks();

	if ((currentTime > lastTime + 2000)&&(!loliMode))
	{
		lastTime = currentTime;
		for (int i = 0; i < 4; i++)
		{
			
			whatColor = currentTime % 3;
			if (whatColor == 0)
			{
				colors.r = 1.0f;
				colors.g = 0.0f;
				colors.b = 0.0f;
			}
			else if (whatColor == 1)
			{
				colors.r = 0.0f;
				colors.g = 1.0f;
				colors.b = 0.0f;
			}
			else
			{
				colors.r = 1.0f;
				colors.g = 1.0f;
				colors.b = 0.0f;
			}
			
			cubes[i]->color = colors;

		}
		
		
	}

	if (loliMode)
	{
		if ((currentTime > lastTime + 100))
		{
			lastTime = currentTime;
			for (int i = 0; i < 4; i++)
			{

				whatColor = currentTime % 3;
				if (whatColor == 0)
				{
					colors.r = 0.0f;
					colors.g = 1.0f;
					colors.b = 1.0f;
				}
				else if (whatColor == 1)
				{
					colors.r = 1.0f;
					colors.g = 0.0f;
					colors.b = 1.0f;
				}
				else
				{
					colors.r = 0.0f;
					colors.g = 0.0f;
					colors.b = 1.0f;
				}

				cubes[i]->color = colors;

			}


		}

	}
	cubes[0]->Render();
	cubes[1]->Render();
	cubes[2]->Render();
	cubes[3]->Render();
	cubes[4]->Render();
	podium[0]->Render();
	podium[1]->Render();
	podium[2]->Render();
	//glBegin(GL_TRIANGLES);
	//
	//
	//glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	//
	//glVertex3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(1.0f, 1.0f, 0.0f);
	//glVertex3f(0.0f, 1.0f, 0.0f);
	//
	//
	//
	//
	//
	//glEnd();
	

//	small code for shpere movement
	randomBall->SetPos(10, 10, counter);
	if (!arrived)
	{
		counter += 0.1f;
		if (counter >= 10)
			arrived = true;
	}
	else
	{
		counter -= 0.1f;
		if (counter <= 0)
			arrived = false;
	}

	btVector3 playerPosition = App->player->GetPosition();
		
	//road->RenderModel();

	/*ReferenceCube->RenderModel();
	
	baseFloor->RenderModel();*/
	

	
	return UPDATE_CONTINUE;
}
update_status ModuleSceneIntro::PostUpdate(float dt)
{
	for (p2List_item<PhysBody3D*>* item = roadList.getFirst(); item; item = item->next)
	{
		item->data->prim->Render();
	}
	leftPole->Render();
	rightPole->Render();
	topPole->Render();

	return UPDATE_CONTINUE;
}
void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1->type == PLAYER)
	{
		switch (body2->type)
		{
		case SPHERE:
		{
			LOG("Player touched sphere uwu"); 
		}
		break;
		case FLOOR:
		{
					
		}
		break;
		default:
			break;
		}
	}

	if (body1->type == PLAYER &&( body2->type == FLOOR || body2->type == RAMP))
	{
		App->player->state = ON_GROUND;
		LOG("On Ground");
	}
	else {
		App->player->state = ON_AIR;
		LOG("On Air");
	}


	if (body1->type == SPHERE && body2->type == SPHERE) {
		LOG("Balls Touching");
	}
}

PhysBody3D* ModuleSceneIntro::CreateSceneItem(float x, float y, float z, Type type, Cube* cube)
{
	if (cube != nullptr)
	{
		Cube* item;

		if (type == FLOOR)
		{
			item = new Cube(16, 0.5, 60);
		}
		if (type == RAMP)
		{
			item = new Cube(16, 0.5, 30);
		}


		Color c;
		c.a = 1;
		c.r = 1;
		c.g = 0.9;
		c.b = 0.8;
		item->color = c;
		item->SetPos(x, y, z);
		PhysBody3D* phys = App->physics->AddBody(*item, 0);
		phys->type = type;
		roadList.add(phys);
		return phys;
	}
	else
	{
		if (type == FLOOR)
		{
			cube = new Cube(16, 0.5, 60);
		}
		if (type == RAMP)
		{
			cube = new Cube(16, 0.5, 30);
		}


		Color c;
		c.a = 1;
		c.r = 1;
		c.g = 0.9;
		c.b = 0.8;
		cube->color = c;
		cube->SetPos(x, y, z);
		PhysBody3D* phys = App->physics->AddBody(*cube, 0);
		phys->type = type;
		roadList.add(phys);
		return phys;
	}
	
	
}