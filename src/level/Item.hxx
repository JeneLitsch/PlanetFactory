#pragma once
#include "SFML/Graphics.hpp"
#include "stdxx/math.hxx"

namespace level {
	struct Item {
		std::string name;
		sf::Color color;
	};

	void render_item(const Item & item, stx::position2f xy, sf::RenderTarget & target);

	inline const Item item_blue {
		.name = "item_blue",
		.color = sf::Color::Blue,
	};

	inline const Item item_yellow {
		.name = "item_yellow",
		.color = sf::Color::Yellow,
	};

	inline const Item item_red {
		.name = "item_red",
		.color = sf::Color::Red,
	};
}