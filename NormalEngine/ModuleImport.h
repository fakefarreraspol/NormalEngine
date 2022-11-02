#pragma once
#include "Application.h"
#include "Module.h"
#include "Globals.h"
#include "Mesh.h"
#include "glew.h"

#include <iostream>
#include <list>

using namespace std;

struct PhysBody3D;
struct PhysMotor3D;
struct aiNode;
struct aiScene;
struct aiMesh;

#define CHECKERS_HEIGHT 50
#define CHECKERS_WIDTH 50

enum TextureMaterialType
{
	NONE = 0,
	DIFFUSE,
	METALLIC,
	ROUGHNESS,
	HEIGH_MAP,
	NORMAL_MAP,
	EMISSIVE
};

struct TextureData
{
	TextureMaterialType materialType; //Will be used later to load different texture materials

	uint texture_ID = 0;
	uint image_ID = 0;

	uint width = 0;
	uint height = 0;

	uint format = 0;
	uint internalFormat = 0;

	const void* texture = nullptr;
	string	path;
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
	GLfloat* texture_coords_indices = nullptr;

	TextureData meshTexturesData;
	string	path;

	//TransformComponent transform; //Hacerlo en un modulo ComponentTransorm
};


class ModuleImport : public Module
{
public:
	ModuleImport(Application* app, bool start_enabled = true);
	~ModuleImport();

	// Starting
	bool Start();
	update_status Update(float dt) override;
	bool CleanUp();

	// Drawing sets
	void LoadAll(const char* meshPath, const char* texturePath);
	void ModelLoad(const char* meshPath, const char* texturePath);
	void MeshLoad(const char* path);
	uint TextureLoad(const char* path);
	uint TextureChecker();

	int testNumber = 0;

private:

};