#include <iostream>
#include <random>
#include "stdxx/io.hxx"
#include "Level.hxx"
#include "render.hxx"
#include "create.hxx"
#include "tick.hxx"

namespace level {
	Level::Level(stx::size2u size, std::uint64_t seed) 
	: tiles{size, Tile{rock}}, tick {0.5} {
		std::mt19937_64 rng{seed};

		// this->machines.push_back(std::make_unique<Source>(stx::position2i{0,0}, item_blue));
		// Machine & s1 = *this->machines.back();

		// this->machines.push_back(std::make_unique<Source>(stx::position2i{1,2}, item_yellow));
		// Machine & s2 = *this->machines.back();

		// this->machines.push_back(std::make_unique<Conveyor>(stx::position2i{0,1}));
		// Machine & c1 = *this->machines.back();

		// this->machines.push_back(std::make_unique<Conveyor>(stx::position2i{0,2}));
		// Machine & c2 = *this->machines.back();

		// this->machines.push_back(std::make_unique<Conveyor>(stx::position2i{0,3}));
		// Machine & c3 = *this->machines.back();

		// c3.link(c2);
		// c2.link(c1);
		// c2.link(s2);
		// c1.link(s1);

		// stx::reference<Machine> prev = c3;

		// for(int i = 0; i < 10; i++) {
		// 	this->machines.push_back(std::make_unique<Conveyor>(stx::position2i{1 + i, 3}));
		// 	stx::reference<Machine> m = *this->machines.back();
		// 	m->link(prev);
		// 	prev = m;
		// }


		// this->machines.push_back(std::make_unique<Assembler>(stx::position2i{11, 3}, yellow_to_red));
		// this->machines.back()->link(prev);
		// prev = *this->machines.back();


		// for(int i = 0; i < 10; i++) {
		// 	this->machines.push_back(std::make_unique<Conveyor>(stx::position2i{12 + i, 3}));
		// 	stx::reference<Machine> m = *this->machines.back();
		// 	m->link(prev);
		// 	prev = m;
		// }

		// this->machines.push_back(std::make_unique<Stockpile>(stx::position2i{22, 3}));
		// this->machines.back()->link(prev);
		// prev = *this->machines.back();

		// for(int i = 0; i < 5; i++) {
		// 	this->machines.push_back(std::make_unique<Conveyor>(stx::position2i{23 + i, 3}));
		// 	stx::reference<Machine> m = *this->machines.back();
		// 	m->link(prev);
		// 	prev = m;
		// }

		auto & s1 = create_source(machinery, {0,0}, item_yellow, 4);
		auto & s2 = create_source(machinery, {1,1}, item_yellow, 4);

		auto & c1 = create_conveyor(machinery, {0,1}, {s1.get_id(), s2.get_id()});
		auto & c2 = create_conveyor(machinery, {0,2}, {c1.get_id()});
		auto & c3 = create_conveyor(machinery, {0,3}, {c2.get_id()});
		auto & c4 = create_conveyor(machinery, {0,4}, {c3.get_id()});

		auto & a1 = create_assembler(machinery, {0,5}, {c4.get_id()}, yellow_to_red);

		auto & c5 = create_conveyor(machinery, {0,6}, {a1.get_id()});
		auto & c6 = create_conveyor(machinery, {0,7}, {c5.get_id()});
		
		auto & x1 = create_container(machinery, {0,8}, {c6.get_id()});
		
		auto & c7 = create_conveyor(machinery, {0,9}, {x1.get_id()});
		auto & c8 = create_conveyor(machinery, {0,10}, {c7.get_id()});
	}



	void Level::update(double dt) {
		if(this->tick(dt)) {
			machinery.run_system(tick_pre);

            std::size_t tries = std::size(this->machinery);

            while (tries > 0) {
                --tries;
				bool done = true;
				machinery.run_system([&] (Machinery::Entity & machine) {
					done &= tick_main(machine);
				});

				if(done) break;
            }

			machinery.run_system(tick_post);
		}
	}



	void Level::render(sf::RenderTarget & render_target) {
		render_tiles(this->tiles, render_target);
		machinery.run_system(render_machine, render_target);
	}
	
	
	
	void Level::init() {
		
	}
}