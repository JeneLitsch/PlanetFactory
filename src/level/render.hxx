#pragma once
#include "stdxx/grid.hxx"
#include "SFML/Graphics.hpp"
#include "level/Tile.hxx"
#include "level/Item.hxx"

namespace level {
	void render_tiles(
		const stx::grid2<Tile> & tiles,
		sf::RenderTarget & target);
}