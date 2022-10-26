#pragma once
#ifndef __ModuleImport_H__
#define __ModuleImport_H__

#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

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

private:

};

#endif // __ModuleImport_H__