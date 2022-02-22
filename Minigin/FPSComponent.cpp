#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"


void dae::FPSComponent::Update(float elapsedSec)
{
	std::string fps{ std::to_string(static_cast<int>(1.f / elapsedSec)) };

	m_pGameObject->GetComponent<TextComponent>()->SetText(fps + " FPS");
}
