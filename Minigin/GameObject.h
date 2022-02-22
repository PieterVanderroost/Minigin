#pragma once
#include "Transform.h"

namespace dae
{
	class BaseComponent;

	class GameObject final
	{
	public:
		GameObject();
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update(float elapsedSec);
		void Render() const;

		void AddComponent(const std::shared_ptr<BaseComponent>& component);

		template <typename T> std::shared_ptr<T> GetComponent() const
		{
			for (auto pComp : m_pComponents)
			{
				if (typeid(*pComp) == typeid(T))
					return std::dynamic_pointer_cast<T>(pComp);
			}
			return nullptr;
		}

		void SetParent(const std::shared_ptr<GameObject>& parent);
		std::shared_ptr<GameObject> GetParent() const;

		size_t GetChildCount() const;
		std::shared_ptr<GameObject> GetChildAt(int index) const;
		void RemoveChild(int index);
		void AddChild(const std::shared_ptr<GameObject>& go);
		
	private:
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
		std::shared_ptr<GameObject> m_pParent = nullptr;
		std::vector<std::shared_ptr<GameObject>> m_pChildren;
	};
}
