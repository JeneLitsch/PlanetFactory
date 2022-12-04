#include "produce.hxx"

namespace level {
	bool is_ready(auto & producer) {
		++producer.tick_counter;
		if(producer.tick_counter >= producer.frequency) {
			producer.tick_counter = 0;
			return true;
		}
		return false;
	}


	void produce_source(Machine & machine) {
		auto * source = machine.get_if<Source>();
		auto * storage = machine.get_if<Storage>();

		if(!source) return;
		if(!storage) return;
		if(storage->item) return;

		if(is_ready(*source)) {
			storage->item = *source->item;
		}
	}


	void produce_sink(Machine & machine) {
		auto * sink = machine.get_if<Sink>();
		auto * storage = machine.get_if<Storage>();

		if(!sink) return;
		if(!storage) return;
		if(!storage->item) return;

		if(is_ready(*sink)) {
			storage->item = stx::nullref;
		}
	}


	void produce_recipe(Machine & machine) {
		auto * recipe = machine.get_if<Recipe>();
		auto * storage = machine.get_if<Storage>();

		if(!recipe) return;
		if(!storage) return;
		if(!storage->item) return;

		if(is_ready(*recipe)) {
			if(&*storage->item == &*recipe->from) {
				storage->item = *recipe->to;
			}
		}
	}
}