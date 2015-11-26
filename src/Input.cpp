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
		camera->moveLeft();
		cout << "left" << endl;
		break;
	case SDLK_RIGHT:
		camera->moveRight();
		cout << "right" << endl;
		break;
	case SDLK_UP:
		camera->moveForward();
		cout << "up" << endl;
		break;
	case SDLK_DOWN:
		camera->moveBackward();
		cout << "down" << endl;
		break;
	default:
		break;
	}
}