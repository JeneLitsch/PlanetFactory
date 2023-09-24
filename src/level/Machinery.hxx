#pragma once
#include "stdxx/reference.hxx"
#include "nanocomp/nanocomp.hpp"
#include "Item.hxx"
#include "ItemStorage.hxx"
#include "ItemStack.hxx"
#include "Recipe.hxx"

namespace level {
	struct Sprite {
		sf::Color color;
	};

	struct Transform {
		stx::position2i position;
	};

	struct Status {
		bool fetching_done = false;
		bool production_done = false; 
	};

	struct Input {
		stx::optref<const Item> item;
		std::vector<std::uint64_t> input_ports;
		std::size_t input_index = 0;
		void * machinery;
	};

	struct Spawn {
		stx::reference<const Item> item;
		std::uint32_t counter = 0;
		std::uint32_t delay = 1;
	};

	struct Build {
		stx::reference<const Recipe> recipe;
		ItemStorage materials;
		stx::optref<const Item> product;
	};

	struct Pass {
		stx::optref<const Item> item;
	};

	struct Output {
		stx::optref<const Item> item;
	};

	struct Storage {
		ItemStack stack;
	};
	
	using Machinery = nc::Ecs<
		Transform, Sprite, Status,
		Input, Spawn,
		Pass, Build,
		Output, Storage
	>;

	void tick_pre(Machinery::Entity & machine);
	bool tick_main(Machinery::Entity & machine);
	void tick_post(Machinery::Entity & machine);

	void render(Machinery::Entity & machine, sf::RenderTarget & target);

	Machinery::Entity & create_conveyor(Machinery & machinery, stx::position2i position, const std::vector<std::uint64_t> & prev);
	Machinery::Entity & create_source(Machinery & machinery, stx::position2i position, stx::reference<const Item> item, std::uint32_t delay);
	Machinery::Entity & create_assembler(Machinery & machinery, stx::position2i position, const std::vector<std::uint64_t> & prev, stx::reference<const Recipe> recipe);
	Machinery::Entity & create_container(Machinery & machinery, stx::position2i position, const std::vector<std::uint64_t> & prev);
}