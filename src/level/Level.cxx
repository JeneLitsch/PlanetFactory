#include "Level.hxx"
#include <iostream>
#include <random>
#include "render.hxx"
#include "stdxx/io.hxx"
#include "level/machinery/Conveyor.hxx"
#include "level/machinery/Source.hxx"
#include "level/machinery/Assembler.hxx"

namespace level {
	const Recipe yellow_to_red {
		.from = {
			item_yellow,
			item_blue,
		},
		.to = item_red,
	};

	Level::Level(stx::size2u size, std::uint64_t seed) 
	: tiles{size, Tile{rock}}, tick {0.5} {
		std::mt19937_64 rng{seed};

		this->machines.push_back(std::make_unique<Source>(stx::position2i{0,0}, item_blue));
		Machine & s1 = *this->machines.back();

		this->machines.push_back(std::make_unique<Source>(stx::position2i{1,2}, item_yellow));
		Machine & s2 = *this->machines.back();

		this->machines.push_back(std::make_unique<Conveyor>(stx::position2i{0,1}));
		Machine & c1 = *this->machines.back();

		this->machines.push_back(std::make_unique<Conveyor>(stx::position2i{0,2}));
		Machine & c2 = *this->machines.back();

		this->machines.push_back(std::make_unique<Conveyor>(stx::position2i{0,3}));
		Machine & c3 = *this->machines.back();

		c3.link(c2);
		c2.link(c1);
		c2.link(s2);
		c1.link(s1);

		stx::reference<Machine> prev = c3;

		for(int i = 0; i < 10; i++) {
			this->machines.push_back(std::make_unique<Conveyor>(stx::position2i{1 + i, 3}));
			stx::reference<Machine> m = *this->machines.back();
			m->link(prev);
			prev = m;
		}


		this->machines.push_back(std::make_unique<Assembler>(stx::position2i{11, 3}, yellow_to_red));
		this->machines.back()->link(prev);
		prev = *this->machines.back();


		for(int i = 0; i < 15; i++) {
			this->machines.push_back(std::make_unique<Conveyor>(stx::position2i{12 + i, 3}));
			stx::reference<Machine> m = *this->machines.back();
			m->link(prev);
			prev = m;
		}
	}



	void Level::update(double dt) {
		if(this->tick(dt)) {
			for(auto & m : machines) {
				m->tick_pre();
			}

            std::size_t tries = std::size(this->machines);

			auto begin = std::begin(this->machines);
			auto end = std::end(this->machines);
			auto machine_done = [] (auto & m) { return m->is_done(); };

            while (!std::all_of(begin, end, machine_done) && tries > 0) {
                --tries;
				for(auto & m : machines) {
					m->tick_main();
				}
            }

			for(auto & m : machines) {
				m->tick_post();
			}
		}
	}



	void Level::render(sf::RenderTarget & render_target) {
		render_tiles(this->tiles, render_target);
		for(const auto & machine : this->machines) {
			machine->render(render_target);
		}
	}
	
	
	
	void Level::init() {
		
	}
}