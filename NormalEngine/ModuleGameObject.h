#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "Application.h"
#include "Module.h"
#include "ModuleImport.h"
#include <vector>

using namespace std;

struct GameObject
{
	uint objectID;

	vector<MeshVertexData> meshes;
	vector<TextureData> textures;
	//vector<TransformComponent> transformComponents;
};


class ModuleGameObject : public Module
{
public:
	ModuleGameObject(Application* app, bool start_enabled = true);
	~ModuleGameObject();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

public:
	vector<GameObject> objects;

};

#endif // !_GAME_OBJECT