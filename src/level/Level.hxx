#pragma once
#include <map>
#include "stdxx/grid.hxx"
#include "stdxx/chrono.hxx"
#include "stdxx/functional.hxx"
#include "core/GameState.hxx"
#include "level/Tile.hxx"
#include "level/Item.hxx"
#include "Machine.hxx"
#include "tool/Tool.hxx"
#include "Planet.hxx"

namespace level {
	class Level : public core::GameState {
	public:
		Level(stx::size2u size, std::uint64_t seed);
		virtual void update(double dt) override;
		virtual void ui(stx::size2f area_size) override;
		virtual void render(sf::RenderTarget & render_target) override;
	protected:
		virtual void init() override;

		virtual void on_event(const core::WindowResized &) override;
		virtual void on_event(const core::MouseMoved &) override;
		virtual void on_event(const core::MouseScrolled &) override;
		virtual void on_event(const core::MouseButtonPressed &) override;
		virtual void on_event(const core::KeyPressed &) override;
	private:
		void update_camera(double dt);
		
		Planet planet;
		
		stx::chrono::every tick;
		stx::chrono::every animation_tick;

		sf::View camera;
		constexpr static inline auto camera_speed = 15.f;
		constexpr static inline auto camera_scroll_speed = 0.25f;
		float camera_scale = 4.0;
		stx::position2f camera_center = {0,0};

		stx::position2i cursor_position = {0,0};

		std::unique_ptr<Tool> tool = nullptr;

		sf::Texture sprite_sheet_machines;
		unsigned animation_frame = 0;
	};
}