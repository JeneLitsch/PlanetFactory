#pragma once
#include "SFML/Graphics.hpp"

namespace core {
	sf::FloatRect calc_view_port(const sf::Window & window, const sf::View & view);
}