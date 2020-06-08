#pragma once
#include "BaseCollider.h"
#include "Structs.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
//#include <box2d/box2d.h>
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

		virtual void Initialize() override;
		virtual void Update(float elapsedSec) override;
		virtual void Render() const override;
	private:
		Rectf m_Box;
		
	};
}

