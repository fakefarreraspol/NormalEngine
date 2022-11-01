#pragma once
#ifndef __SAVEANDLOAD_H__
#define __SAVEANDLOAD_H__


#include "Module.h"
#include "SDL.h"
#include "parson.h"






class SaveAndLoad : public Module
{
public:

	SaveAndLoad(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~SaveAndLoad();

	bool Init();
	update_status PostUpdate(float dt) override;
	bool CleanUp();

	bool Load();
	bool Save();

	bool loadTrigger = false;
	bool saveTrigger = false;

	JSON_Value* config = nullptr;

};

#endif // __SAVEANDLOAD_H__

