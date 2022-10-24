#include "Application.h"


Application::Application() : debug(false)
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this, true);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	scene_intro = new ModuleSceneIntro(this);
	save_load = new SaveAndLoad(this);
	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(audio);
	
	// Scenes
	AddModule(scene_intro);
	

	// Renderer last!
	AddModule(renderer3D);
	

	AddModule(save_load);
}

Application::~Application()
{
	list<Module*>::iterator item = list_modules.end();

	while(list_modules.empty() == true)
	{
		item = list_modules.erase(item);
		item--;
	}
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	list<Module*>::iterator item = list_modules.begin();

	while(item != list_modules.end() && ret == true)
	{
		ret = item._Ptr->_Myval->Init();
		item++;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");

	item = list_modules.begin();

	while (item != list_modules.end() && ret == true) {

		ret = item._Ptr->_Myval->Start();
		item++;
	}
	
	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	frameCount++;
	lastSecFrameCount++;
	dt = frameDuration.ReadMs();
	frameDuration.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	float secondsSinceStartup = startupTime.Read();

	if (lastSecFrameTime.Read() > 1000) {
		lastSecFrameTime.Start();
		framesPerSecond = lastSecFrameCount;
		lastSecFrameCount = 0;
		averageFps = (averageFps + framesPerSecond) / 2;
	}

	static char title[256];

	sprintf_s(title, 256, "FPS: %i Tile:[%d,%d] ", framesPerSecond);

	float delay = float(1000 / maxFrameRate) - frameDuration.ReadMs();

	PTimer* delayt = new PTimer();
	delayt->Start();
	if (maxFrameRate > 0 && delay > 0) SDL_Delay(delay);

	window->SetTitle(title);
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end() && ret == true) {

		ret = item._Ptr->_Myval->PreUpdate(dt);
		item++;
	}

	item = list_modules.begin();

	while (item != list_modules.end() && ret == true) {

		ret = item._Ptr->_Myval->Update(dt);
		item++;
	}

	item = list_modules.begin();

	while (item != list_modules.end() && ret == true) {

		ret = item._Ptr->_Myval->PostUpdate(dt);
		item++;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end() && ret == true) {

		ret = item._Ptr->_Myval->CleanUp();
		item++;
	}

	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}