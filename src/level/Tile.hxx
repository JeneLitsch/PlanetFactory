#pragma once
#include <SFML/Graphics.hpp>
#include "stdxx/reference.hxx"

namespace level {
	struct TileType {
		sf::Color color;
	};

	
	
	struct Tile {
		stx::optref<const TileType> type;
	};

	
	
	inline const TileType rock {
		.color = sf::Color{128,128,128},
	};
}