#include "SimpleInput.hxx"
#include "level/output/Output.hxx"

namespace level {
	void SimpleInput::prepare() {
		if(!std::empty(ports)) {
			this->index = (this->index + 1) % std::size(this->ports); 
		}
	}

	stx::optref<const Item> SimpleInput::peek_suplier() const {
		if(std::empty(this->ports)) return stx::nullref;
		return this->ports[this->index]->peek();
	}

	void SimpleInput::clear_suplier() {
		this->ports[this->index]->clear();
	}

	void SimpleInput::store(stx::optref<const Item> item) {
		this->item = item;
	}

	stx::optref<const Item> SimpleInput::peek() const {
		return this->item;
	}
	
	void SimpleInput::clear() {
		this->item = stx::nullref;
	}

	void SimpleInput::link(stx::reference<Output> suplier) {
		ports.push_back(suplier);
	}
	
	void SimpleInput::unlink(stx::reference<Output> suplier) {
		throw std::runtime_error{""};
	}
}