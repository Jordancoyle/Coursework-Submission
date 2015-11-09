#ifndef _GAMEAPPLICATION_H
#define _GAMEAPPLICATION_H

#include "Common.h"
#include "FileSystem.h"
#include "Graphics.h"
#include "GameObject.h"
#include "Components/Components.h"
#include "FBXLoader.h"

class GameApplication
{
public:
	GameApplication();
	virtual ~GameApplication();

	virtual bool init();
	virtual void initScene();
	virtual void update();
	virtual void render();
	virtual void destroy();

	void render(GameObject::GameObjectSharedPtr gObj);
	void run();
protected:
	SDL_Window * m_pWindow;
	SDL_GLContext m_glcontext;
	bool m_bIsRunning;
	vector<GameObject::GameObjectSharedPtr> m_GameObjects;
	GameObject::GameObjectSharedPtr m_MainCamera;

};
#endif
