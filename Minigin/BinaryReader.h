#pragma once
#include <type_traits>
#include <string>
#include <istream>
#include <fstream>
#include <vector>

//Bron ==> Mats Present 2DAE07 (multiverse engine)
namespace LVB
{
	class BinaryReader
	{
	public:
		BinaryReader(const std::string& file);

		BinaryReader& operator>>(std::string& target);
	

		template <typename T>
		BinaryReader& operator>>(std::vector<T>& target);
		//Enable if gets 2 paramaters (bool and int)
		//if true ==> enable_if_t will be a integer
		//if false ==> enable_if_t will crash (enable_if_t = errortype)
		//This will make sure that the function only exists for type of standard layout
		//https://en.cppreference.com/w/cpp/named_req/StandardLayoutType
		template <typename T,  std::enable_if_t<std::is_standard_layout_v<T>, int > = 0>
		BinaryReader& operator>>(T& target);
		
	private:
		std::ifstream m_File;

	};

	template<typename T>
	inline BinaryReader& BinaryReader::operator>>(std::vector<T>& target)
	{
		std::size_t size;
		this->operator>>(size);
		target.clear();
		target.reserve(size);
		for (std::size_t i{ 0 }; i < size; ++i)
		{
			this->operator>>(target[i]);
		}
		return *this;
	}

	template<typename T, std::enable_if_t<std::is_standard_layout_v<T>, int >>
	inline BinaryReader& LVB::BinaryReader::operator>>(T& target)
	{
		m_File.read(reinterpret_cast<char*>(&target), sizeof(T));
		return *this;
	}
}
