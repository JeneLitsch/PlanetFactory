#pragma once
#include "stdxx/reference.hxx"
#include "stdxx/vector.hxx"
#include "level/Item.hxx"

namespace level {
	struct Location {
		stx::position2i xy;
	};

	struct Storage {
		stx::optref<const Item> item;
	};

	struct Sprite {
		sf::Color color;
	};

	struct Connects {
		std::vector<std::uint64_t> machine_ids;
		std::size_t next_output;
	};

	struct Sink {
		std::uint64_t frequency;
		std::uint64_t tick_counter;
	};

	struct Source {
		stx::reference<const Item> item;
		std::uint64_t frequency;
		std::uint64_t tick_counter;
	};

	struct Recipe {
		stx::reference<const Item> from;
		stx::reference<const Item> to;
		std::uint64_t frequency;
		std::uint64_t tick_counter;
	};
}