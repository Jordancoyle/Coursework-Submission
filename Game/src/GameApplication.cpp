#include "GameApplication.h"

GameApplication::GameApplication()
{

}

GameApplication::~GameApplication()
{
	destroy();
}

bool GameApplication::init()
{
	ChangeWorkingDirectory();
	//Controls the game loop
	m_bIsRunning = true;

	// init everyting - SDL, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init " << SDL_GetError() << std::endl;

		return false;
	}
	//
	int	imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int	returnInitFlags = IMG_Init(imageInitFlags);
	if (((returnInitFlags)&	(imageInitFlags)) != imageInitFlags)	{

		cout << "ERROR	SDL_Image	Init	" << IMG_GetError() << endl;
		return false;
	}

	if (TTF_Init() == -1)	{
		std::cout << "ERROR	TTF_Init:	" << TTF_GetError();
		return false;
	}

	//Request opengl 4.1 context, Core Context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	//Create a window
	m_pWindow = SDL_CreateWindow(
		"SDL",             // window title
		SDL_WINDOWPOS_CENTERED,     // x position, centered
		SDL_WINDOWPOS_CENTERED,     // y position, centered
		640,                        // width, in pixels
		480,                        // height, in pixels
		SDL_WINDOW_OPENGL           // flags
		);

	// Create an OpenGL context associated with the window.
	m_glcontext = SDL_GL_CreateContext(m_pWindow);

	//Call our InitOpenGL Function
	initOpenGL();
	//Set our viewport
	setViewport(640, 480);
	initScene();

	return true;
}

void GameApplication::initScene()
{
	m_MainCamera=shared_ptr<GameObject>(new GameObject);
	m_MainCamera->setName("Main Camera");
	auto t=shared_ptr<Transform>(new Transform);
	t->setPosition(vec3(0.0f,0.0f,10.0f));
	//create camera component
	auto c=shared_ptr<Camera>(new Camera);
	c->setFOV(45.0f);
	c->setAspectRatio(640.0f/480.0f);
	c->setNearClip(0.1f);
	c->setFarClip(1000.0f);

	m_MainCamera->addComponent(c);
	m_MainCamera->addComponent(t);
	m_GameObjects.push_back(m_MainCamera);

	for (auto it=m_GameObjects.begin();it!=m_GameObjects.end();++it)
	{
		(*it)->onInit();
	}
}

void GameApplication::update()
{
	for (auto it=m_GameObjects.begin();it!=m_GameObjects.end();it++)
	{
		(*it)->onUpdate();
	}
}

void GameApplication::render(GameObject::GameObjectSharedPtr gObj)
{

	gObj->onPreRender();
	//grab current material
	auto mat=static_pointer_cast<Material>(gObj->getComponent("Material"));
	if (mat)
	{
		//cout<<"Grabing Material"<<endl;
		//grab shader
		auto shader=mat->getShader();
		auto camera=static_pointer_cast<Camera>(m_MainCamera->getComponent("Camera"));
		//grab transform
		auto t=static_pointer_cast<Transform>(gObj->getComponent("Transform"));
		//send values to shader
		if (shader){
			GLint MVPMatrixLocation=shader->getUniformLocation("MVP");
			if (camera && t){
				mat4 modelMatrix=t->getModelMatrix();
				mat4 viewMatrix=camera->getView();
				mat4 projectionMatrix=camera->getProjection();
				mat4 MVPMatrix=projectionMatrix*viewMatrix*modelMatrix;
				shader->setUniformMatrix4f(MVPMatrixLocation,MVPMatrix);
			}
		}

	}
	gObj->onRender();

	gObj->onPostRender();
	//go through children
	for (int i=0;i<gObj->getNumberOfChildren();i++)
	{
		render(gObj->getChild(i));
	}
}

void GameApplication::render()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	//Set the clear colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//Clear the depth buffer
	glClearDepth(1.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto it=m_GameObjects.begin();it!=m_GameObjects.end();++it)
	{
		render((*it));
	}
}

void GameApplication::destroy()
{
	// clean up, reverse order!!!
	m_GameObjects.clear();
	SDL_GL_DeleteContext(m_glcontext);
	SDL_DestroyWindow(m_pWindow);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void GameApplication::run()
{
	SDL_Event event;
	//Game Loop
	while (m_bIsRunning)
	{
		//While we still have events in the queue
		while (SDL_PollEvent(&event)) {
			//Get event type
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				//set our boolean which controls the loop to false
				m_bIsRunning = false;
			}
		}
		//init Scene
		update();
		//render
		render();
		//Call swap so that our GL back buffer is displayed
		SDL_GL_SwapWindow(m_pWindow);

	}
}
