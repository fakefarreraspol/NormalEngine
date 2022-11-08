#include "glew.h"

#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleImport.h"
#include "ModuleGameObject.h"

#include "SDL_opengl.h"

#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

#include "ilu.h"
#include "ilut.h"

#pragma comment (lib, "assimp-vc142-mt.lib")
#pragma comment (lib, "opengl32.lib")     /*  link Microsoft OpenGL lib  */

using namespace std;


ModuleImport::ModuleImport(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	uint id_index = 0;          // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;
	uint id_vertex = 0;         // unique vertex in VRAM
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

	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION || ilGetInteger(ILU_VERSION_NUM) < ILU_VERSION || ilGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION)
	{
		LOG("Error: DevIL Version does not match with lib version.");
	}
	else
	{
		LOG("Initializing DevIL");
		ilInit();
		iluInit();
		ilutInit();
		ilutRenderer(ILUT_OPENGL);
	}


	App->importf->ModelLoad("Assets/BakerHouse.fbx", "Assets/bakeHouse.png");

	return ret;
}

update_status ModuleImport::Update(float dt)
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleImport::CleanUp()
{
	// Detach log stream
	aiDetachAllLogStreams();

	LOG("Shutting down DevIL");
	ilShutDown();

	return true;
}

void ModuleImport::LoadAll(const char* meshPath, const char* texturePath)
{
    MeshLoad(meshPath);
    TextureLoad(texturePath);
}

