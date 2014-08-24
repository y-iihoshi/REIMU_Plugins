#pragma once

#include <cstdint>

namespace Th123
{
	enum class Mode : std::uint8_t
	{
		Story,
		Arcade,
		VsCom,
		VsPlayer,
		VsNetworkHost,
		VsNetworkClient,
		VsNetworkWatch
	};
}
