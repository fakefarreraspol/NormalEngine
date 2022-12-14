#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "Primitive.h"
#include "glew.h"
#include "SDL_opengl.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

#include <vector> // Vector 

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

    width = SCREEN_WIDTH;
    height = SCREEN_HEIGHT;
    
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

    if (ImGui::BeginMainMenuBar())
    {
        // File tab
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Scene", "CTRL+N")) {}
            if (ImGui::MenuItem("Open Scene", "CTRL+O")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Load", "CTRL+L")) 
            {
                App->save_load->loadTrigger = true;
            }
            if (ImGui::MenuItem("Save", "CTRL+S")) 
            {
                App->save_load->saveTrigger = true;
            }
            if (ImGui::MenuItem("Save As", "CTRL+Shift+S")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("New Project")) {}
            if (ImGui::MenuItem("Open Project")) {}
            ImGui::Separator();
            if (ImGui::Button("Close"))
            {
                return UPDATE_STOP;
            }
            ImGui::EndMenu();
        }

        // Edit tab
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Select All", "CTRL+A")) {}
            if (ImGui::MenuItem("Deselect All", "Shift+D")) {}
            if (ImGui::MenuItem("Select Children", "CTRL+C")) {}
            if (ImGui::MenuItem("Invert Selection", "CTRL+I")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Duplicate", "CTRL+D")) {}
            if (ImGui::MenuItem("Rename")) {}
            if (ImGui::MenuItem("Delete")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Play", "CTRL+P")) {}
            if (ImGui::MenuItem("Pause", "CTRL+Shift+P")) {}
            ImGui::EndMenu();
        }

        // Import tab
        if (ImGui::BeginMenu("Import"))
        {
            if (ImGui::MenuItem("Cone", "CTRL+1"))
            {
                App->importf->MeshLoad("Assets/Primitives/cone.fbx");
            }

            if (ImGui::MenuItem("Cube", "CTRL+2")) 
            {
                App->importf->MeshLoad("Assets/Primitives/cube.fbx");
            }

            if (ImGui::MenuItem("Cylinder", "CTRL+3"))
            {
                App->importf->MeshLoad("Assets/Primitives/cylinder.fbx");
            }

            if (ImGui::MenuItem("Polyhedron", "CTRL+4"))
            {
                App->importf->MeshLoad("Assets/Primitives/polyhedron.fbx");
            }

            if (ImGui::MenuItem("Pyramid", "CTRL+5"))
            {
                App->importf->MeshLoad("Assets/Primitives/pyramid.fbx");
            }

            if (ImGui::MenuItem("Sphere", "CTRL+6"))
            {
                App->importf->MeshLoad("Assets/Primitives/sphere.fbx");
            }

            if (ImGui::MenuItem("Torus", "CTRL+7"))
            {
                App->importf->MeshLoad("Assets/Primitives/torus.fbx");
            }
            
            if (ImGui::MenuItem("House", "CTRL+8"))
            {
                App->importf->ModelLoad("Assets/BakerHouse.fbx", "Assets/bakeHouse.png");
            }

            if (ImGui::MenuItem("Train Station", "CTRL+9"))
            {
                App->importf->ModelLoad("Assets/BusStation.fbx", "Assets/lambert23_Base_Color.png");
            }

            ImGui::EndMenu();
        }

        // Style tab
        if (ImGui::BeginMenu("Style"))
        {
            ImGui::ShowStyleEditor();

            ImGui::EndMenu();
        }

        // Help tab
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

    ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_None);

    // Screen settings
    if (ImGui::CollapsingHeader("Screen Settings"))
    {
        ImGui::Checkbox("Fullscreen", &fullscreen);
        {
            if (fullscreen == true)
            {
                fullscreenno = true;
                App->window->FullscreenSet(fullscreen);

            }

            if (fullscreen == false)
            {
                fullscreenno = false;
                App->window->FullscreenNoSet(fullscreenno);
            }
        }

        ImGui::Checkbox("Wireframe", &boolWireframe);

        ImGui::Checkbox("Resizable", &checkResizable);

        ImGui::Checkbox("Vsync", &vsync);
        {
            App->window->ActivateVsync(App->window->vsync);
        }

        brightness = App->window->GetBrightness();
        if (ImGui::SliderFloat("Brightness", &brightness, 0.000f, 1.000f))
        {
            App->window->SetBrightness(brightness);
        }

        if (ImGui::SliderInt("Width", &App->window->width, 720, 1920))
        {
            App->window->SetWindowSize();
        }

        if (ImGui::SliderInt("Height", &App->window->height, 480, 1080))
        {
            App->window->SetWindowSize();
        }

        ImGui::Text("Updated window size: Width:"); { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "%i ", App->window->width); } { ImGui::SameLine(); ImGui::Text("Height:"); } { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "%i", App->window->height); }
        
        ImGui::Separator();
    }

    // Extra settings
    if (ImGui::CollapsingHeader("Extra Settings"))
    {
        static auto i = 100;
        ImGui::SliderInt("Volume", &i, 0, 100);

        ImGui::Separator();
    }

    // FPS graph
    if (ImGui::CollapsingHeader("FPS")) 
    {
        fps = App->GetMaxFPS();
        ImGui::SliderInt("Max FPS", &fps, 5, 144);
        ImGui::Text("Limit Framerate is at %d", fps);
        App->SetMaxFPS(fps);

        ImGui::PlotHistogram("FPS", fpsData, IM_ARRAYSIZE(fpsData), 0, NULL, 0.0f, 144.0f, ImVec2(0, 80));
        ImGui::PlotHistogram("Miliseconds", msData, IM_ARRAYSIZE(msData), 0, NULL, 0.0f, 40.0f, ImVec2(0, 80));

        ImGui::Separator();
    }

    // Other information
    if (ImGui::CollapsingHeader("Other Information"))
    {
        ImGuiIO& io = ImGui::GetIO();
        if (ImGui::TreeNode("Mouse Data"))
        {
            if (ImGui::IsMousePosValid())
            {
                ImGui::Text("Mouse pos: "); { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "(%g, %g)", io.MousePos.x, io.MousePos.y); }
            }
            else
            {
                ImGui::Text("Mouse pos: "); { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "<INVALID>"); };
            }

            ImGui::Text("Mouse delta: "); { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "(%g, %g)", io.MouseDelta.x, io.MouseDelta.y); }

            int count = IM_ARRAYSIZE(io.MouseDown);
            ImGui::Text("Mouse down: ");         for (int i = 0; i < count; i++) if (ImGui::IsMouseDown(i)) { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "b%d (%.02f secs)", i, io.MouseDownDuration[i]); }
            ImGui::Text("Mouse clicked: ");      for (int i = 0; i < count; i++) if (ImGui::IsMouseClicked(i)) { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "b%d (%d)", i, ImGui::GetMouseClickedCount(i)); }
            ImGui::Text("Mouse released: ");     for (int i = 0; i < count; i++) if (ImGui::IsMouseReleased(i)) { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "b%d", i); }
            ImGui::Text("Mouse wheel: ", io.MouseWheel); { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "%.1f", io.MouseWheel); }
            ImGui::Text("Pen Pressure: ", io.PenPressure); { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "%.1f", io.PenPressure); } // Note: currently unused
            ImGui::TreePop();
        }

        ImGui::Separator();

        if (ImGui::TreeNode("Hardware Data"))
        {
            SDL_version linked;
            SDL_GetVersion(&linked);

            ImGui::Text("System: "); { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "%s", SDL_GetPlatform()); }
            ImGui::Text("SDL Version: "); { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "%u.%u.%u", linked.major, linked.minor, linked.patch); }

            ImGui::Separator();

            ImGui::Text("CPU cores: "); { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "%d", SDL_GetCPUCount()); }
            ImGui::Text("RAM: "); { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "%.2f GB", SDL_GetSystemRAM() / 1024.0f); }

            ImGui::Text("Caps: ");
            if (SDL_HasRDTSC() == SDL_bool::SDL_TRUE)
            {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "RDTSC,");
            }
            if (SDL_HasMMX() == SDL_bool::SDL_TRUE)
            {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "MMX,");
            }
            if (SDL_HasSSE() == SDL_bool::SDL_TRUE)
            {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "SSE,");
            }
            if (SDL_HasSSE2() == SDL_bool::SDL_TRUE)
            {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "SSE2,");
            }
            if (SDL_HasSSE3() == SDL_bool::SDL_TRUE)
            {
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "SSE3,");
            }
            if (SDL_HasSSE41() == SDL_bool::SDL_TRUE)
            {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "SSE41,");
            }
            if (SDL_HasSSE42() == SDL_bool::SDL_TRUE)
            {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "SSE41,");
            }
            if (SDL_HasAVX() == SDL_bool::SDL_TRUE)
            {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "AVX,");
            }
            if (SDL_HasAVX2() == SDL_bool::SDL_TRUE)
            {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "AVX2");
            }

            ImGui::Separator();

            const GLubyte* vendor = glGetString(GL_VENDOR);
            const GLubyte* renderer = glGetString(GL_RENDERER);

            ImGui::Text("GPU:");
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "%s", vendor);

            ImGui::Text("Brand:");
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "%s", renderer);

            GLint parameter = 0;
            glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &parameter);
            ImGui::Text("VRAM budget:");
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d Mb", parameter / 1024);
            glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX, &parameter);
            ImGui::Text("VRAM usage:");
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d Mb", parameter / 1024);

            glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &parameter);
            ImGui::Text("VRAM available:");
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d Mb", parameter / 1024);

            glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX, &parameter);
            ImGui::Text("VRAM reserved:");
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d Mb", parameter / 1024);

            ImGui::TreePop();
        }
    }

    ImGui::End();

    ImGui::Begin("Object Properties", nullptr, ImGuiWindowFlags_None);

    if (ImGui::CollapsingHeader("Transformation"))
    {

    }

    if (ImGui::CollapsingHeader("Mesh"))
    {

    }

    if (ImGui::CollapsingHeader("Material"))
    {

    }

    if (ImGui::CollapsingHeader("Light"))
    {

    }

    ImGui::End();

    if (activateAbout == true)
    {
        ImGui::Begin("About", 0, ImGuiWindowFlags_MenuBar);
        {
            ImGui::Text("Normal Engine v0.1");
            ImGui::Text("The next generation Game Engine");
            ImGui::Text("Pol and Carlos (https://github.com/fakefarreraspol/NormalEngine)");

            ImGui::Text("");
            ImGui::Separator();
            ImGui::Text("");

            ImGui::Text("3rd Party Libraries used:");
            ImGui::Text("- SDL 2.0.6");
            ImGui::Text("- SDL Mixer 2.0.0");
            ImGui::Text("- Glew 2.0.0");
            ImGui::Text("- ImGui 1.51");
            ImGui::Text("- MathGeoLib 1.5");
            ImGui::Text("- OpenGL 3.1");
            ImGui::Text("- Assimp 3.1.1");

            ImGui::Text("");
            ImGui::Separator();
            ImGui::Text("");

            ImGui::Text("License:");
            ImGui::Text("MIT License");
            ImGui::Text("Copyright (c) 2022 fakefarreraspol & carlosarnau");

            ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy");
            ImGui::Text("of this software and associated documentation files(the 'Software'), to deal");
            ImGui::Text("in the Software without restriction, including without limitation the rights");
            ImGui::Text("to use, copy, modify, merge, publish, distribute, sublicense, and /or sell");
            ImGui::Text("copies of the Software, and to permit persons to whom the Software is");
            ImGui::Text("furnished to do so, subject to the following conditions:");

            ImGui::Text("The above copyright notice and this permission notice shall be included in all");
            ImGui::Text("copies or substantial portions of the Software.");

            ImGui::Text("THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR");
            ImGui::Text("IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,");
            ImGui::Text("FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE");
            ImGui::Text("AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER");
            ImGui::Text("LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,");
            ImGui::Text("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE");
            ImGui::Text("SOFTWARE.");

        }
        ImGui::End();
    }

    // Save
    if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
    {
        App->save_load->saveTrigger = true;
    }

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
    App->renderer3D->RenderModels();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::UpdateFrameData(int frames, int ms)
{
    for (uint i = 0; i < (MAX_HISTOGRAM_SIZE - 1); ++i)
    {
        fpsData[i] = fpsData[i + 1];
        msData[i] = msData[i + 1];
    }
    fpsData[MAX_HISTOGRAM_SIZE - 1] = (float)frames;
    msData[MAX_HISTOGRAM_SIZE - 1] = (float)ms;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

bool ModuleSceneIntro::SaveRequest()
{
    json_object_dotset_boolean(json_object(App->save_load->config), "Fullscreen", fullscreen);
    json_object_dotset_boolean(json_object(App->save_load->config), "Vsync", vsync);
    json_object_dotset_boolean(json_object(App->save_load->config), "Wireframe", boolWireframe);
    json_object_dotset_boolean(json_object(App->save_load->config), "Resizable", checkResizable);

    json_object_dotset_boolean(json_object(App->save_load->config), "Depth", activateDepthTest);
    json_object_dotset_boolean(json_object(App->save_load->config), "CullFace", activateCullFace);
    json_object_dotset_boolean(json_object(App->save_load->config), "Light", activateLightning);
    json_object_dotset_boolean(json_object(App->save_load->config), "ColorMaterial", activateColorMaterial);
    json_object_dotset_boolean(json_object(App->save_load->config), "Texture2D", activateTexture2D);

    json_object_dotset_number(json_object(App->save_load->config), "Brightness", brightness);
    json_object_dotset_number(json_object(App->save_load->config), "Width", width);
    json_object_dotset_number(json_object(App->save_load->config), "Height", height);

    return true;
}

bool ModuleSceneIntro::LoadRequest()
{
    fullscreen = (bool)json_object_dotget_boolean(json_object(App->save_load->config), "Fullscreen");
    vsync = (bool)json_object_dotget_boolean(json_object(App->save_load->config), "Vsync");
    boolWireframe = (bool)json_object_dotget_boolean(json_object(App->save_load->config), "Wireframe");
    checkResizable = (bool)json_object_dotget_boolean(json_object(App->save_load->config), "Resizable");

    activateDepthTest = (bool)json_object_dotget_boolean(json_object(App->save_load->config), "Depth");
    activateCullFace = (bool)json_object_dotget_boolean(json_object(App->save_load->config), "CullFace");
    activateLightning = (bool)json_object_dotget_boolean(json_object(App->save_load->config), "Light");
    activateColorMaterial = (bool)json_object_dotget_boolean(json_object(App->save_load->config), "ColorMaterial");
    activateTexture2D = (bool)json_object_dotget_boolean(json_object(App->save_load->config), "Texture2D");
    
    brightness = (int)json_object_dotget_number(json_object(App->save_load->config), "Brightness");
    width = (int)json_object_dotget_number(json_object(App->save_load->config), "Width");
    height = (int)json_object_dotget_number(json_object(App->save_load->config), "Height");
    App->window->SetWindowSize();
    return true;
}