#include "Application.h"
#include "Globals.h"
#include "ModuleRenderer3D.h"
#include "ModuleSceneIntro.h"
#include "ModuleImport.h"
#include "ModuleGameObject.h"


ModuleGameObject::ModuleGameObject(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleGameObject::~ModuleGameObject()
{}

bool ModuleGameObject::Init()
{
	return true;
}

update_status ModuleGameObject::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleGameObject::CleanUp()
{
	return true;
}