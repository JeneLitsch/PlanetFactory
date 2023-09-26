#include "Builder.hxx"

namespace level {
	Builder::Builder(stx::reference<const Recipe> recipe)
		: recipe {recipe} {
		
		for(const auto & material : recipe->from) {
			this->materials.add_slot(ItemStack{material, 1});
		}
	};



	void Builder::prepare() {}



	std::tuple<bool, bool> Builder::produce(stx::optref<const Item> item) {
		if(!this->product) {
			bool clear = true;
			if(this->materials.store(*item, 1) == 0) {
				clear = true;
			}
			if(verify_recipe()) {
				for(const auto & material : this->recipe->from) {
					this->materials.retrieve(*material, 1);
				}
				this->product = *this->recipe->to;
				return { true, clear };
			}
		}
		return { false, false };
	}



	stx::optref<const Item> Builder::take() {
		return std::exchange(this->product, stx::nullref);
	}



	bool Builder::verify_recipe() const {
		for(const auto & from : this->recipe->from) {
			if(this->materials.get_amount(from) == 0) {
				return false;
			}
		}
		return true;
	}
}