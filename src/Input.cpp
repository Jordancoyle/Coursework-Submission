#include "Input.h"
#include "Common.h"

Input::Input()
{

}

Input::~Input()
{

}

void Input::inputDetection(shared_ptr<Camera> camera)
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
		camera->moveForward();
		cout << "up" << endl;
		break;
	case SDLK_DOWN:
		cout << "down" << endl;
		break;
	default:
		break;
	}
}