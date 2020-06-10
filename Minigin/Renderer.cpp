#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "Spritesheet.h"
void LVB::Renderer::Init(SDL_Window * window)
{
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void LVB::Renderer::Render() const
{
	SDL_SetRenderDrawColor(m_Renderer, 128, 128, 128, 255);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(m_Renderer);
}

void LVB::Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void LVB::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	dst = GetDestRect(x, y, static_cast<float>(dst.w), static_cast<float>(dst.h));
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void LVB::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{ GetDestRect(x,y,width,height) };
	
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void LVB::Renderer::RenderSprite(const Sprite& sprite, const float x, const float y) const
{
	SDL_Rect src{ sprite.GetSourceRect() };
	SDL_Rect dst{GetDestRect(x - src.w/2.f,y - src.h/2.f,static_cast<float>(src.w),static_cast<float>(src.h))};

	SDL_RenderCopy(GetSDLRenderer(), sprite.GetSpriteSheet()->GetTexture()->GetSDLTexture(), &src, &dst);
	
}

void LVB::Renderer::RenderPolygon(const b2Vec2* vertices)
{
	SDL_Rect dst{ GetDestRect(vertices[0].x,vertices[0].y,vertices[1].x - vertices[0].x,vertices[2].y - vertices[0].y) };
	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(m_Renderer, &dst);
}

SDL_Rect LVB::Renderer::GetDestRect(float x, float y, float width, float height) const
{
	SDL_Rect rect{};
	rect.x = static_cast<int>((x - m_CameraOrigin.x) * m_Scale);
	rect.y = static_cast<int>((y - m_CameraOrigin.y) * m_Scale);
	rect.w = static_cast<int>(width * m_Scale);
	rect.h = static_cast<int>(height * m_Scale);
	return rect;
}
