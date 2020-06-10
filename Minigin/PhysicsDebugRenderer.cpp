#include "MiniginPCH.h"
#include "PhysicsDebugRenderer.h"
#include "Renderer.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include "glm/glm.hpp"
#pragma warning(pop)

void PhysicsDebugRenderer::DrawPolygon(const b2Vec2* , int32 , const b2Color& )
{

}

void PhysicsDebugRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 , const b2Color& )
{

	LVB::Renderer::GetInstance().RenderPolygon(vertices);

}
