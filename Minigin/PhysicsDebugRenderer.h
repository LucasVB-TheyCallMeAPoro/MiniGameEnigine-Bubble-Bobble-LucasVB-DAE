#pragma once


//bron ==> https://www.iforce2d.net/b2dtut/debug-draw
#include  "Box2D.h"
class PhysicsDebugRenderer :public b2Draw
{
public:
    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
    void DrawSolidPolygon(const b2Vec2*, int32, const b2Color&) override;
    void DrawCircle(const b2Vec2& , float , const b2Color& ) override {}
    void DrawSolidCircle(const b2Vec2& , float , const b2Vec2& , const b2Color& ) override {}
    void DrawSegment(const b2Vec2& , const b2Vec2& , const b2Color& ) override {}
    void DrawTransform(const b2Transform& ) override {}
    void DrawPoint(const b2Vec2& , float , const b2Color& ) override {}
};

