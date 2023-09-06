#include "SimpleOutput.hxx"

namespace level {
	bool SimpleOutput::is_clear() const {
		return !this->item;
	}



	void SimpleOutput::push(stx::optref<const Item> item) {
		this->item = item;
	}



	bool SimpleOutput::is_ready() const {
		return this->item;
	}



	stx::optref<const Item> SimpleOutput::get() const {
		return this->item;
	}



	void SimpleOutput::discard() {
		this->item = stx::nullref;
	}



	void SimpleOutput::prepare() {

	}



	bool SimpleOutput::process() {
		return true;
	}
}