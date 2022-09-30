#pragma once
#include "Module.h"
#include "Globals.h"
#include <iostream>
#include <list>

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class Primitive;
class  PhysBody3D;

using namespace std;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	bool myToolActive = true;
	bool myTryActive = true;
	bool closeButton = false;
	bool activateAbout = false;

private:
	list<Primitive*> primitives;
};