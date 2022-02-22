#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>
namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(const std::string& text, const std::shared_ptr<Font>& pFont,SDL_Color color = {255,255,255});
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void Update(float elapsedSec) override;
		virtual void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTextTexture;
		SDL_Color m_Color;
	};
}

