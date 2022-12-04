#pragma once
#include "level/Item.hxx"
#include "ecs.hxx"

namespace level {
	void item_transfer(Machine & machine, MachineEcs & machines);
	std::vector<std::uint64_t> determine_transfer_order(const MachineEcs & machines);
}