#include <iostream>
#include <random>
#include "stdxx/io.hxx"
#include "Level.hxx"
#include "render.hxx"
#include "create.hxx"
#include "Recipe.hxx"
namespace level {
	Level::Level(stx::size2u size, std::uint64_t seed) 
	: tiles{size, Tile{rock}}, tick {0.5} {
		std::mt19937_64 rng{seed};

		// this->machines.push_back(std::make_unique<Source>(stx::position2i{0,0}, item_blue));
		// Machinery::Entity & s1 = *this->machines.back();

		// this->machines.push_back(std::make_unique<Source>(stx::position2i{1,2}, item_yellow));
		// Machinery::Entity & s2 = *this->machines.back();

		// this->machines.push_back(std::make_unique<Conveyor>(stx::position2i{0,1}));
		// Machinery::Entity & c1 = *this->machines.back();

		// this->machines.push_back(std::make_unique<Conveyor>(stx::position2i{0,2}));
		// Machinery::Entity & c2 = *this->machines.back();

		// this->machines.push_back(std::make_unique<Conveyor>(stx::position2i{0,3}));
		// Machinery::Entity & c3 = *this->machines.back();

		// c3.link(c2);
		// c2.link(c1);
		// c2.link(s2);
		// c1.link(s1);

		// stx::reference<Machinery::Entity> prev = c3;

		// for(int i = 0; i < 10; i++) {
		// 	this->machines.push_back(std::make_unique<Conveyor>(stx::position2i{1 + i, 3}));
		// 	stx::reference<Machinery::Entity> m = *this->machines.back();
		// 	m->link(prev);
		// 	prev = m;
		// }


		// this->machines.push_back(std::make_unique<Assembler>(stx::position2i{11, 3}, yellow_to_red));
		// this->machines.back()->link(prev);
		// prev = *this->machines.back();


		// for(int i = 0; i < 10; i++) {
		// 	this->machines.push_back(std::make_unique<Conveyor>(stx::position2i{12 + i, 3}));
		// 	stx::reference<Machinery::Entity> m = *this->machines.back();
		// 	m->link(prev);
		// 	prev = m;
		// }

		// this->machines.push_back(std::make_unique<Stockpile>(stx::position2i{22, 3}));
		// this->machines.back()->link(prev);
		// prev = *this->machines.back();

		// for(int i = 0; i < 5; i++) {
		// 	this->machines.push_back(std::make_unique<Conveyor>(stx::position2i{23 + i, 3}));
		// 	stx::reference<Machinery::Entity> m = *this->machines.back();
		// 	m->link(prev);
		// 	prev = m;
		// }

		auto s1 = create_source({0,0}, item_yellow, 4);
		auto s2 = create_source({1,1}, item_yellow, 4);

		auto c1 = create_conveyor({0,1}, {*s1, *s2});
		auto c2 = create_conveyor({0,2}, {*c1});
		auto c3 = create_conveyor({0,3}, {*c2});
		auto c4 = create_conveyor({0,4}, {*c3});

		auto a1 = create_assembler({0,5}, {*c4}, yellow_to_red);

		auto c5 = create_conveyor({0,6}, {*a1});
		auto c6 = create_conveyor({0,7}, {*c5});
		
		auto x1 = create_container({0,8}, {*c6});
		
		auto c7 = create_conveyor({0,9}, {*x1});
		auto c8 = create_conveyor({0,10}, {*c7});

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
	}



	void Level::render(sf::RenderTarget & render_target) {
		render_tiles(this->tiles, render_target);
		for(const auto & m : this->machines) {
			render_machine(*m, render_target);
		}
	}
	
	
	
	void Level::init() {
		
	}
}