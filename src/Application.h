#pragma once

#include <iostream>
#include <list>
#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "PTimer.h"

using namespace std;


class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleSceneIntro* scene_intro;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	
	bool debug;

private:
	Timer	ms_timer;
	float	dt;
	list<Module*> list_modules;

public:
	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	// Timer things
	PTimer perftimer;
	PTimer frameDuration;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;

	float frameCount = 0;
	int framesPerSecond = 0;
	int lastSecFrameCount = 0;
	bool FPSCapTo30 = false;
	float averageFps = 0.0f;
	int maxFrameRate = 30;

private:
	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};