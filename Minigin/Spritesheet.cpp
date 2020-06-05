#include "MiniginPCH.h"
#include "Spritesheet.h"
#include "Texture2D.h"
#include "SDL.h"
LVB::Sprite::Sprite(const SpriteSheet* sheet)
	:m_SourceTexture{sheet}
	,m_Index{0}
{
}
void LVB::Sprite::SetIndex(int i)
{
	int total = m_SourceTexture->GetColumnCount() * m_SourceTexture->GetRowCount();
	m_Index = i % total;
}

void LVB::Sprite::IncrementIndex()
{
	SetIndex(m_Index + 1);
}

SDL_Rect LVB::Sprite::GetSourceRect() const
{
	SDL_Rect rect{};

	rect.w = m_SourceTexture->GetSpriteWidth();
	rect.h = m_SourceTexture->GetSpriteHeight();
	rect.x = m_SourceTexture->GetOrigin().x + (m_Index * rect.w) % m_SourceTexture->GetColumnCount();
	rect.y = m_SourceTexture->GetOrigin().y + (m_Index * rect.h) / m_SourceTexture->GetColumnCount();

	return rect;
}

LVB::SpriteSheet::SpriteSheet(const Texture2D* texture, glm::ivec2 origin, int spriteWidth, int spriteHeight, int columnCount, int rowCount)
	:m_SourceTexture{texture}
	,m_Origin{origin}
	,m_SpriteWidth{spriteWidth}
	,m_SpriteHeight{spriteHeight}
	,m_ColumnCount{columnCount}
	,m_RowCount{rowCount}
{
}
