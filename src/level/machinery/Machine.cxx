#include "Machine.hxx"

namespace level {
	Machine::Machine(stx::position2i position)
		: position{position} {}



	stx::position2i Machine::get_position() const {
		return this->position;
	}



	void Machine::tick_main() {
		if(!this->fetching_done) {
			this->fetch();
		} 

		if(!this->production_done) {
			this->produce();
		} 
	}



	stx::optref<const Item> Machine::take_output() {
		if(auto item = this->peek_output()) {
			this->clear_output();
			return item;
		}
		else {
			return stx::nullref;
		}
	}
}