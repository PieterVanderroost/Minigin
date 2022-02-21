#pragma once
#include "Transform.h"
#include "SceneObject.h"


namespace dae
{
	class BaseComponent;

	// todo: this should become final.
	class GameObject: public SceneObject
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

		void AddComponent(std::shared_ptr<BaseComponent> component);

		template <typename T> std::shared_ptr<T> GetComponent() const
		{
			for (auto pComp : m_pComponents)
			{
				if (typeid(*pComp) == typeid(T))
					return std::dynamic_pointer_cast<T>(pComp);
			}
			return nullptr;
		}

		//void SetParent(GameObject* parent);
		//GameObject* GetParent() const;
		////void SetTexture(const std::string& filename);
		////void SetPosition(float x, float y);

		//size_t GetChildCount() const;
		//GameObject* GetChildAt(int index) const;
		//void RemoveChild(int index);
		//void AddChild(GameObject* go);
		
	private:
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
		// todo: mmm, every gameobject has a texture? Is that correct?
		//std::shared_ptr<Texture2D> m_Texture{};
	};
}
