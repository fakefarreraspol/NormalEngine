#include "SaveAndLoad.h"
#include "Application.h"
#include "Globals.h"
#include "Application.h"



SaveAndLoad::SaveAndLoad(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

// Destructor
SaveAndLoad::~SaveAndLoad()
{
}

bool SaveAndLoad::Init()
{
	LOG("Initializing ModuleSaveLoad");

	// Load Configuration.json file
	//config = json_parse_file("Configuration.json");

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
	LOG("Cleaning ModuleSaveLoad");

	// Free file ptr
	//json_value_free(config);

	//delete configurationFile;

	return true;
}

bool SaveAndLoad::Save()
{
	

	// Aplying save to the .json file
	//json_serialize_to_file(config, "movistar");

	return true;
}

bool SaveAndLoad::Load()
{
	

	return true;
}