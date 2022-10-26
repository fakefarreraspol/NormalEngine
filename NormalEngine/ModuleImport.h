#pragma once
#include "Module.h"
#include "Globals.h"
#include <iostream>
#include <list>

using namespace std;


class ModuleImport : public Module
{
public:
	ModuleImport(Application* app, bool start_enabled = true);
	~ModuleImport();

	bool Start();
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();

	// Drawing primitives
	void DrawCube();
	void DrawSphere();
	void DrawPyramid();

	// Drawing sets
	void DrawHouse();
	void DrawStation();

private:

};