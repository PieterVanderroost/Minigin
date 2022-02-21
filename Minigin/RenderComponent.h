#pragma once
#include "BaseComponent.h"
namespace dae {
    class Texture2D;

    class RenderComponent final:
        public BaseComponent
    {
    public:
		RenderComponent();
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void SetTexture(const std::string& fileName);

		virtual void Update(float) override {};
		virtual void Render() const override;

	private:
		std::shared_ptr<Texture2D> m_pTexture;

    };
}

