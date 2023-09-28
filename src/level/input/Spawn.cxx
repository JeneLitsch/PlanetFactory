#include "Spawn.hxx"

namespace level {
	Spawn::Spawn(stx::optref<const Item> item) : item {item} {}



	void Spawn::prepare() {
		++this->counter;
	}



	bool Spawn::fetch_suply() {
		return true;
	}	



	stx::optref<const Item> Spawn::peek() const {
		return (this->counter % this->delay == 0) ? stx::optref{*this->item} : stx::nullref;
	}



	void Spawn::clear() {

	}



	void Spawn::link(stx::reference<Output> suplier) {

	}



	void Spawn::unlink(stx::reference<Output> suplier) {

	}
}