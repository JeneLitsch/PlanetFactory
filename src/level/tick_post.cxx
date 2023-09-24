#include "tick.hxx"

namespace level {
	namespace {
		void tick_post(Pass & pass, Output & output) {
			if(pass.item && !output.item) {
				output.item = pass.item;
			}
			pass.item = stx::nullref;
		}


		
		void tick_post(Spawn & spawn, Output & output) {
			if(spawn.counter % spawn.delay == 0) {
				output.item = *spawn.item;
			}
		}



		void tick_post(Pass & pass, Storage & storage) {
			if(pass.item) {
				if(storage.stack.is_empty()) {
					storage.stack = ItemStack{*pass.item, 5};
				}
				if(!storage.stack.is_full() && storage.stack.get_item() == pass.item) {
					storage.stack.store(1);
				}
			}
			pass.item = stx::nullref;
		}



		void tick_post(Build & build, Output & output) {
			if(!output.item) {
				if(auto item = std::exchange(build.product, stx::nullref)) {
					output.item = item;
				}
			}
		}
	}

	void tick_post(Machinery::Entity & machine) {
		auto * pass = machine.get_if<Pass>();
		auto * output = machine.get_if<Output>();
		auto * spawn = machine.get_if<Spawn>();
		auto * build = machine.get_if<Build>();
		auto * storage = machine.get_if<Storage>();

		if(pass && output) tick_post(*pass, *output);
		if(spawn && output) tick_post(*spawn, *output);
		if(pass && storage) tick_post(*pass, *storage);
		if(build && output) tick_post(*build, *output);
	}
}