#include "NoInput.hxx"

namespace level {
	void NoInput::prepare() {

	}



	bool NoInput::fetch_suply() {
		return true;
	}



	stx::optref<const Item> NoInput::peek() const {
		return stx::nullref;
	}
	


	void NoInput::clear() {

	}



	void NoInput::link(stx::reference<Output> suplier) {}



	void NoInput::unlink(stx::reference<Output> suplier) {}
}