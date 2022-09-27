#ifndef __GuiWindow_H_
#define __GuiWindow_H_
#include "Application.h"

#include "Globals.h"



class GuiWindow:public Module
{
public:

	GuiWindow(){}
	~GuiWindow(){}

	void Create();
	void ShutDown();

	void HandleSDLEvent(SDL_Event& event);
	
	void BeginRender();
	void EndRender();

private:




};











#endif // __GuiWindow_H_
