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

	const char* filepath = ("NormalEngine\Game\Assets\BakerHouse.fbx");
	FileLoad(filepath);

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