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
	int testNumber = 0;
private:
};


struct MeshVertexData
{

	uint id_index = 0; // index in VRAM
	uint num_indices = 0;
	uint* indices = nullptr;

	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertices = 0;
	float* vertices = nullptr;

	/*GLuint id_normal = 0;
	aiVector3D num_normals[3] = {};
	float* normals = nullptr;

	GLuint id_normalVertices = 0;
	GLfloat* normalVertices = nullptr;*/

	uint id_UV = 0; // id of the UV
	uint num_UVs = 0;
	//GLfloat* texture_coords_indices = nullptr;

	//TextureData meshTexturesData;
	std::string	path;

	
	//TransformComponent transform; //Hacerlo en un modulo ComponentTransorm
};