#pragma once
#include "stdxx/reference.hxx"
#include "stdxx/math.hxx"
#include "stdxx/oop.hxx"
#include "level/Item.hxx"

namespace level {
	struct Output;

	struct Input : stx::non_copyable {
		~Input() = default;

		virtual void prepare() = 0;

		virtual stx::optref<const Item> peek_suplier() const = 0;
		virtual void clear_suplier() = 0;

		virtual void store(stx::optref<const Item> item) = 0;

		virtual stx::optref<const Item> peek() const = 0;
		virtual void clear() = 0;

		virtual void link(stx::reference<Output> suplier) = 0;
		virtual void unlink(stx::reference<Output> suplier) = 0;
	};
}