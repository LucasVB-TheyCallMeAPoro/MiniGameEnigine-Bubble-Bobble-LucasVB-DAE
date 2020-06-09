#include "MiniginPCH.h"
#include "PhysicsDebugRenderer.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include "glm/glm.hpp"
#pragma warning(pop)

void PhysicsDebugRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    GLfloat glverts[16]; //allow for polygons up to 8 vertices
    glVertexPointer(2, GL_FLOAT, 0, glverts); //tell OpenGL where to find vertices
    glEnableClientState(GL_VERTEX_ARRAY); //use vertices in subsequent calls to glDrawArrays

    //fill in vertex positions as directed by Box2D
    for (int i = 0; i < vertexCount; i++) {
        glverts[i * 2] = vertices[i].x;
        glverts[i * 2 + 1] = vertices[i].y;
    }

    //draw solid area
    glColor4f(color.r, color.g, color.b, 1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

    //draw lines
    glLineWidth(3); //fat lines
    glColor4f(1, 0, 1, 1); //purple
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
}

void PhysicsDebugRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    GLfloat glverts[16]; //allow for polygons up to 8 vertices
    glVertexPointer(2, GL_FLOAT, 0, glverts); //tell OpenGL where to find vertices
    glEnableClientState(GL_VERTEX_ARRAY); //use vertices in subsequent calls to glDrawArrays

    //fill in vertex positions as directed by Box2D
    for (int i = 0; i < vertexCount; i++) {
        glverts[i * 2] = vertices[i].x;
        glverts[i * 2 + 1] = vertices[i].y;
    }

    //draw solid area
    glColor4f(color.r, color.g, color.b, 1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

    //draw lines
    glLineWidth(3); //fat lines
    glColor4f(1, 0, 1, 1); //purple
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
}
