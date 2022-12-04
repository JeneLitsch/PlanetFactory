#include "Level.hxx"
#include <iostream>
#include <random>
#include "render.hxx"
#include "stdxx/io.hxx"

namespace level {
	Level::Level(stx::size2u size, std::uint64_t seed) 
	: tiles{size, Tile{rock}}, machines{1}, tick {0.5} {
		std::mt19937_64 rng{seed};

		auto belt_a = new_conveyor_belt(this->machines, {
			{5,5},{6,5}, {7,5}, {8,5}, {9,5}, {10,5}, {11,5}, {12,5}, {13,5},
		});

		auto belt_b = new_conveyor_belt(this->machines, {
			{14,6},
			{14,7},
			{14,8},
			{14,9},
			{14,10},
			{14,11},
			{14,12},
			{14,13},
		});

		auto & miner = new_miner(this->machines, {4,5}, item_blue);
		auto & miner2 = new_miner(this->machines, {5,4}, item_blue);
		auto & assembler = new_assembler(this->machines, {14,5}, item_blue, item_yellow); 
		auto & sink = new_sink(this->machines, {14,14}); 

		connect(miner, belt_a.front());
		connect(miner2, belt_a.front());
		connect(belt_a.back(), assembler);
		connect(assembler, belt_b.front());
		connect(belt_b.back(), sink);
	}



	void Level::update(double dt) {
		if(tick(dt)) {
			machines.run_system(produce_sink);
			machines.run_system(produce_recipe);
			auto order = determine_transfer_order(this->machines);
			// std::cout << stx::whole(order) << "\n";
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