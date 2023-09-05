#pragma once
#include <vector>
#include "ItemSlot.hxx"

namespace level {
	class ItemStorage {
	public:
		void add_slot(ItemSlot slot);

		[[no_discard]] std::int32_t store(stx::reference<const Item> item, std::int32_t amount);
		[[no_discard]] std::int32_t retrieve(stx::reference<const Item> item, std::int32_t amount);

		[[no_discard]] std::int32_t get_amount(stx::reference<const Item> item) const;

		void print() const;
	private:
		std::vector<ItemSlot> slots;
	};
}