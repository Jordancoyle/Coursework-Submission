#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Common.h"

#include "Components/Component.h"

using namespace std;

class GameObject
{
public:
	typedef shared_ptr<GameObject> GameObjectSharedPtr;
	typedef vector<GameObjectSharedPtr> ChildGameObjects;
	typedef map<string, IComponent::ComponentSharedPtr> Components;
	typedef vector<IComponent::ComponentSharedPtr> ComponentList;

	GameObject();
	~GameObject();
	void setName(const string& name);
	void addChild(GameObjectSharedPtr Child);
	void addComponent(Component::ComponentSharedPtr Component);
	void addComponentToAll(Component::ComponentSharedPtr Component);

	Component::ComponentSharedPtr getComponent(const string &type);
	GameObjectSharedPtr getChild(int index);
	int getNumberOfChildren();

	void onUpdate();
	void onPreRender();
	void onRender();
	void onPostRender();
	void onInit();

	GameObject * getParent()
	{
		return m_pParent;
	};

private:
	void addComponent(GameObject * current, Component::ComponentSharedPtr Component);
	string m_Name;
	ChildGameObjects m_Children;
	Components m_Components;
	ComponentList m_ComponentList;
	GameObject * m_pParent;
};

#endif
