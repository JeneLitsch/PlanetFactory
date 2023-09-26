#pragma once
#include "Machine.hxx"
#include "Recipe.hxx"

namespace level {
	std::unique_ptr<Machine> create_conveyor(stx::position2i position, stx::position2i rotation);
	std::unique_ptr<Machine> create_source(stx::position2i position, stx::position2i rotation, stx::reference<const Item> item, std::uint32_t delay);
	std::unique_ptr<Machine> create_assembler(stx::position2i position, stx::position2i rotation, stx::reference<const Recipe> recipe);
	std::unique_ptr<Machine> create_container(stx::position2i position, stx::position2i rotation);

	void link_machines(Machine & from, Machine & to);
}