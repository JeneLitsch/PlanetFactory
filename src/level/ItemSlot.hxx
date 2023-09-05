#pragma once
#include "stdxx/reference.hxx"
#include "Item.hxx"

namespace level {
	class ItemSlot {
	public:
		ItemSlot(stx::reference<const Item> item, std::int32_t capacity);
		void exchange(std::int32_t amount);

		std::int32_t get_amount() const;
		std::int32_t get_capacity() const;
		bool is_empty() const;
		bool is_full() const;

		stx::reference<const Item> get_item() const;
	private:
		stx::reference<const Item> item;
		std::int32_t capacity;
		std::int32_t amount;
	};
}