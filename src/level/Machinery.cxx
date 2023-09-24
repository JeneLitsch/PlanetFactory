#include "Machinery.hxx"

namespace level {
	void tick_pre(Machinery::Entity & machine) {
		if(auto * input = machine.get_if<Input>()) {
			input->input_index = (input->input_index + 1) % std::size(input->input_ports); 
		}

		if(auto status = machine.get_if<Status>()) {
			status->fetching_done = false;
			status->production_done = false;
		}

		if(auto spawn = machine.get_if<Spawn>()) {
			++spawn->counter;
		}
	}



	namespace {
		stx::optref<const Item> peek_output(Input & input) {
			Machinery * machinery = reinterpret_cast<Machinery*>(input.machinery);
			if(auto * machine = machinery->get_if(input.input_ports[input.input_index])) {
				if(auto * output = machine->get_if<Output>()) {
					return output->item;
				}

				if(auto * storage = machine->get_if<Storage>()) {
					if(!storage->stack.is_empty()) {
						return storage->stack.get_item();
					} 
				}
			}
			return stx::nullref;
		}


		void clear_output(Input & input) {
			Machinery * machinery = reinterpret_cast<Machinery*>(input.machinery);
			if(auto * machine = machinery->get_if(input.input_ports[input.input_index])) {
				if(auto * output = machine->get_if<Output>()) {
					output->item = stx::nullref;
				}

				if(auto * storage = machine->get_if<Storage>()) {
					storage->stack.retrieve(1);
				}
			}
		}



		stx::optref<const Item> take_output(Input & input) {
			if(auto item = peek_output(input)) {
				clear_output(input);
				return item;
			}
			else {
				return stx::nullref;
			}
		}



		bool is_output_clear(Machinery::Entity & machine) {
			auto * output = machine.get_if<Output>();
			return output && !output->item;
		}



		bool fetch(Machinery::Entity & machine, Input & input) {
			if(!std::empty(input.input_ports) && is_output_clear(machine)) {
				if(auto item = take_output(input)) {
					input.item = item;
					return true;
				}
			}
			return false;
		}


		
		bool fetch(Machinery::Entity & machine, Input & input, Build & build) {
			if(!std::empty(input.input_ports) && is_output_clear(machine)) {
				if(auto item = peek_output(input)) {
					if(build.materials.store(*item, 1) == 0) {
						clear_output(input);
					}
					return true;
				}
			}
			return false;
		}



		bool fetch(Machinery::Entity & machine, Input & input, Storage & storage) {
			if(!std::empty(input.input_ports) && (!storage.stack.is_full() || storage.stack.is_empty())) {
				if(auto item = take_output(input)) {
					input.item = item;
					return true;
				}
			}
			return false;
		}



		bool fetch(Machinery::Entity & machine) {
			if(auto * input = machine.get_if<Input>()) {
				if(auto * build = machine.get_if<Build>()) {
					return fetch(machine, *input, *build);
				}
				if(auto * storage = machine.get_if<Storage>()) {
					return fetch(machine, *input, *storage);
				}
				return fetch(machine, *input);
			} 
			return true;
		}



		bool verify_recipe(const Build & build) {
			for(const auto & from : build.recipe->from) {
				if(build.materials.get_amount(from) == 0) {
					return false;
				}
			}
			return true;
		}



		bool produce(Build & build) {
			if(!build.product) {
				if(verify_recipe(build)) {
					for(const auto & material : build.recipe->from) {
						build.materials.retrieve(*material, 1);
					}
					build.product = *build.recipe->to;
					return true;
				}
			}
			return false;
		}



		bool produce(Input & input, Pass & pass) {
			if(input.item && !pass.item) {
				pass.item = input.item;
				input.item = stx::nullref;
				return true;
			}
			return false;
		}



		bool produce(Machinery::Entity & machine) {
			auto * input = machine.get_if<Input>();
			auto * pass = machine.get_if<Pass>();
			auto * build = machine.get_if<Build>();
			if(input && pass) return produce(*input, *pass);
			if(build) return produce(*build);
			return true;
		}
	}



