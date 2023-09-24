#include "tick.hxx"

namespace level {
	namespace {
		stx::optref<const Item> peek_suplier(Machine & machine) {
			auto * input = machine.get_if<Input>();
			if(!input) return stx::nullref;
			if(std::empty(input->input_ports)) return stx::nullref;

			Machinery * machinery = reinterpret_cast<Machinery*>(input->machinery);
			if(auto * machine = machinery->get_if(input->input_ports[input->input_index])) {
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



		void clear_suplier(Machine & machine) {
			auto * input = machine.get_if<Input>();
			if(!input) return;

			Machinery * machinery = reinterpret_cast<Machinery*>(input->machinery);
			if(auto * machine = machinery->get_if(input->input_ports[input->input_index])) {
				if(auto * output = machine->get_if<Output>()) {
					output->item = stx::nullref;
				}

				if(auto * storage = machine->get_if<Storage>()) {
					storage->stack.retrieve(1);
				}
			}
		}



		bool store_input(Machine & machine, stx::reference<const Item> item) {
			if(auto * input = machine.get_if<Input>()) {
				input->item = *item;
				return true;
			}
			return false;
		}



		bool fetch(Machinery::Entity & machine) {
			if(is_output_clear(machine)) {
				if(auto item = peek_suplier(machine)) {
					if(store_input(machine, *item)) {
						clear_suplier(machine);
					}
					return true;
				}
			}

			return false;
		}



		bool verify_recipe(const Build & build) {
			for(const auto & from : build.recipe->from) {
				if(build.materials.get_amount(from) == 0) {
					return false;
				}
			}
			return true;
		}



		stx::optref<const Item> get_input_item(Machine & machine) {
			if(auto * input = machine.get_if<Input>()) {
				return input->item;
			}
			return stx::nullref;
		}



		void clear_input_item(Machine & machine) {
			if(auto * input = machine.get_if<Input>()) {
				input->item = stx::nullref;
			}
		}



		std::tuple<bool, bool> produce(stx::optref<const Item> item, Machine & machine) {
			if(auto * build = machine.get_if<Build>()) {
				if(!build->product) {
					bool clear = true;
					if(build->materials.store(*item, 1) == 0) {
						clear = true;
					}
					if(verify_recipe(*build)) {
						for(const auto & material : build->recipe->from) {
							build->materials.retrieve(*material, 1);
						}
						build->product = *build->recipe->to;
						return { true, clear };
					}
				}
				return { false, false };
			}
			if(auto * pass = machine.get_if<Pass>()) {
				if(item && !pass->item) {
					pass->item = item;
					return {true,true};
				}
				return {false,false};
			}

			return {true,false};
		}



		bool produce(Machine & machine) {
			auto item = get_input_item(machine);
			auto [done,clear] = produce(item, machine);
			if(clear) clear_input_item(machine);
			return done;
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