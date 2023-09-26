#include "Pass.hxx"

namespace level {
	void Pass::prepare() {};



	std::tuple<bool, bool> Pass::produce(stx::optref<const Item> item) {
		if(item && !this->item) {
			this->item = item;
			return {true,true};
		}
		return {false,false};
	}



	stx::optref<const Item> Pass::take() {
		return std::exchange(this->item, stx::nullref);
	}
}