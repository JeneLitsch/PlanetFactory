#include "RecipeBuilder.hxx"

namespace level {
	RecipeBuilder::RecipeBuilder(stx::reference<const Recipe> recipe)
		: recipe{recipe} {
		
		for(const auto & material : this->recipe->from) {
			this->materials.add_slot(ItemStack{material, 1});
		}
	}


	
	bool RecipeBuilder::push(stx::reference<const Item> item) {
		return materials.store(*item, 1) == 0;
	}



	bool RecipeBuilder::process() {
		if(!this->product) {
			if(this->verify_recipe()) {
				this->product = *this->recipe->to;
				for(const auto & material : this->recipe->from) {
					this->materials.retrieve(*material, 1);
				}
				return true;
			}
		}
		return false;
	}



	bool RecipeBuilder::verify_recipe() const {
		for(const auto & from : this->recipe->from) {
			if(this->materials.get_amount(from) == 0) {
				return false;
			}
		}
		return true;
	}



	stx::optref<const Item> RecipeBuilder::pull() {
		return std::exchange(this->product, stx::nullref);
	}
}