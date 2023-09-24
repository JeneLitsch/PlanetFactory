#pragma once
#include "Machinery.hxx"

namespace level {
	Machine & create_conveyor(Machinery & machinery, stx::position2i position, const std::vector<std::uint64_t> & prev);
	Machine & create_source(Machinery & machinery, stx::position2i position, stx::reference<const Item> item, std::uint32_t delay);
	Machine & create_assembler(Machinery & machinery, stx::position2i position, const std::vector<std::uint64_t> & prev, stx::reference<const Recipe> recipe);
	Machine & create_container(Machinery & machinery, stx::position2i position, const std::vector<std::uint64_t> & prev);
}