#include "MiniginPCH.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"

dae::GameObject::GameObject()
{
	AddComponent(std::make_shared<TransformComponent>());
}

void dae::GameObject::Update(float elapsedSec)
{
	for (auto component : m_pComponents)
	{
		component->Update(elapsedSec);
	}
}

void dae::GameObject::Render() const
{
	for (auto component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	component->SetGameObject(this);
	m_pComponents.push_back(component);
}