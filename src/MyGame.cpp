#include "MyGame.h"

Vertex verts[] = {
	//Front
	{ vec3(-0.5f, 0.5f, 0.5f),
	vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec2(0.0f, 0.0f) },// Top Left

		{ vec3(-0.5f, -0.5f, 0.5f), 
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec2(0.0f, 1.0f)  },// Bottom Left

	{ vec3(0.5f, -0.5f, 0.5f),
	vec4(1.0f, 1.0f, 1.0f, 1.0f),
	vec2(1.0f, 1.0f) }, //Bottom Right

	{ vec3(0.5f, 0.5f, 0.5f), 
	vec4(1.0f, 1.0f, 1.0f, 1.0f),
	vec2(1.0f, 0.0f)},// Top Right


	//back
	{ vec3(-0.5f, 0.5f, -0.5f), vec4(1.0f, 1.0f, 1.0f, 1.0f),
	vec2(0.0f, 0.0f)},// Top Left

	{ vec3(-0.5f, -0.5f, -0.5f), vec4(1.0f, 1.0f, 1.0f, 1.0f),
	vec2(0.0f, 1.0f) },// Bottom Left

	{ vec3(0.5f, -0.5f, -0.5f), vec4(1.0f, 1.0f, 1.0f, 1.0f),
	vec2(1.0f, 1.0f) }, //Bottom Right

	{ vec3(0.5f, 0.5f, -0.5f), vec4(1.0f, 1.0f, 1.0f, 1.0f),
	vec2(1.0f, 0.0f)},// Top Right

};

int indices[] = {
	//front
	0, 1, 2,
	0, 3, 2
	/*
	//left
	4, 5, 1,
	4, 1, 0,

	//right
	3, 7, 2,
	7, 6, 2,

	//bottom
	1, 5, 2,
	6, 2, 5,

	//top
	4, 0, 7,
	0, 7, 3,

	//back
	4, 5, 6,
	4, 7, 6*/
};

MyGame::MyGame()
{

}

MyGame::~MyGame()
{

}

void MyGame::initScene()
{
	auto pObj=shared_ptr<GameObject>(new GameObject);
	pObj->setName("Cube");
	auto transform = shared_ptr<Transform>(new Transform);
	transform->setPosition(vec3(5, 0.0, 0.0));
	pObj->addComponent(transform);

	auto pMesh = shared_ptr<Mesh>(new Mesh);
	pMesh->init(verts, 8, indices, 6);
	pObj->addComponent(pMesh);

	auto pShader = shared_ptr<Shader>(new Shader);
	string vsFilename = ASSET_PATH + SHADER_PATH + "/textureVS.glsl";
	string fsFilename = ASSET_PATH + SHADER_PATH + "/textureFS.glsl";
	pShader->loadShaderFromFiles(vsFilename, fsFilename);
	pShader->link();

	auto pMaterial = shared_ptr<Material>(new Material);
	string texturePath = ASSET_PATH + TEXTURE_PATH + "/texture.png";
	pMaterial->loadDiffuseTexture(texturePath);
	pMaterial->setShader(pShader);
	pObj->addComponent(pMaterial);
	m_GameObjects.push_back(pObj);

	//Create new shader
	pShader = shared_ptr<Shader>(new Shader);
	vsFilename = ASSET_PATH + SHADER_PATH + "/textureVS.glsl";
	fsFilename = ASSET_PATH + SHADER_PATH + "/textureFS.glsl";
	pShader->loadShaderFromFiles(vsFilename, fsFilename);
	pShader->link();

	pMaterial = shared_ptr<Material>(new Material);
	texturePath = ASSET_PATH + TEXTURE_PATH + "/armoredrecon_diff.png";
	pMaterial->loadDiffuseTexture(texturePath);
	pMaterial->setShader(pShader);

	string modelFile = ASSET_PATH + MODEL_PATH + "/armoredrecon.fbx";
	auto armoredreconModel=loadFBXFromFile(modelFile);
	armoredreconModel->addComponentToAll(pMaterial);
	m_GameObjects.push_back(armoredreconModel);

	GameApplication::initScene();
}
