#include "SimpleInput.hxx"
#include "level/machinery/Machine.hxx"

namespace level {
	void SimpleInput::link(stx::reference<Machine> machine) {
		this->input_ports.push_back(machine);
	}
	
	
	
	bool SimpleInput::is_ready() const {
		return this->item;
	}



	stx::optref<const Item> SimpleInput::pull() {
		return std::exchange(this->item, stx::nullref);
	}



	void SimpleInput::prepare() {
		this->input_index = (this->input_index + 1) % std::size(this->input_ports);
	}

	
	
	bool SimpleInput::process() {
		if(!std::empty(this->input_ports)) {
			if(auto item = this->input_ports[this->input_index]->take_output()) {
				this->item = item;
				return true;
			}
		}
		return false;
	}
}