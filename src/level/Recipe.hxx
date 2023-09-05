#pragma once
#include "stdxx/reference.hxx"
#include "Item.hxx"

namespace level {
	struct Recipe {
		std::vector<stx::reference<const Item>> from;
		stx::reference<const Item> to;
	};
}