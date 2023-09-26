#include "NoInput.hxx"

namespace level {
	void NoInput::prepare() {
		
	}



	stx::optref<const Item> NoInput::peek_suplier() const {
		return stx::nullref;
	}



	void NoInput::clear_suplier() {

	}



	void NoInput::store(stx::optref<const Item> item) {

	}



	stx::optref<const Item> NoInput::peek() const {
		return stx::nullref;
	}
	


	void NoInput::clear() {

	}



	void NoInput::link(stx::reference<Output> suplier) {}



	void NoInput::unlink(stx::reference<Output> suplier) {}
}