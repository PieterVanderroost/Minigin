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
	for (auto child : m_pChildren)
	{
		child->Update(elapsedSec);
	}
}

void dae::GameObject::Render() const
{
	for (auto component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameObject::AddComponent(const std::shared_ptr<BaseComponent>& component)
{
	component->SetGameObject(this);
	m_pComponents.push_back(component);
}

void dae::GameObject::SetParent(const std::shared_ptr<GameObject>& parent)
{
	m_pParent = parent;
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetParent() const
{
	return m_pParent;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_pChildren.size();
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(int index) const
{
	return m_pChildren[index];
}

void dae::GameObject::RemoveChild(int index)
{
	m_pChildren.erase(m_pChildren.begin() + index);
}

void dae::GameObject::AddChild(const std::shared_ptr<GameObject>& go)
{
	m_pChildren.push_back(go);
}
