#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include <memory>
namespace LVB
{
    //The collider classes are mad using this site http://thatgamesguy.co.uk/cpp-game-dev-15/
    //Some function are mad using this site https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection
    enum class CollisionLayer
    {
        Default = 1,    // bit 0
        Player = 2,     // bit 1
        Tile = 3        // bit 2
    };

    struct Collision
    {
        bool colliding = false;
        const Rectf* other;
    };
    class GameObject;
    class BaseCollider : public BaseComponent
    {
        public:
            BaseCollider();
            ~BaseCollider();

            virtual Collision Intersects(std::shared_ptr<BaseCollider> other) = 0;
            virtual void ResolveOverlap(const Collision& m) = 0;

            CollisionLayer GetLayer() const;
            void SetLayer(CollisionLayer layer);

        private:
            CollisionLayer m_Layer;

    };
}

