#include "tick.hxx"

namespace level {
	namespace {
		stx::optref<const Item> get_tmp_item(Machine & machine) {
			if(auto * pass = machine.get_if<Pass>()) {
				return std::exchange(pass->item, stx::nullref);
			}

			if(auto * build = machine.get_if<Build>()) {
				return std::exchange(build->product, stx::nullref);
			}

			if(auto * spawn = machine.get_if<Spawn>()) {
				return (spawn->counter % spawn->delay == 0) ? stx::optref{*spawn->item} : stx::nullref;
			}
		}



		void store_output_item(Machine & machine, stx::reference<const Item> item) {
			if(auto * output = machine.get_if<Output>()) {
				output->item = *item;
			}

			if(auto * storage = machine.get_if<Storage>()) {
				if(storage->stack.is_empty()) {
					storage->stack = ItemStack{item, 5};
				}
				if(!storage->stack.is_full() && storage->stack.get_item() == *item) {
					storage->stack.store(1);
				}
			}
		}
	}



	void tick_post(Machine & machine) {
		if(is_output_clear(machine)) {
			if(const auto item = get_tmp_item(machine)) {
				store_output_item(machine, *item);
			}
		}
	}
}