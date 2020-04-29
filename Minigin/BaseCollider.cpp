#include "MiniginPCH.h"
#include "BaseCollider.h"

LVB::BaseCollider::BaseCollider()
    :BaseComponent{}, m_Layer(CollisionLayer::Default)
{
}

LVB::BaseCollider::~BaseCollider()
{
}

LVB::CollisionLayer LVB::BaseCollider::GetLayer() const
{
    return m_Layer;
}

void LVB::BaseCollider::SetLayer(CollisionLayer layer)
{
    m_Layer = layer;
}

