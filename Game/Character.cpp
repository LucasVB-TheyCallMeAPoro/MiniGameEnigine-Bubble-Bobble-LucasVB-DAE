#include "Character.h"
#include "ResourceManager.h"
#include <Structs.h>
#include "Texture2D.h"
#include "SDL.h"
#include "Spritesheet.h"
Character::Character(Character::Type type, int columnCount, int rowCount, int totalRowCount)
	:m_Type{type}
	,m_AnimTime{0.f}
{
	SetTexture("BBSprites/Sprites0.png");
	int spriteHeight = GetTexture()->GetHeight() / totalRowCount;
	SetSprite(glm::ivec2(0, GetTexture()->GetHeight() / totalRowCount + static_cast<unsigned int>(m_Type) * spriteHeight * 2), GetTexture()->GetWidth() / columnCount, spriteHeight, columnCount, rowCount);
}

void Character::Render() const
{
}

void Character::Update(float elapsedSec)
{
	m_AnimTime += elapsedSec;
	if (m_AnimTime >= (1.f / this->GetSprite()->GetSpriteSheet()->GetColumnCount()))
	{
		m_AnimTime = 0;
		this->GetSprite()->IncrementIndex();
	}
}
