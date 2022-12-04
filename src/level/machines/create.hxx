#pragma once
#include "ecs.hxx"

namespace level {
	Machine & new_conveyor(MachineEcs & ecs, stx::position2i xy);
	std::pair<Machine &, Machine &> new_conveyor_belt(MachineEcs & ecs, std::vector<stx::position2i> steps);
	Machine & new_miner(MachineEcs & ecs, stx::position2i xy);
	Machine & new_sink(MachineEcs & ecs, stx::position2i xy);
	void connect(Machine & from, const Machine & to);
}