#pragma once
#include "BinaryReader.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
//Bron ==> Mats Present 2DAE07 (multiverse engine)

class Level
{
public:
	std::vector<glm::ivec2> BlockPositions() const;

private:

	//This is the width and height of each level within the level file.
	const static unsigned int m_Width = 32; //const static AND defined in header ==> Const expresion (compile time constant)
	const static unsigned int m_Height = 25;

	//the variables must be const expression in order to be defined at compile time for our static array
	bool m_Tiles[m_Width * m_Height];

	friend LVB::BinaryReader& operator>>(LVB::BinaryReader& reader, Level& level);

};

LVB::BinaryReader& operator>>(LVB::BinaryReader& reader, Level& level);