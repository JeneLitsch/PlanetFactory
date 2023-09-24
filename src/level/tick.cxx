#include "tick.hxx"

namespace level {
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
}