#pragma once

#include <map>
#include <string>
#include <sstream>
#include <cstdint>
#include "Mode.h"
#include "Chara.h"

namespace Th105
{
	template<typename TKey>
	static std::string GetString(const std::map<TKey, std::string> &stringMap, const TKey &key)
	{
		try
		{
			return stringMap.at(key);
		}
		catch (const std::out_of_range &)
		{
			std::ostringstream stream;
			stream << "unknown (" << static_cast<int>(key) << ")";
			return stream.str();
		}
	}

	extern const std::map<std::uint16_t, std::string> Versions;
	extern const std::map<Th105::Mode, std::string> Modes;
	extern const std::map<Th105::Chara, std::string> Characters;
	extern const std::map<std::uint16_t, std::string> SystemCards;
	extern const std::map<Th105::Chara, std::map<std::uint16_t, std::string>> Cards;
	extern const std::map<std::uint8_t, std::string> Stages;
	extern const std::map<std::uint8_t, std::string> Bgms;
}
