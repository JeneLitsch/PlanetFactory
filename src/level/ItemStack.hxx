#pragma once
#include "stdxx/reference.hxx"
#include "Item.hxx"

namespace level {
	class ItemStack {
	public:
		ItemStack();
		ItemStack(stx::reference<const Item> item, std::int32_t capacity);
		[[no_discard]] std::int32_t store(std::int32_t amount);
		[[no_discard]] std::int32_t retrieve(std::int32_t amount);

		std::int32_t get_amount() const;
		std::int32_t get_capacity() const;
		bool is_empty() const;
		bool is_full() const;

		stx::optref<const Item> get_item() const;
	private:
		stx::optref<const Item> item;
		std::int32_t capacity;
		std::int32_t amount;
	};
}