#pragma once
#include "Singleton.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
struct SDL_Window;
struct SDL_Renderer;

namespace LVB
{
	class Texture2D;
	class Sprite;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderSprite(const Sprite& sprite, const float x, const float y);
		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
		void SetScale(float scale) { m_Scale = scale; }
		void SetOrigin(int x, int y) { m_CameraOrigin.x = x; m_CameraOrigin.y = y; }
	private:
		SDL_Renderer* m_Renderer{};
		glm::ivec2 m_CameraOrigin{ 0,0 };
		float m_Scale = 1.f;
	};
}

