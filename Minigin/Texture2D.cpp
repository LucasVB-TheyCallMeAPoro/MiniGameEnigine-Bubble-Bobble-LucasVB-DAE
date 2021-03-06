#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

LVB::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* LVB::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

LVB::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &m_Width, &m_Height);
}
