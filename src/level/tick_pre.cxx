#include "tick.hxx"

namespace level {
	void tick_pre(Input & input) {
		input.input_index = (input.input_index + 1) % std::size(input.input_ports); 
	}


	void tick_pre(Status & status) {
		status.fetching_done = false;
		status.production_done = false;
	}



	void tick_pre(Spawn & spawn) {
		++spawn.counter;
	}



	void tick_pre(Machine & machine) {
		if(auto * input  = machine.get_if<Input>())  tick_pre(*input);
		if(auto * status = machine.get_if<Status>()) tick_pre(*status);
		if(auto * spawn  = machine.get_if<Spawn>())  tick_pre(*spawn);
	}
}