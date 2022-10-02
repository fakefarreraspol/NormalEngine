#include "PTimer.h"
#include "SDL_timer.h"

float PTimer::frequency = 0;


// L07: DONE 2: Fill Constructor, Start(),ReadMs() and ReadTicks() methods
// they are simple, one line each!

PTimer::PTimer()
{
	if (frequency == 0) frequency = SDL_GetPerformanceFrequency();

	Start();
}

void PTimer::Start()
{
	startTime = SDL_GetPerformanceCounter();
}

double PTimer::ReadMs() const
{
	return 1000.0 * (double(SDL_GetPerformanceCounter() - startTime) / double(frequency));
}

float PTimer::ReadTicks() const
{
	return SDL_GetPerformanceCounter() - startTime;
}