#pragma once
#include "ecs.hxx"

namespace level {
	Machine & new_conveyor(
		MachineEcs & ecs,
		stx::position2i xy
	);
	
	std::vector<stx::reference<Machine>> new_conveyor_belt(
		MachineEcs & ecs,
		std::vector<stx::position2i> steps
	);

	Machine & new_miner(
		MachineEcs & ecs,
		stx::position2i xy,
		const Item & item
	);
	
	Machine & new_sink(
		MachineEcs & ecs,
		stx::position2i xy
	);
	
	Machine & new_assembler(
		MachineEcs & ecs,
		stx::position2i xy,
		const Item & from,
		const Item & to
	);
	
	void connect(Machine & from, const Machine & to);
}