#include "Globals.h"
#include "Application.h"
#include "ModuleImport.h"

#pragma comment (lib, "assimp-vc142-mt.lib")


ModuleImport::ModuleImport(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

// Destructor
ModuleImport::~ModuleImport()
{}

// Called before render is available
bool ModuleImport::Start()
{
	return true;
}

// Called before quitting
bool ModuleImport::CleanUp()
{
	// detach log stream
	aiDetachAllLogStreams();

	return true;
}

update_status ModuleImport::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleImport::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}