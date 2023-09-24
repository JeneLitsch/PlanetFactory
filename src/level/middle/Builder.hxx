#pragma once
#include "Middle.hxx"
#include "level/Recipe.hxx"
#include "level/ItemStorage.hxx"

namespace level {
	class Builder : public Middle {
	public:
		Builder(stx::reference<const Recipe> recipe)
			: recipe {recipe} {
			
			for(const auto & material : recipe->from) {
				this->materials.add_slot(ItemStack{material, 1});
			}
		};

		virtual void prepare() override {

		}

		virtual std::tuple<bool, bool> produce(stx::optref<const Item> item) override {
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

		virtual stx::optref<const Item> take() override {
			return std::exchange(this->product, stx::nullref);
		}

	private:
		bool verify_recipe() {
			for(const auto & from : this->recipe->from) {
				if(this->materials.get_amount(from) == 0) {
					return false;
				}
			}
			return true;
		}

		stx::reference<const Recipe> recipe;
		ItemStorage materials;
		stx::optref<const Item> product;
	};
}