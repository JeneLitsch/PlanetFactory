#include "Machine.hxx"

namespace level {
	namespace {
		bool fetch(Machine & machine) {
			if(machine.output->is_clear()) {
				if(auto item = machine.input->peek_suplier()) {
					machine.input->store(item);
					machine.input->clear_suplier();
					return true;
				}
			}
			return false;
		}



		bool produce(Machine & machine) {
			auto item = machine.input->peek();
			auto [done,clear] = machine.middle->produce(item);
			if(clear) machine.input->clear();
			return done;
		}
	}


	void Machine::tick_pre() {
		this->fetching_done = false;
		this->production_done = false;

		this->input->prepare();
		this->middle->prepare();
		this->output->prepare();
	}

	bool Machine::tick_main() {
		if(!this->fetching_done) {
			this->fetching_done = fetch(*this);
		} 

		if(!this->production_done) {
			this->production_done = produce(*this);
		}
		return this->production_done && this->fetching_done;
	}

	void Machine::tick_post() {
		if(this->output->is_clear()) {
			if(const auto item = this->middle->take()) {
				this->output->store(item);
			}
		}
	}
}