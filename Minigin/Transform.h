#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include "BaseComponent.h"
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace LVB
{
	class Transform final : public BaseComponent
	{
	public:
		Transform(bool isStatic = false);
		Transform(float x, float y, float z, bool isStatic = false);
		virtual ~Transform() = default;
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);

		bool GetIsStatic() const { return m_IsStatic; }
		void SetIsStatic(bool s) { m_IsStatic = s; }
		
	private:
		glm::vec3 m_Position;
		bool m_IsStatic;

		virtual void Initialize() override;
		virtual void Update(float elapsedSec) override;
		virtual void Render() const override;
	};
}
