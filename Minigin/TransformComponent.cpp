#include "MiniginPCH.h"
#include "TransformComponent.h"


	const glm::vec3& dae::TransformComponent::GetPosition() const
	{
		return m_Position;
	}

	void dae::TransformComponent::SetPosition(float x, float y, float z)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
	}
