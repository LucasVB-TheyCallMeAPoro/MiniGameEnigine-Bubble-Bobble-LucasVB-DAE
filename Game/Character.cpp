#include "Character.h"
#include "ResourceManager.h"
#include <Structs.h>
#include "Texture2D.h"
#include "SDL.h"
#include "Spritesheet.h"
Character::Character(Character::Type type, int columnCount, int rowCount, int totalRowCount)
	:m_Type{type}

{
	SetTexture("BBSprites/Sprites0.png");
	SetSprite(glm::ivec2(0, GetTexture()->GetHeight() / totalRowCount + static_cast<unsigned int>(m_Type) * 2), GetTexture()->GetWidth() / columnCount, GetTexture()->GetHeight() / totalRowCount, columnCount, rowCount);
}

void Character::Render() const
{
}

void Character::Update(float)
{
	
}
