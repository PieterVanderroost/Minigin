#pragma once
#include "GameObject.h"

namespace dae
{
	class BaseComponent
	{
	public:
		BaseComponent()
			:m_pGameObject{ nullptr }
		{}
		virtual ~BaseComponent() {};
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update(float elapsedSec) = 0;
		virtual void Render() const {};

		GameObject* GetGameObject() const { return m_pGameObject; }
		void SetGameObject(GameObject* gameObject) { m_pGameObject = gameObject; }

	protected:
		friend GameObject;
		GameObject* m_pGameObject;
	};
}

