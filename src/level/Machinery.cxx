#include "Machinery.hxx"

namespace level {
	bool is_output_clear(Machine & machine) {
		if(auto * output = machine.get_if<Output>()) {
			return !output->item;
		}

		if(auto * storage = machine.get_if<Storage>()) {
			return !storage->stack.is_full() || storage->stack.is_empty();
		}
		return false;
	}
}