#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
namespace LVB
{
	struct Rectf
	{
		glm::vec2 bottemLeft;
		float width;
		float height;

		bool Intersect(Rectf other) const
		{
			bool collisionX = bottemLeft.x + width >= other.bottemLeft.x &&
				other.bottemLeft.x + other.width >= bottemLeft.x;
			// Collision y-axis?
			bool collisionY = bottemLeft.y + height >= other.bottemLeft.y &&
				other.bottemLeft.y + other.height >= bottemLeft.y;
			// Collision only if on both axes
			return collisionX && collisionY;
		}
	};
}