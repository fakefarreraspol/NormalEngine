#pragma once
#include "Module.h"
#include "Globals.h"
#include <iostream>
#include <list>


class Primitive;
class  PhysBody3D;

using namespace std;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();

	//TODO 9: Create an "OnCollision" method specific for this module

private:
	list<Primitive*> primitives;
};