#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "TransformComponent.h"

dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& pFont, SDL_Color color)
	:m_NeedsUpdate{ true },
	m_Text{ text },
	m_pFont{ pFont },
	m_pTextTexture{ nullptr },
	m_Color{ color }
{
}

void dae::TextComponent::Update(float)
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = m_Color;
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}
void dae::TextComponent::Render() const
{
	if (m_pTextTexture != nullptr)
	{
		const auto pos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTextTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetPosition(float x, float y)
{
	m_pGameObject->GetComponent<TransformComponent>()->SetPosition(x, y, 0.0f);
}
