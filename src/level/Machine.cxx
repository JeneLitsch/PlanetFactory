#include "Machine.hxx"

namespace level {
	Machine::Machine(stx::position2i position)
		: position{position} {}



	stx::position2i Machine::get_position() const {
		return this->position;
	}
}