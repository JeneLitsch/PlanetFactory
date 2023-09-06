#include "ItemStack.hxx"

namespace level {
	ItemStack::ItemStack()
		: item {stx::nullref}
		, capacity{0}
		, amount{0} {}


	ItemStack::ItemStack(stx::reference<const Item> item, std::int32_t capacity)
		: item {*item}
		, capacity{capacity}
		, amount{0} {}



	std::int32_t ItemStack::store(std::int32_t amount) {
		const std::int32_t remaining = this->capacity - this->amount;
		if(remaining < amount) {
			this->amount = this->capacity;
			return amount - remaining;
		}
		else {
			this->amount += amount;
			return 0;
		}
	}



	std::int32_t ItemStack::retrieve(std::int32_t amount) {
		if(this->amount < amount) {
			this->amount = 0;
			return amount - this->amount;
		}
		else {
			this->amount -= amount;
			return 0;
		}
	}



	std::int32_t ItemStack::get_amount() const {
		return this->amount;
	}



	std::int32_t ItemStack::get_capacity() const {
		return this->capacity;
	}



	bool ItemStack::is_empty() const {
		return this->amount <= 0;
	}



	bool ItemStack::is_full() const {
		return this->amount >= this->capacity;
	}



	stx::optref<const Item> ItemStack::get_item() const {
		return this->item;
	}
}