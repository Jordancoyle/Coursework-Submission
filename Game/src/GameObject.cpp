#include "GameObject.h"


GameObject::GameObject()
{
	m_Name="GameObject";
	m_pParent=NULL;
	m_Children.clear();
	m_Components.clear();
	m_ComponentList.clear();
}

GameObject::~GameObject()
{
	m_Children.clear();
	m_Components.clear();
	m_ComponentList.clear();
}

void GameObject::setName(const string& name)
{
	m_Name=name;
}

void GameObject::addChild(GameObjectSharedPtr Child)
{
	Child->m_pParent=this;
	m_Children.push_back(Child);
}

void GameObject::addComponent(Component::ComponentSharedPtr Component)
{
	//check to see if Component exists, if it does, don't add
	if (m_Components.find(Component->getType())==m_Components.end())
	{
		cout<<"Adding "<<Component->getType()<<" to "<<m_Name<<endl;
		Component->setOwner(this);
		m_Components[Component->getType()]=Component;
		m_ComponentList.push_back(Component);
	}
	else{
		//we found it, so don't do anything
	}
}

void GameObject::addComponent(GameObject * current, Component::ComponentSharedPtr Component)
{
	current->addComponent(Component);
	for (int i = 0; i < current->getNumberOfChildren(); i++)
	{
		GameObject * pChild = current->getChild(i).get();
		addComponent(pChild, Component);
	}
}

void GameObject::addComponentToAll(Component::ComponentSharedPtr Component)
{
	addComponent(this, Component);
}

Component::ComponentSharedPtr GameObject::getComponent(const string &type)
{
	return m_Components[type];
}

GameObject::GameObjectSharedPtr GameObject::getChild(int index)
{
	return m_Children[index];
}

int GameObject::getNumberOfChildren()
{
	return m_Children.size();
};

void GameObject::onUpdate()
{
	for (auto it=m_ComponentList.begin();it!=m_ComponentList.end();++it)
	{
		(*it)->onUpdate();
	}
	for (auto it=m_Children.begin();it!=m_Children.end();++it)
	{
		(*it)->onUpdate();
	}
}

void GameObject::onPreRender()
{
	for (auto it=m_ComponentList.begin();it!=m_ComponentList.end();++it)
	{
		(*it)->onPreRender();
	}
}

void GameObject::onRender()
{
	//cout<<"Drawing Game Object"<<endl;
	for (auto it=m_ComponentList.begin();it!=m_ComponentList.end();++it)
	{
		(*it)->onRender();
	}
}

void GameObject::onPostRender()
{
	for (auto it=m_ComponentList.begin();it!=m_ComponentList.end();++it)
	{
		(*it)->onPostRender();
	}
}

void GameObject::onInit()
{
	for (auto it=m_ComponentList.begin();it!=m_ComponentList.end();++it)
	{
		(*it)->onInit();
	}
}
