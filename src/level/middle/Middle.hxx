#pragma once
#include <memory>
#include "stdxx/reference.hxx"
#include "stdxx/math.hxx"
#include "stdxx/oop.hxx"
#include "level/Item.hxx"

namespace level {
	struct Middle : stx::non_copyable {
		~Middle() = default;

		virtual void prepare() = 0;

		virtual std::tuple<bool, bool> produce(stx::optref<const Item> item) = 0;

		virtual stx::optref<const Item> take() = 0;
	};
}