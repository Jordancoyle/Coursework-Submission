#ifndef _INPUT_H
#define _INPUT_H

#include "Common.h"

class Input
{
public:
	Input();
	~Input();

	void inputDetection();

	void setInputEvent(SDL_Event tempEvent)
	{
		inputEvent = tempEvent;
	}
private:
	SDL_Event inputEvent;
protected:
};

#endif