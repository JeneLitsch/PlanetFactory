#include "create.hxx"

namespace level {
	void connect(Machine & from, const Machine & to) {
		if(!from.has<Connects>()) {
			from.add(Connects{
				.machine_ids = {},
				.next_output = 0,
			});
		}
		auto & connects = from.get<Connects>();
		connects.machine_ids.push_back(to.get_id());
	}

	Machine & new_conveyor(MachineEcs & ecs, stx::position2i xy) {
		auto & machine = ecs.new_entity();
		machine.add(Sprite{
			.color = sf::Color{16,16,16}
		});
		machine.add(Location{
			.xy = xy
		});
		machine.add(Storage{
			.item = stx::nullref
		});
		return machine;
	}



	std::vector<stx::reference<Machine>> new_conveyor_belt(MachineEcs & ecs, std::vector<stx::position2i> steps) {
		std::vector<stx::reference<Machine>> machines;
		stx::optref<Machine> prev = stx::nullref;
		for(const auto & step : steps) {
			auto & conveyor = new_conveyor(ecs, step);
			if(prev) {
				connect(*prev, conveyor);
			}
			machines.push_back(conveyor);
			prev = conveyor;
		}

		return machines;
	}
	


	Machine & new_miner(
		MachineEcs & ecs,
		stx::position2i xy,
		const Item & item) {
		
		auto & machine = ecs.new_entity();
		machine.add(Sprite{
			.color = sf::Color::Green
		});
		machine.add(Location{
			.xy = xy
		});
		machine.add(Storage{
			.item = stx::nullref
		});
		machine.add(Source{
			.item = item,
			.frequency = 2,
			.tick_counter = 0,
		});
		return machine;
	}



	Machine & new_sink(MachineEcs & ecs, stx::position2i xy) {
		auto & machine = ecs.new_entity();
		machine.add(Sprite{
			.color = sf::Color::Red
		});
		machine.add(Location{
			.xy = xy
		});
		machine.add(Storage{
			.item = stx::nullref
		});
		machine.add(Sink{
			.frequency = 1,
			.tick_counter = 0,
		});
		return machine;
	}



	Machine & new_assembler(
		MachineEcs & ecs,
		stx::position2i xy,
		const Item & from,
		const Item & to) {
		
		auto & machine = ecs.new_entity();
		machine.add(Sprite{
			.color = to.color
		});
		machine.add(Location{
			.xy = xy
		});
		machine.add(Storage{
			.item = stx::nullref
		});
		machine.add(Recipe{
			.from = from,
			.to = to,
			.frequency = 1,
			.tick_counter = 0,
		});
		return machine;
	}
}