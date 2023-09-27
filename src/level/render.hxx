#pragma once
#include "stdxx/grid.hxx"
#include "SFML/Graphics.hpp"
#include "level/Tile.hxx"
#include "level/Item.hxx"
#include "Machine.hxx"

namespace level {
	void render_tiles(const stx::grid2<Tile> & tiles, sf::RenderTarget & target);
	void render_machine(const Machine & machine, sf::RenderTarget & target, sf::Texture & sprite_sheet, unsigned frame);
}