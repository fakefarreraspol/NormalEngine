#ifndef __PERFTIMER_H__
#define __PERFTIMER_H__


class PTimer
{
public:
	// Constructor
	PTimer();

	void Start();
	double ReadMs() const;
	float ReadTicks() const;

private:
	float startTime;
	static float frequency;
};

#endif //__PERFTIMER_H__