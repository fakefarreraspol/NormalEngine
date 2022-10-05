#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "SDL_opengl.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

#pragma comment (lib, "assimp-vc142-mt.lib")
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	IMGUI_CHECKVERSION();
	void* context = ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	for (int n = 0; n < primitives.size(); n++)
	{
		primitives.clear();
	}

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

    // Render a color-cube consisting of 6 quads with different colors
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
       // Top face (y = 1.0f)
       // Define vertices in counter-clockwise (CCW) order with normal pointing out
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(1.0f, 2.0f, -1.0f);
    glVertex3f(-1.0f, 2.0f, -1.0f);
    glVertex3f(-1.0f, 2.0f, 1.0f);
    glVertex3f(1.0f, 2.0f, 1.0f);

    // Bottom face (y = -1.0f)
    glColor3f(1.0f, 0.5f, 0.0f);     // Orange
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);

    // Front face  (z = 1.0f)
    glColor3f(1.0f, 1.0f, 0.0f);     // Red
    glVertex3f(1.0f, 2.0f, 1.0f);
    glVertex3f(-1.0f, 2.0f, 1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);

    // Back face (z = -1.0f)
    glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
    glVertex3f(1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 2.0f, -1.0f);
    glVertex3f(1.0f, 2.0f, -1.0f);

    // Left face (x = -1.0f)
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(-1.0f, 2.0f, 1.0f);
    glVertex3f(-1.0f, 2.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);

    // Right face (x = 1.0f)
    glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
    glVertex3f(1.0f, 2.0f, -1.0f);
    glVertex3f(1.0f, 2.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glEnd();  // End of drawing color-cube

	if (App->debug == true)
	{
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			//TODO 3: Create a "new" sphere, and add it to the "primitives" DynArray

			//TODO 9: Push ModuleSceneIntro to the sphere collision listeners
		}
	}

	//TODO 3: Nothing to do here. But it's good to know where all primitives are being updated
	for (uint n = 0; n < primitives.size(); n++)
	{
		primitives.begin();
	}

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();

    //ImGui::Begin("Custom window",0, ImGuiWindowFlags_MenuBar);

    ImGui::ShowDemoWindow();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::Button("Close"))
            {
                return UPDATE_STOP;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::Button("About"))
            {
                activateAbout = !activateAbout;

            }

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (activateAbout == true)
    {
        ImGui::Begin("About", 0, ImGuiWindowFlags_MenuBar);
        {
            ImGui::Text("Normal Engine");
            ImGui::Text("vg motor");
            ImGui::Text("Pol and Carlos (https://github.com/fakefarreraspol/NormalEngine)");
            ImGui::Text("We have the Mathegeolib, the glew, the JSON and the SDL");
            ImGui::Text("License");
        }
        ImGui::End();
    }

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	//TODO 3: Nothing to do here. But it's good to know where all primitives are being rendered
	for (uint n = 0; n < primitives.size(); n++)
	{
		primitives.rend();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}