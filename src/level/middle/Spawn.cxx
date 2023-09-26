#include "Spawn.hxx"

namespace level {
	Spawn::Spawn(stx::reference<const Item> item) : item {item} {}



	void Spawn::prepare() {
		++this->counter;
	}



	std::tuple<bool, bool> Spawn::produce(stx::optref<const Item> item) {
		return {true,true};
	}



	stx::optref<const Item> Spawn::take() {
		return (this->counter % this->delay == 0) ? stx::optref{*this->item} : stx::nullref;
	}
}