void ModuleImport::ModelLoad(const char* meshPath, const char* texturePath)
{
	GameObject newGameObject;

	//Mesh Loading part
	const aiScene* scene = aiImportFile(meshPath, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		MeshVertexData vertexData;
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		TextureData textureData;
		textureData.texture_ID = 0;
		textureData.image_ID = 0;

		for (uint i = 0; i < scene->mNumMeshes; i++)
		{
			vertexData.num_vertices = scene->mMeshes[i]->mNumVertices;
			vertexData.vertices = new float[vertexData.num_vertices * 3];
			memcpy(vertexData.vertices, scene->mMeshes[i]->mVertices, sizeof(float3) * vertexData.num_vertices);
			LOG("New mesh with %d vertices", vertexData.num_vertices);

			// Copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
				vertexData.num_indices = scene->mMeshes[i]->mNumFaces * 3;
				vertexData.indices = new uint[vertexData.num_indices];			// Assume each face is a triangle

				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
				{
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else
					{
						memcpy(&vertexData.indices[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}
			}

			if (scene->mMeshes[i]->HasTextureCoords(0))
			{
				vertexData.num_UVs = scene->mMeshes[i]->mNumVertices;
				vertexData.texture_coords_indices = new float[vertexData.num_UVs * 3];
				memcpy(vertexData.texture_coords_indices, scene->mMeshes[i]->mTextureCoords[0], vertexData.num_UVs * sizeof(float3));
				vertexData.meshTexturesData.texture_ID = scene->mMeshes[i]->mMaterialIndex;
			}

			glGenBuffers(1, &vertexData.id_vertex);
			glBindBuffer(GL_ARRAY_BUFFER, vertexData.id_vertex);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.num_vertices * 3, vertexData.vertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenBuffers(1, &vertexData.id_index);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexData.id_index);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * vertexData.num_indices, vertexData.indices, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			glGenBuffers(1, &(vertexData.id_UV));
			glBindBuffer(GL_ARRAY_BUFFER, vertexData.id_UV);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.num_UVs * 3, vertexData.texture_coords_indices, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			//Texture Loading part
			if (texturePath != nullptr)
			{

				ilGenImages(1, (ILuint*)&textureData.image_ID);
				ilBindImage(textureData.image_ID);

				char* data = nullptr;
				uint file_size = App->filesyst->Load(texturePath, &data);

				ILenum fileType = IL_TYPE_UNKNOWN;

				if (App->filesyst->GetFileExtension(texturePath) == "png")
				{
					fileType = IL_PNG;
				}

				if (App->filesyst->GetFileExtension(texturePath) == "dds")
				{
					fileType = IL_DDS;
				}

				if (ilLoadL(fileType, (const void*)data, file_size))
				{
					if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
					{
						LOG("Texture correctly loaded from path: %s", texturePath);

						textureData.texture_ID = ilutGLBindTexImage(); //This fucking missing line generated the UV error - DONT erase it

						glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

						glGenTextures(1, (GLuint*)&textureData.texture_ID);
						glBindTexture(GL_TEXTURE_2D, textureData.texture_ID);

						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

						glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
						glGenerateMipmap(GL_TEXTURE_2D);
						glBindTexture(GL_TEXTURE_2D, 0);
					}
					else LOG("ERROR converting image: %s", iluErrorString(ilGetError()));
				}
				else
				{
					LOG("ERROR loading image: %s", iluErrorString(ilGetError()));
					ilDeleteImages(1, &textureData.image_ID);
				}
			}
			else LOG("ERROR loading image from path: %s", texturePath);

			if (textureData.texture_ID != 0)
			{
				textureData.path = texturePath;
				vertexData.path = meshPath;
				vertexData.meshTexturesData.path = texturePath;
				vertexData.meshTexturesData.texture_ID = textureData.texture_ID;
				vertexData.meshTexturesData.width = ilGetInteger(IL_IMAGE_WIDTH);
				vertexData.meshTexturesData.height = ilGetInteger(IL_IMAGE_HEIGHT);
			}
			newGameObject.meshes.push_back(vertexData);
		}
		newGameObject.textures.push_back(textureData);
		App->modulego->objects.push_back(newGameObject);
		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading scene % s", meshPath);
	}
}

void ModuleImport::MeshLoad(const char* path)
{
	GameObject newGameObject;

	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	MeshVertexData vertexData;

	if (scene != nullptr && scene->HasMeshes()) //The original: if (scene != nullptr && aiScene > HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (uint i = 0; i < scene->mNumMeshes; i++)
		{
			vertexData.num_vertices = scene->mMeshes[i]->mNumVertices;
			vertexData.vertices = new float[vertexData.num_vertices * 3];
			memcpy(vertexData.vertices, scene->mMeshes[i]->mVertices, sizeof(float) * vertexData.num_vertices * 3); // * 3 ?
			LOG("New mesh with %d vertices", vertexData.num_vertices);

			// Copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
				vertexData.num_indices = scene->mMeshes[i]->mNumFaces * 3;
				vertexData.indices = new uint[vertexData.num_indices]; // assume each face is a triangle

				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
				{
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else
					{
						memcpy(&vertexData.indices[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}
			}

			if (scene->mMeshes[i]->HasTextureCoords(0))
			{
				vertexData.num_UVs = scene->mMeshes[i]->mNumVertices;
				vertexData.texture_coords_indices = new float[vertexData.num_UVs * 3];
				memcpy(vertexData.texture_coords_indices, scene->mMeshes[i]->mTextureCoords[0], vertexData.num_UVs * sizeof(float3));
				vertexData.meshTexturesData.texture_ID = scene->mMeshes[i]->mMaterialIndex;
			}

			glGenBuffers(1, &vertexData.id_vertex);
			glBindBuffer(GL_ARRAY_BUFFER, vertexData.id_vertex);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.num_vertices * 3, vertexData.vertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenBuffers(1, &vertexData.id_index);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexData.id_index);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * vertexData.num_indices, vertexData.indices, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			glGenBuffers(1, &(vertexData.id_UV));
			glBindBuffer(GL_ARRAY_BUFFER, vertexData.id_UV);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.num_UVs * 3, vertexData.texture_coords_indices, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			vertexData.path = path;
			newGameObject.meshes.push_back(vertexData);
			//meshes.push_back(vertexData);
		}

		App->modulego->objects.push_back(newGameObject);
		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading scene % s", path);
	}

}

uint ModuleImport::TextureLoad(const char* path)
{
	GameObject newGameObject;
	TextureData textureData;

	textureData.texture_ID = 0;
	textureData.image_ID = 0;

	if (path != nullptr)
	{
		ilGenImages(1, (ILuint*)&textureData.image_ID);
		ilBindImage(textureData.image_ID);

		if (ilLoadImage(path))
		{
			if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
			{
				LOG("Texture correctly loaded from path: %s", path);

				textureData.texture_ID = ilutGLBindTexImage();

				glGenTextures(1, (GLuint*)&textureData.texture_ID);
				glBindTexture(GL_TEXTURE_2D, textureData.texture_ID);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

				glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else LOG("ERROR converting image: %s", iluErrorString(ilGetError()));
		}
		else LOG("ERROR loading image: %s", iluErrorString(ilGetError()));
	}
	else LOG("ERROR loading image from path: %s", path);

	textureData.path = path;
	newGameObject.textures.push_back(textureData);
	//textures.push_back(textureData);

	App->modulego->objects.push_back(newGameObject);

	return textureData.texture_ID;
}

uint ModuleImport::TextureChecker()
{
	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];

	for (int i = 0; i < CHECKERS_HEIGHT; i++)
	{
		for (int j = 0; j < CHECKERS_WIDTH; j++)
		{
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkerImage[i][j][0] = (GLubyte)c;
			checkerImage[i][j][1] = (GLubyte)c;
			checkerImage[i][j][2] = (GLubyte)c;
			checkerImage[i][j][3] = (GLubyte)255;
		}
	}

	uint textureID = 0;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, (GLuint*)&textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}