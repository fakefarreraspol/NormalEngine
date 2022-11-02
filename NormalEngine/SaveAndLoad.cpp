
#include "Application.h"
#include "Globals.h"
#include "Application.h"

#include "SaveAndLoad.h"

SaveAndLoad::SaveAndLoad(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

// Destructor
SaveAndLoad::~SaveAndLoad()
{
}

bool SaveAndLoad::Init()
{
	LOG("Initializing Save and Load");

	// Load Configuration.json file
	
	config = json_parse_file("configuration.json");

	return true;
}




update_status SaveAndLoad::PostUpdate(float dt) 
{
	if (saveTrigger == true)
	{
		Save();

		saveTrigger = false;
	}

	if (loadTrigger == true)
	{
		Load();

		loadTrigger = false;
	}

	return UPDATE_CONTINUE;
}

bool SaveAndLoad::CleanUp()
{
	LOG("Cleaning Save and Load");

		
	json_value_free(config);

	//delete config;

	return true;
}

bool SaveAndLoad::Save()
{
	
	App->scene_intro->SaveRequest();
	// Saving .json file
	json_serialize_to_file(config, "configuration.json");

	return true;
}

bool SaveAndLoad::Load()
{
	
	App->scene_intro->LoadRequest();
	return true;
}