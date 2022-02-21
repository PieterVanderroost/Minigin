#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"

dae::RenderComponent::RenderComponent()
	:m_pTexture{nullptr}
{
}

void dae::RenderComponent::SetTexture(const std::string& fileName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
}

void dae::RenderComponent::Render() const
{
	const auto& pos = GetGameObject()->GetComponent<TransformComponent>()->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}
