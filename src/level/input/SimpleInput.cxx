#include "SimpleInput.hxx"
#include "level/output/Output.hxx"

namespace level {
	SimpleInput::~SimpleInput() {
		for(const auto & o : this->ports) {
			o->unlink(*this);
		}
	}	


	
	void SimpleInput::prepare() {
		if(!std::empty(ports)) {
			this->index = (this->index + 1) % std::size(this->ports); 
		}
	}



	bool SimpleInput::fetch_suply() {
		if(std::empty(this->ports)) return false;
		if(auto item = this->ports[this->index]->peek()) {
			this->item = item;
			this->ports[this->index]->clear();
			return true;
		} 
		return false;
	}



	stx::optref<const Item> SimpleInput::peek() const {
		return this->item;
	}
	


	void SimpleInput::clear() {
		this->item = stx::nullref;
	}



	void SimpleInput::link(stx::reference<Output> suplier) {
		ports.push_back(suplier);
		suplier->back_link(*this);
	}
	


	void SimpleInput::unlink(stx::reference<Output> suplier) {
		std::erase(this->ports, suplier);
	}
}