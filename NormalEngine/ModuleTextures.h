#pragma once
#ifndef MODULE_TEXTURES_H
#define MODULE_TEXTURES_H

#include "Globals.h"
#include "Module.h"

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void LoadTexture(const char* textPath);
};
#endif // !MODULE_TEXTURES_H
