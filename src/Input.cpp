#include "Input.h"
#include "Common.h"

Input::Input()
{

}

Input::~Input()
{

}

void Input::inputDetection()
{
	switch (inputEvent.key.keysym.sym)
	{
	case SDLK_LEFT:
		cout << "left" << endl;
		break;
	case SDLK_RIGHT:
		cout << "right" << endl;
		break;
	case SDLK_UP:
		cout << "up" << endl;
		break;
	case SDLK_DOWN:
		cout << "down" << endl;
		break;
	default:
		break;
	}
}