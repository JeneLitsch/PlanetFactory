#include "ItemSlot.hxx"

namespace level {
	ItemSlot::ItemSlot(stx::reference<const Item> item, std::int32_t capacity)
		: item {item}
		, capacity{capacity}
		, amount{0} {}



	void ItemSlot::exchange(std::int32_t amount) {
		this->amount += amount;
	}



	std::int32_t ItemSlot::get_amount() const {
		return this->amount;
	}



	std::int32_t ItemSlot::get_capacity() const {
		return this->capacity;
	}



	bool ItemSlot::is_empty() const {

	}



	bool ItemSlot::is_full() const {

	}



	stx::reference<const Item> ItemSlot::get_item() const {
		return this->item;
	}
}