#include "glew.h"

#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleImport.h"
#include "ModuleGameObject.h"
#include "SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "SDL_opengl.h"

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "glew32s.lib")


ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOG("Creating 3D Renderer context");
	bool ret = true;
	
	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if(context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	
	if(ret == true)
	{
		// Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		// Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Check for error
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		// Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		// Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		// Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
	}
	GLenum error = glewInit();
	if (GLEW_OK != error)
	{
		LOG("Glew failed, Error: %s\n", glewGetErrorString(error));
	}
	LOG("Glew version: %s\n", glewGetString(GLEW_VERSION));

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	return UPDATE_CONTINUE;
}

update_status ModuleRenderer3D::Update(float dt)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AMBIENT);

	if (wireframeMode == false)
	{
		// Turns off wiremode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (wireframeMode == true)
	{
		// Turns on wiremode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (faceCullingMode == false)
	{
		// Turns off wiremode
		glDisable(GL_CULL_FACE);
	}
	else if (faceCullingMode == true)
	{
		// Turns on wiremode
		glEnable(GL_CULL_FACE);
	}

	if (texturesOFF == false)
	{
		// Turns on textures
		glEnable(GL_TEXTURE_2D);
	}
	else if (texturesOFF == true)
	{
		// Turns off textures
		glDisable(GL_TEXTURE_2D);
	}

	if (disableLights == false)
	{
		// Turns on textures
		glEnable(GL_LIGHTING);
	}
	else if (disableLights == true)
	{
		// Turns off textures
		glDisable(GL_LIGHTING);
	}

	if (disableAO == false)
	{
		// Turns on textures
		glEnable(GL_AMBIENT);
	}
	else if (disableAO == true)
	{
		// Turns off textures
		glDisable(GL_AMBIENT);
	}

	return UPDATE_CONTINUE;
}

update_status ModuleRenderer3D::PostUpdate(float dt)
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

bool ModuleRenderer3D::CleanUp()
{
	LOG("Destroying 3D Renderer");

	SDL_GL_DeleteContext(context);

	return true;
}

void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ModuleRenderer3D::RenderModels()
{
	for (int i = 0; i < App->modulego->objects.size(); i++)
	{
		for (int j = 0; j < App->modulego->objects[i].meshes.size(); j++)
		{
			// Draw elements
			MeshVertexData* vertexData = &App->modulego->objects[i].meshes[j];

			glEnableClientState(GL_VERTEX_ARRAY);

			// Render things in Element mode
			glBindBuffer(GL_ARRAY_BUFFER, vertexData->id_vertex);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexData->id_index);

			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, vertexData->id_UV);
			glTexCoordPointer(3, GL_FLOAT, 0, NULL);
			glBindTexture(GL_TEXTURE_2D, vertexData->meshTexturesData.texture_ID);

			glDrawElements(GL_TRIANGLES, vertexData->num_indices, GL_UNSIGNED_INT, NULL);

			glBindTexture(GL_TEXTURE_2D, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
		}
	}
}