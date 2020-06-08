#include "MiniginPCH.h"
#include "BinaryReader.h"

LVB::BinaryReader::BinaryReader(const std::string& file)
{
	m_File = std::ifstream(file, std::ios::binary);
}

LVB::BinaryReader& LVB::BinaryReader::operator>>(std::string& target)
{
	std::size_t size;
	
	*this >> size;
	target.reserve(size);
	for (std::size_t i{ 0 }; i < size; ++i)
	{
		this->operator>>(target[i]);
	}
	return *this;
}
