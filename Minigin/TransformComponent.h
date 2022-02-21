#pragma once
#include "BaseComponent.h"
namespace dae {
	class TransformComponent final : public BaseComponent
	{
	public:
		const glm::vec3& GetPosition() const;
		void SetPosition(float x, float y, float z = 0.f);

		virtual void Update(float) override {};
		virtual void Render() const override {};

	private:
		glm::vec3 m_Position;
	};
}
