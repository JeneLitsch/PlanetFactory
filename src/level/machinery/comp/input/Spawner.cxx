#include "Spawner.hxx"

namespace level {
	Spawner::Spawner(stx::reference<const Item> to_be_produced)
		: to_be_produced{to_be_produced}
		, item{stx::nullref} {}

	

	void Spawner::link(stx::reference<Machine> machine) {}
	
	
	
	bool Spawner::is_ready() const {
		return this->item;
	}



	stx::optref<const Item> Spawner::pull() {
		return std::exchange(this->item, stx::nullref);
	}



	void Spawner::prepare() {
		++this->counter;
	}

	
	
	bool Spawner::process() {
		if(counter % 4 == 0) {
			this->item = *this->to_be_produced;
			return true;
		}
		return false;
	}
}