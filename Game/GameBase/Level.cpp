#include "Level.h"

LVB::BinaryReader& operator>>(LVB::BinaryReader& reader, Level& level)
{
	//8 = number of bits in a byte
	for (std::size_t i{ 0 }; i < (level.m_Width * level.m_Height) / 8; ++i)
	{
		char byte;
		reader >> byte;
		for (std::size_t j{ 0 }; j < 8; ++j)
		{
			//level.m_Tiles[8 *i + j] = byte & (1 << j);  
			level.m_Tiles[8 * i + j] = byte & (1 << (7 -j));
		}
	}

	return reader;
}

std::vector<glm::ivec2> Level::BlockPositions() const
{
	std::vector<glm::ivec2> positions;
	for (std::size_t y{ 0 }; y < m_Height; ++y)
	{
		for (std::size_t x{ 0 }; x < m_Width-2; ++x)
		{
			if (this->m_Tiles[x + m_Width * y])
			{
				positions.push_back({ x,y });
			}
		}
		for (std::size_t x{ m_Width - 2 }; x < m_Width; ++x)
			positions.push_back({ x,y });
	}
	return positions;
}
