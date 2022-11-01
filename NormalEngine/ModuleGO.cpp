#include "Application.h"
#include "Globals.h"
#include "ModuleRenderer3D.h"
#include "ModuleSceneIntro.h"
#include "ModuleImport.h"
#include "ModuleGO.h"


ModuleGO::ModuleGO(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleGO::~ModuleGO()
{}

bool ModuleGO::Init()
{
	return true;
}

update_status ModuleGO::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleGO::CleanUp()
{
	return true;
}