#include "glew.h"
#include "Globals.h"

#include "Application.h"


#include "ModuleSceneIntro.h"
#include "ModuleImport.h"

#include "SDL_opengl.h"

#include "cimport.h"
#include "scene.h"
#include "postprocess.h"



#pragma comment (lib, "assimp-vc142-mt.lib")
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

using namespace std;


ModuleImport::ModuleImport(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;
}

// Destructor
ModuleImport::~ModuleImport()
{}

// Called before render is available
bool ModuleImport::Start()
{
    LOG("Loading Intro assets");
    bool ret = true;

	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	/*const char* filepath = ("Assets\BakerHouse.fbx");
	FileLoad(filepath);*/

	return ret;
}

// Called before quitting
bool ModuleImport::CleanUp()
{
	// Detach log stream
	aiDetachAllLogStreams();

	return true;
}

update_status ModuleImport::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleImport::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

void ModuleImport::LoadAll(const char* meshPath, const char* texturePath)
{
    // FileLoad(file_path);
    // LoadTexture(texturePath);
}

void ModuleImport::NodeLoad(aiNode* nextNode, const aiScene* scene)
{
    for (int i = 0; i < nextNode->mNumMeshes; i++)
    {
        aiMesh* aux = scene->mMeshes[nextNode->mMeshes[i]];
        meshes.push_back(MeshLoad(aux, scene));
    }

    for (unsigned int i = 0; i < nextNode->mNumChildren; i++)
    {
        NodeLoad(nextNode->mChildren[i], scene);
    }
}

Mesh ModuleImport::MeshLoad(aiMesh* mesh, const aiScene* scene)
{
    //temporary varaibles to store the mesh data
    vector<Vertex> vertices;
    vector<int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        float3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    return Mesh(vertices, indices);
}

void ModuleImport::FileLoad(const char* file_path)
{
    
	if (file_path != nullptr)
	{
		const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
		if (scene != nullptr && scene->HasMeshes())
		{
		    // Use scene->mNumMeshes to iterate on scene->mMeshes array
		    NodeLoad(scene->mRootNode, scene);

		    aiReleaseImport(scene);
		}
		else
		{
		    const char* a = aiGetErrorString();
		}

		if (scene == nullptr)
		{
			testNumber = 2;
			//Texto de ejemplo

		}

		//const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
		//MeshVertexData vertexData;
		////aiMesh* mesh = nullptr;

		//if (scene != nullptr && scene->HasMeshes()) //The original: if (scene != nullptr && aiScene > HasMeshes())
		//{
		//	// Use scene->mNumMeshes to iterate on scene->mMeshes array

		//	for (uint i = 0; i < scene->mNumMeshes; i++)
		//	{

		//		vertexData.num_vertices = scene->mMeshes[i]->mNumVertices;
		//		vertexData.vertices = new float[vertexData.num_vertices * 3];
		//		memcpy(vertexData.vertices, scene->mMeshes[i]->mVertices, sizeof(float) * vertexData.num_vertices * 3); // * 3 ?
		//		LOG("New mesh with %d vertices", vertexData.num_vertices);

		//		// copy faces
		//		if (scene->mMeshes[i]->HasFaces())
		//		{
		//			vertexData.num_indices = scene->mMeshes[i]->mNumFaces * 3;
		//			vertexData.indices = new uint[vertexData.num_indices]; // assume each face is a triangle

		//			for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
		//			{
		//				if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3)
		//				{
		//					LOG("WARNING, geometry face with != 3 indices!");
		//				}
		//				else
		//				{
		//					memcpy(&vertexData.indices[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
		//				}
		//			}
		//		}

		//		/*if (scene->mMeshes[i]->HasTextureCoords(0))
		//		{
		//			vertexData.num_UVs = scene->mMeshes[i]->mNumVertices;
		//			vertexData.texture_coords_indices = new float[vertexData.num_UVs * 3];
		//			memcpy(vertexData.texture_coords_indices, scene->mMeshes[i]->mTextureCoords[0], vertexData.num_UVs * sizeof(float3));
		//			vertexData.meshTexturesData.texture_ID = scene->mMeshes[i]->mMaterialIndex;
		//		}*/
		//		

		//		glGenBuffers(1, &vertexData.id_vertex);
		//		glBindBuffer(GL_ARRAY_BUFFER, vertexData.id_vertex);
		//		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.num_vertices * 3, vertexData.vertices, GL_STATIC_DRAW);
		//		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//		glGenBuffers(1, &vertexData.id_index);
		//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexData.id_index);
		//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * vertexData.num_indices, vertexData.indices, GL_STATIC_DRAW);
		//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//		glGenBuffers(1, &(vertexData.id_UV));
		//		glBindBuffer(GL_ARRAY_BUFFER, vertexData.id_UV);
		//		//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.num_UVs * 3, vertexData.texture_coords_indices, GL_STATIC_DRAW);
		//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//		vertexData.path = file_path;
		//		//newGameObject.meshes.push_back(vertexData);
		//		//meshes.push_back(vertexData);
		//	}

		//	//App->moduleGameObject->objects.push_back(newGameObject);
		//	aiReleaseImport(scene);


		//}
	}
    
    
}

void ModuleImport::DrawCube()
{

}

void ModuleImport::DrawSphere()
{

}

void ModuleImport::DrawPyramid()
{

}