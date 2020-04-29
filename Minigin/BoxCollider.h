#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include "BaseCollider.h"
#include <glm/vec2.hpp>
#include "Structs.h"
#pragma warning(pop)

namespace LVB
{
	class BoxCollider : public BaseCollider
	{
	public:
		BoxCollider(glm::vec2 bottomLeft, float width, float height);
		virtual ~BoxCollider() = default;
		const glm::vec2& GetPosition() const { return m_Box.bottemLeft; }
		void SetPosition(float x, float y);
		void SetWidth(float w) { m_Box.width = w;}
		void SetHeight(float h) { m_Box.height = h; }
		
		virtual Collision Intersects(std::shared_ptr<BaseCollider> other) override;
		virtual void ResolveOverlap(const Collision & m) override;

		const Rectf& GetBox() const { return m_Box; }
		
	private:
		Rectf m_Box;
		virtual void Initialize() override;
		virtual void Update(float elapsedSec) override;
		virtual void Render() const override;

		
	};
}