	bool tick_main(Machinery::Entity & machine) {
		if(auto status = machine.get_if<Status>()) {
			if(!status->fetching_done) {
				status->fetching_done = fetch(machine);
			} 

			if(!status->production_done) {
				status->production_done = produce(machine);
			} 

			return status->fetching_done && status->production_done;
		}
		return true;
	}



	void tick_post(Machinery::Entity & machine) {
		auto * pass = machine.get_if<Pass>();
		auto * output = machine.get_if<Output>();
		auto * spawn = machine.get_if<Spawn>();
		auto * build = machine.get_if<Build>();
		auto * storage = machine.get_if<Storage>();

		if(pass && output) {
			if(pass->item && !output->item) {
				output->item = pass->item;
			}
			pass->item = stx::nullref;
		}

		if(spawn && output) {
			if(spawn->counter % spawn->delay == 0) {
				output->item = *spawn->item;
			}
		}

		if(pass && storage) {
			if(pass->item) {
				if(storage->stack.is_empty()) {
					storage->stack = ItemStack{*pass->item, 5};
				}
				if(!storage->stack.is_full() && storage->stack.get_item() == pass->item) {
					storage->stack.store(1);
				}
			}
			pass->item = stx::nullref;
		}

		if(build && output) {
			if(!output->item) {
				if(auto item = std::exchange(build->product, stx::nullref)) {
					output->item = item;
				}
			}
		}
	}



	void render(Machinery::Entity & machine, sf::RenderTarget & target) {
		auto * transform = machine.get_if<Transform>();
		auto * output = machine.get_if<Output>();
		auto * sprite = machine.get_if<Sprite>();
		auto * storage = machine.get_if<Storage>();

		if(transform && sprite) {
			sf::RectangleShape main_rect;
			main_rect.setSize({1,1});
			main_rect.setFillColor(sprite->color),
			main_rect.setPosition(transform->position.x, transform->position.y);
			target.draw(main_rect);
		}

		if(transform && output && output->item) {
			sf::RectangleShape item_rect;
			item_rect.setSize({0.5,0.5});
			item_rect.setFillColor(output->item->color),
			item_rect.setPosition(transform->position.x + 0.25, transform->position.y + 0.25);
			target.draw(item_rect);
		}

		if(transform && storage) {
			for(std::int32_t i = 0; i < storage->stack.get_amount(); i++) {
				sf::RectangleShape item_rect;
				item_rect.setSize({0.5,0.1});
				item_rect.setFillColor(storage->stack.get_item()->color),
				item_rect.setPosition(transform->position.x + 0.25, transform->position.y + 0.25 + 0.1 * i);
				target.draw(item_rect);
			}
		}
	}



	Machinery::Entity & create_machine(Machinery & machinery, stx::position2i position, sf::Color color) {
		Machinery::Entity & machine = machinery.new_entity();

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



	Machinery::Entity & create_conveyor(Machinery & machinery, stx::position2i position, const std::vector<std::uint64_t> & prev) {
		Machinery::Entity & machine = create_machine(machinery, position, sf::Color{64,64,64});

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



	Machinery::Entity & create_source(Machinery & machinery, stx::position2i position, stx::reference<const Item> item, std::uint32_t delay) {
		Machinery::Entity & machine = create_machine(machinery, position, sf::Color::White);
		
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



	Machinery::Entity & create_assembler(Machinery & machinery, stx::position2i position, const std::vector<std::uint64_t> & prev, stx::reference<const Recipe> recipe) {
		Machinery::Entity & machine = create_machine(machinery, position, sf::Color{128,128,128});

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



	Machinery::Entity & create_container(Machinery & machinery, stx::position2i position, const std::vector<std::uint64_t> & prev) {
		Machinery::Entity & machine = create_machine(machinery, position, sf::Color{196,196,196});

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