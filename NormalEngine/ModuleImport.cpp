#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleImport.h"

#include "SDL_opengl.h"
#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

#pragma comment (lib, "assimp-vc142-mt.lib")
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleImport::ModuleImport(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

// Destructor
ModuleImport::~ModuleImport()
{}

// Called before render is available
bool ModuleImport::Start()
{
	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

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

void ModuleImport::DrawCube()
{

}

void ModuleImport::DrawSphere()
{

}

void ModuleImport::DrawPyramid()
{

}

void ModuleImport::DrawHouse()
{

}

void ModuleImport::DrawStation()
{

}