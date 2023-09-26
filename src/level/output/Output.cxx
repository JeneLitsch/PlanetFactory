#include "Output.hxx"
#include "level/input/Input.hxx"

namespace level {
	Output::~Output() {
		for(const auto & i : this->connected_inputs) {
			i->unlink(*this);
		}
	}



	void Output::back_link(stx::reference<Input> succesor_input) {
		this->connected_inputs.insert(succesor_input);
	}



	void Output::unlink(stx::reference<Input> succesor_input) {
		this->connected_inputs.erase(succesor_input);
	}
}