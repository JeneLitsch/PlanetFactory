#include "Level.hxx"
#include <iostream>
#include <random>
#include "render.hxx"
#include "stdxx/io.hxx"

namespace level {
	Level::Level(stx::size2u size, std::uint64_t seed) 
	: tiles{size, Tile{rock}}, machines{1}, tick {0.5} {
		std::mt19937_64 rng{seed};

		auto [first, last] = new_conveyor_belt(this->machines, {
			{5,5},{6,5}, {7,5}, {8,5}, {9,5}, {10,5}, {11,5}, {12,5}, {13,5},
		});

		auto & miner = new_miner(this->machines, {4,5}); 
		auto & sink = new_sink(this->machines, {14,5}); 

		connect(miner, first);
		connect(last, sink);
	}



	void Level::update(double dt) {
		if(tick(dt)) {
			machines.run_system(produce_sink);
			auto order = determine_transfer_order(this->machines);
			std::cout << stx::whole(order) << "\n";
			machines.run_system_for(order, [&] (Machine & machine) {
				return item_transfer(machine, this->machines);
			});
			machines.run_system(produce_source);
		}
	}



	void Level::render(sf::RenderTarget & render_target) {
		render_tiles(this->tiles, render_target);
		this->machines.run_system([&] (Machine & m) {
			return render_machine(m, render_target);
		});
	}
	
	
	
	void Level::init() {
		
	}
}