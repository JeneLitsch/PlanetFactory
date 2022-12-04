#include "create.hxx"

namespace level {
	void connect(Machine & from, const Machine & to) {
		from.add(Connects{
			.machine_id = to.get_id()
		});
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



	std::pair<Machine &, Machine &> new_conveyor_belt(MachineEcs & ecs, std::vector<stx::position2i> steps) {
		stx::optref<Machine> first = stx::nullref;
		stx::optref<Machine> prev = stx::nullref;
		for(const auto & step : steps) {
			auto & conveyor = new_conveyor(ecs, step);
			if(prev) {
				connect(*prev, conveyor);
			}
			if(!first) {
				first = conveyor;
			}
			prev = conveyor;
		}

		return { *first, *prev };
	}
	


	Machine & new_miner(MachineEcs & ecs, stx::position2i xy) {
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
			.item = test,
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
}