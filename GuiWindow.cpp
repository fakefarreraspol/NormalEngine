#include "GuiWindow.h"
#include "ModuleWindow.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


void GuiWindow::Create()
{
	IMGUI_CHECKVERSION();
	
	ImGui::CreateContext();
	
	//ImGui_ImplSDL2_InitForOpenGL();
}