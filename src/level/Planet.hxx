#pragma once
#include <map>
#include "stdxx/grid.hxx"
#include "level/Tile.hxx"
#include "level/Item.hxx"
#include "Machine.hxx"
#include "tool/Tool.hxx"

namespace level {
	struct Planet {
		std::vector<std::unique_ptr<Machine>> machines;

		stx::grid2<stx::optref<const Tile>> tiles;
		stx::grid2<stx::optref<const Item>> resources;
	};
}