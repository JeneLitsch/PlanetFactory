#include "PassThrough.hxx"

namespace level {
	bool PassThrough::is_clear() const {
		return !this->item;
	}



	void PassThrough::push(stx::optref<const Item> item) {
		this->item = item;
	}
	


	bool PassThrough::is_ready() const {
		return this->item;
	}
	


	stx::optref<const Item> PassThrough::pull() {
		return std::exchange(this->item, stx::nullref);
	}



	void PassThrough::prepare() {
	
	}



	bool PassThrough::process() {
		return true;
	}
}