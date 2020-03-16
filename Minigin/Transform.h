#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include "BaseComponent.h"
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class Transform final : public BaseComponent
	{
	public:
		Transform();
		Transform(float x, float y, float z);
		virtual ~Transform() = default;
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);

		
	private:
		glm::vec3 m_Position;

		virtual void Initialize() override;
		virtual void Update(float elapsedSec) override;
		virtual void Draw() override;
	};
}
