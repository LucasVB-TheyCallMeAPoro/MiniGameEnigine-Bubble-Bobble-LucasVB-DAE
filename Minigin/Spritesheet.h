#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

struct SDL_Rect;
namespace LVB
{
	class Texture2D;
	class SpriteSheet
	{
	public:
		SpriteSheet(const Texture2D* texture, glm::ivec2 origin, int spriteWidth, int spriteHeight, int columnCount, int rowCount);

		const Texture2D* GetTexture() const { return m_SourceTexture; }
		int GetColumnCount() const { return m_ColumnCount; }
		int GetRowCount() const { return m_RowCount; }
		int GetSpriteWidth() const { return m_SpriteWidth; }
		int GetSpriteHeight() const { return m_SpriteHeight; }
		glm::ivec2 GetOrigin() const { return m_Origin; }
	private:

		const Texture2D* m_SourceTexture;
		glm::ivec2 m_Origin; 

		int m_SpriteWidth;
		int m_SpriteHeight;

		int m_ColumnCount;
		int m_RowCount;
	};


	class Sprite
	{
	public:
		Sprite(const SpriteSheet* sheet);
		void SetIndex(int i);
		void IncrementIndex();
		int GetIndex() const { return m_Index; }
		const SpriteSheet* GetSpriteSheet() const { return m_SourceTexture; }
		SDL_Rect GetSourceRect() const;
		
	private:

		int m_Index;
		const SpriteSheet* m_SourceTexture;
	};
}

