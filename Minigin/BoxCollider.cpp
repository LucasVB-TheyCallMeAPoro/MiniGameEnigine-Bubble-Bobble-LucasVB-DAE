#include "MiniginPCH.h"
#include "BoxCollider.h"

#include "GameObject.h"
#include "Transform.h"
LVB::BoxCollider::BoxCollider(glm::vec2 bottomLeft, float width, float height)
    :m_Box{bottomLeft,width,height}
{
}
void LVB::BoxCollider::SetPosition(float x, float y)
{
    m_Box.bottemLeft.x = x;
    m_Box.bottemLeft.y = y;
}
LVB::Collision LVB::BoxCollider::Intersects(std::shared_ptr<BaseCollider> other)
{
    LVB::Collision c;
    c.colliding = false; // We default to not colliding.

    std::shared_ptr<LVB::BoxCollider> boxCollider
        = std::dynamic_pointer_cast<LVB::BoxCollider>(other); // 1

    if (boxCollider) // 2
    {
        const LVB::Rectf& rect1 = GetBox();
        const LVB::Rectf& rect2 = boxCollider->GetBox();

        if (rect1.Intersect(rect2)) // 3
        {
            c.colliding = true; // 4
            c.other = &rect2;
        }
    }

    return c;
}
void LVB::BoxCollider::ResolveOverlap(const Collision& c)
{
    auto transform = this->m_pGameObject->GetTransform();

    if (transform->GetIsStatic()) { return; } // 1

    const Rectf& rect1 = GetBox();
    const Rectf* rect2 = c.other;

    float resolve = 0; // 2
    float xDiff = (rect1.bottemLeft.x + (rect1.width * 0.5f))
        - (rect2->bottemLeft.x + (rect2->width * 0.5f)); // 3
    float yDiff = (rect1.bottemLeft.y + (rect1.height * 0.5f))
        - (rect2->bottemLeft.y + (rect2->height * 0.5f));

    if (fabs(xDiff) > fabs(yDiff)) // 4
    {
        if (xDiff > 0) // Colliding on the left.
        {
            // We add a positive x value to move the object to the right.
            resolve = (rect2->bottemLeft.x + rect2->width) - rect1.bottemLeft.x;
        }
        else // Colliding on the right.
        {
            // We add a negative x value to move the object to the left.
            resolve = -((rect1.bottemLeft.x + rect1.width) - rect2->bottemLeft.x);
        }

        transform->SetPosition(transform->GetPosition().x + resolve, 0,0); // 5
    }
    else
    {
        if (yDiff > 0) // Colliding above.
        {
            // We add a positive y value to move the object down.
            resolve = (rect2->bottemLeft.y + rect2->height) - rect1.bottemLeft.y;
        }
        else // Colliding below
        {
            // We add a negative y value to move the object up.
            resolve = -((rect1.bottemLeft.y + rect1.height) - rect2->bottemLeft.y);
        }

        transform->SetPosition(0, transform->GetPosition().y + resolve,0); // 5
    }
}
void LVB::BoxCollider::Initialize()
{
}

void LVB::BoxCollider::Update(float)
{
  
}

void LVB::BoxCollider::Render() const
{
    //glBegin(GL_LINE_LOOP);
    //glVertex2f(m_Box.bottemLeft.x, m_Box.bottemLeft.y);
    //glVertex2f(m_Box.bottemLeft.x + m_Box.width, m_Box.bottemLeft.y);
    //glVertex2f(m_Box.bottemLeft.x + m_Box.width, m_Box.bottemLeft.y + m_Box.height);
    //glVertex2f(m_Box.bottemLeft.x, m_Box.bottemLeft.y + m_Box.height);
    //glEnd();

    
}
