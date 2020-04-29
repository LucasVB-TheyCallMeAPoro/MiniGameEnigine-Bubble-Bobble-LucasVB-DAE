#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include "BaseComponent.h"
#include <glm/vec3.hpp>
#pragma warning(pop)
namespace LVB
{
	class Rigidbody : public BaseComponent
	{
	public:
		Rigidbody();
		virtual ~Rigidbody() = default;
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);

		void UseGravity(bool use) {m_UseGravity = use;}
	private:

		virtual void Initialize() override;
		virtual void Update(float elapsedSec) override;
		virtual void Render() const override;

		glm::vec3 m_Position;

		bool m_UseGravity = true;
		float m_Gravity = 9.81f;
	};
}

