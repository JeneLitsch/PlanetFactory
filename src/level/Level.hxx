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

		virtual void on_event(const core::WindowResized &) override;
		virtual void on_event(const core::MouseScrolled &) override;
	private:
		void update_camera(double dt);
		
		std::vector<std::unique_ptr<Machine>> machines;
		stx::grid2<Tile> tiles;
		stx::chrono::every tick;

		sf::View camera;
		constexpr static inline auto camera_speed = 15.f;
		constexpr static inline auto camera_scroll_speed = 0.25f;
		float camera_scale = 4.0;
		stx::position2f camera_center = {0,0};
	};
}