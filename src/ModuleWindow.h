#pragma once
#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL.h"


class Application;

class ModuleWindow : public Module
{
public:
	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

	void SetTitle(const char* title);
	void FullscreenSet(bool fullscreen);
	void FullscreenNoSet(bool fullscreenno);
	void Vsync(bool fullscreenno);

	SDL_Window* GetSDLWindow()
	{
		return window;
	}

public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;
};

#endif // __ModuleWindow_H__