#pragma once
#include "SFML/Graphics.hpp"
#include "stdxx/reference.hxx"

namespace level {
	struct Tile {
		sf::Color color;
	};

	
	
	inline const Tile rock {
		.color = sf::Color{128,128,128},
	};
}