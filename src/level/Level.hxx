#pragma once
#include <map>
#include "stdxx/grid.hxx"
#include "stdxx/chrono.hxx"
#include "core/GameState.hxx"
#include "level/Tile.hxx"
#include "level/Item.hxx"
#include "Machine.hxx"

namespace level {
	class Level : public core::GameState {
	public:
		Level(stx::size2u size, std::uint64_t seed);
		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;
	protected:
		virtual void init() override;

	private:
		std::vector<std::unique_ptr<Machine>> machines;
		stx::grid2<Tile> tiles;
		stx::chrono::every tick;
	};
}