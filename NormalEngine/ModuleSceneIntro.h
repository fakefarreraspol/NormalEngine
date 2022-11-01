#pragma once
#include "Module.h"
#include "Globals.h"
#include <iostream>
#include <list>

#define MAX_SNAKE 2
#define MAX_HISTOGRAM_SIZE 100

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

	void UpdateFrameData(int frames, int ms);
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	SDL_Window* window;

	bool SaveRequest();
	// Buttons
	bool myToolActive = true;
	bool myTryActive = true;
	bool closeButton = false;
	bool activateAbout = false;

	// Screen
	float brightness = 1.000f;
	int width;
	int height;
	bool fullscreen = false;
	bool fullscreenno = false;
	bool vsync = false;
	bool boolWireframe = false;
	bool checkResizable = false;

	// Textures
	bool activateDepthTest = false;
	bool activateCullFace = false;
	bool activateLightning = false;
	bool activateColorMaterial = false;
	bool activateTexture2D = false;

	const char* name;

	const char* GetName()const
	{
		return name;
	}

	// FPS Values
	int fps;
	float fpsData[MAX_HISTOGRAM_SIZE];
	float msData[MAX_HISTOGRAM_SIZE];

private:
	list<Primitive*> primitives;
};