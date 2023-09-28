#include <iostream>
#include <random>
#include "stdxx/io.hxx"
#include "Level.hxx"
#include "render.hxx"
#include "create.hxx"
#include "Recipe.hxx"
#include "core/calc_viewport.hxx"
#include "imgui.h"
#include "tool/Eraser.hxx"
#include "tool/PlaceConveyor.hxx"

namespace ui = ImGui;

namespace level {
	Level::Level(stx::size2u size, std::uint64_t seed) 
	: tiles{size, rock}
	, resources{size, stx::nullref}
	, tick {0.5}
	, animation_tick {0.5 / 4.0} {

		this->resources(5,5) = item_blue;

		std::mt19937_64 rng{seed};
		
		auto s1 = create_source({0,0}, {0,0}, item_yellow, 4);
		auto s2 = create_source({1,1}, {0,0}, item_yellow, 4);

		auto c1 = create_conveyor({0,1}, {0,0});
		link_machines(*s1, *c1);
		link_machines(*s2, *c1);

		auto c2 = create_conveyor({0,2}, {0,0});
		link_machines(*c1, *c2);
		auto c3 = create_conveyor({0,3}, {0,0});
		link_machines(*c2, *c3);
		auto c4 = create_conveyor({0,4}, {0,0});
		link_machines(*c3, *c4);

		auto a1 = create_assembler({0,5}, {0,0}, yellow_to_red);
		link_machines(*c4, *a1);

		auto c5 = create_conveyor({0,6}, {0,0});
		link_machines(*a1, *c5);
		auto c6 = create_conveyor({0,7}, {0,0});
		link_machines(*c5, *c6);
		
		auto x1 = create_container({0,8}, {0,0});
		link_machines(*c6, *x1);
		
		auto c7 = create_conveyor({0,9}, {0,0});
		link_machines(*x1, *c7);
		auto c8 = create_conveyor({0,10}, {0,0});
		link_machines(*c7, *c8);

		this->machines.push_back(std::move(s1));
		this->machines.push_back(std::move(s2));
		
		this->machines.push_back(std::move(a1));
		this->machines.push_back(std::move(x1));

		this->machines.push_back(std::move(c1));
		this->machines.push_back(std::move(c2));
		this->machines.push_back(std::move(c3));
		this->machines.push_back(std::move(c4));
		this->machines.push_back(std::move(c5));
		this->machines.push_back(std::move(c6));
		this->machines.push_back(std::move(c7));
		this->machines.push_back(std::move(c8));

		this->sprite_sheet_machines.loadFromFile("./assets/machines.png");
	}





	void Level::update(double dt) {
		if(this->tick(dt)) {
			for(const auto & m : this->machines) {
				m->tick_pre();
			}
            std::size_t tries = std::size(this->machines);

            while (tries > 0) {
                --tries;
				bool done = true;
				
				for(const auto & m : this->machines) {
					done &= m->tick_main();
				}

				if(done) break;
            }

			for(const auto & m : this->machines) {
				m->tick_post();
			}
		}

		if(this->animation_tick(dt)) {
			++this->animation_frame;
			this->animation_frame %= 4;
		}

		this->update_camera(dt);
	}



	void Level::update_camera(double dt) {
		const float dt_f = static_cast<float>(dt);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			this->camera_center.x -= dt_f * camera_speed * this->camera_scale;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			this->camera_center.x += dt_f * camera_speed * this->camera_scale;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			this->camera_center.y -= dt_f * camera_speed * this->camera_scale;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->camera_center.y += dt_f * camera_speed * this->camera_scale;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			this->camera_scale -= this->camera_scale * dt_f;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			this->camera_scale += this->camera_scale * dt_f;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			this->tool = nullptr;
		}

		this->camera_center = stx::clamp(
			this->camera_center,
			stx::position2f{-2,-2},
			stx::position2f{this->tiles.size()} + stx::position2f{1,1}
		);

		this->camera_scale = std::clamp(this->camera_scale, 0.25f, 16.f);
	}



	void Level::ui(stx::size2f area_size) {
		if(ui::Begin("Test", nullptr
			, ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoMove)) {
			ui::SetWindowPos({0, 0.75f * area_size.y});
			ui::SetWindowSize({area_size.x, 0.25f * area_size.y});
			auto area = ui::GetContentRegionAvail();

			if(ui::Button("Demolish", {area.x / 8.f, area.y})) {
				this->tool = std::make_unique<Eraser>(this->machines);
			}
			ui::SameLine();
			if(ui::Button("Conveyor", {area.x / 8.f, area.y})) {
				this->tool = std::make_unique<PlaceConveyor>(this->machines);
			}
			ui::SameLine();
		}
		else {
			ui::SetWindowFontScale(2);
			ui::SetWindowPos({0, area_size.y - ui::GetWindowHeight()});
			ui::SetWindowSize({area_size.x, ui::GetWindowHeight()});
		}
		ui::SetWindowFontScale(2);
		ui::End();
	}



	void Level::render(sf::RenderTarget & render_target) {
		auto old_view = render_target.getView();
		camera.setCenter(this->camera_center.to<sf::Vector2f>());
		camera.setSize(16 * this->camera_scale, 9 * this->camera_scale);
		render_target.setView(camera);

		render_tiles(this->tiles, render_target);
		render_resources(this->resources, render_target);
		for(const auto & m : this->machines) {
			render_machine(*m, render_target, sprite_sheet_machines, animation_frame);
		}

		if(this->tool) {
			this->tool->render(this->cursor_position, render_target);
		}

		render_target.setView(old_view);
	}
	
	
	
	void Level::init() {
		
	}



	void Level::on_event(const core::WindowResized & event)  {
		this->camera.setViewport(core::calc_view_port(*event.window, this->camera));
	}



	void Level::on_event(const core::MouseMoved & event) {
		const auto a = stx::position2f::from(event.window->mapPixelToCoords(event.position.to<sf::Vector2i>(), this->camera));
		cursor_position = stx::position2i{stx::floor(a)};
	}



	void Level::on_event(const core::MouseButtonPressed & event) {
		if(event.button == sf::Mouse::Left) {
			if(this->tool) {
				this->tool->apply(this->cursor_position);
			}
		}
	}



	void Level::on_event(const core::MouseScrolled & event) {
		const auto a = stx::position2f::from(event.window->mapPixelToCoords(event.position.to<sf::Vector2i>(), this->camera));
		const auto b = a - this->camera_center;
		const auto xy = b;
		
		const float new_scale = this->camera_scale + camera_scroll_speed * (event.value * this->camera_scale);
		const float scale_change =  new_scale - this->camera_scale;
		const float offset_x = -(xy.x * scale_change) / new_scale; 
		const float offset_y = -(xy.y * scale_change) / new_scale;
		this->camera_center = this->camera_center + stx::position2f{offset_x, offset_y};
		this->camera_scale = new_scale;
		
	}



	void Level::on_event(const core::KeyPressed & event) {
		if(event.code == sf::Keyboard::Key::R) {
			if(this->tool) this->tool->rotate_cw();
		}
	}
}