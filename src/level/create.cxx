#include "create.hxx"



namespace level {
	Machine & create_machine(Machinery & machinery, stx::position2i position, sf::Color color) {
		Machine & machine = machinery.new_entity();

		machine.add(Transform{
			.position = position,
		});

		machine.add(Sprite{
			.color = color,
		});

		machine.add(Status{
			.fetching_done = false,
			.production_done = false,
		});
	
		return machine;
	}



	Machine & create_conveyor(Machinery & machinery, stx::position2i position, const std::vector<std::uint64_t> & prev) {
		Machine & machine = create_machine(machinery, position, sf::Color{64,64,64});

		machine.add(Input{
			.input_ports = prev,
			.input_index = 0,
			.item = stx::nullref,
			.machinery = &machinery,
		});

		machine.add(Pass {
			.item = stx::nullref,
		});

		machine.add(Output {
			.item = stx::nullref,
		});

		return machine;
	}



	Machine & create_source(Machinery & machinery, stx::position2i position, stx::reference<const Item> item, std::uint32_t delay) {
		Machine & machine = create_machine(machinery, position, sf::Color::White);
		
		machine.add(Spawn{
			.item = item,
			.counter = 0,
			.delay = delay,
		});

		machine.add(Output {
			.item = stx::nullref,
		});

		return machine;
	}



	Machine & create_assembler(Machinery & machinery, stx::position2i position, const std::vector<std::uint64_t> & prev, stx::reference<const Recipe> recipe) {
		Machine & machine = create_machine(machinery, position, sf::Color{128,128,128});

		machine.add(Input{
			.input_ports = prev,
			.input_index = 0,
			.item = stx::nullref,
			.machinery = &machinery,
		});

		auto & build = machine.add(Build {
			.recipe = recipe
		});

		for(const auto & material : recipe->from) {
			build.materials.add_slot(ItemStack{material, 1});
		}

		machine.add(Output {
			.item = stx::nullref,
		});

		return machine;
	}



	Machine & create_container(Machinery & machinery, stx::position2i position, const std::vector<std::uint64_t> & prev) {
		Machine & machine = create_machine(machinery, position, sf::Color{196,196,196});

		machine.add(Input{
			.input_ports = prev,
			.input_index = 0,
			.item = stx::nullref,
			.machinery = &machinery,
		});

		machine.add(Pass {
			.item = stx::nullref,
		});

		machine.add(Storage {
			.stack = {}
		});
	
		return machine;
	}
}