#pragma once
#include "Module.h"
#include "Globals.h"
#include "Mesh.h"

#include <iostream>
#include <list>

using namespace std;

struct PhysBody3D;
struct PhysMotor3D;
struct aiNode;
struct aiScene;
struct aiMesh;


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
	void ModuleImport::LoadAll(const char* meshPath, const char* texturePath);
	void NodeLoad(aiNode* nextNode, const aiScene* scene);
	void FileLoad(const char* file_path);
	Mesh MeshLoad(aiMesh* mesh, const aiScene* scene);

	vector<Mesh> meshes;

private:
};