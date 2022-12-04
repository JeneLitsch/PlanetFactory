#pragma once
#include <SFML/Graphics.hpp>
#include "stdxx/math.hxx"

namespace level {
	struct Item {
		sf::Color color;
	};

	void render_item(const Item & item, stx::position2f xy, sf::RenderTarget & target);

	inline const Item test {
		.color = sf::Color::Blue,
	};


}