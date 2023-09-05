#include "ItemStorage.hxx"

namespace level {
	void ItemStorage::add_slot(ItemSlot slot) {
		this->slots.push_back(slot);
	}


	
	std::int32_t ItemStorage::store(stx::reference<const Item> item, std::int32_t amount) {
		for(auto & slot : this->slots) {
			if(slot.get_item() == *item) {
				amount = slot.store(amount);
			}
		}
		return amount;
	}



	std::int32_t ItemStorage::retrieve(stx::reference<const Item> item, std::int32_t amount) {
		for(auto & slot : this->slots) {
			if(slot.get_item() == *item) {
				amount = slot.retrieve(amount);
			}
		}
		return amount;
	}



	std::int32_t ItemStorage::get_amount(stx::reference<const Item> item) const {
		std::int32_t amount = 0;
		for(auto & slot : this->slots) {
			if(slot.get_item() == *item) {
				amount += slot.get_amount();
			}
		}
		return amount;
	}


	void ItemStorage::print() const {
		for(auto & slot : this->slots) {
			std::cout << slot.get_item()->name << " x" << slot.get_amount() << "\n";
 		}
	}
}