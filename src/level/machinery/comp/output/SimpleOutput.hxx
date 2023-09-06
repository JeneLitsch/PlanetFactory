#pragma once
#include "stdxx/reference.hxx"
#include "level/Item.hxx"

namespace level {
	class SimpleOutput {
	public:
		bool is_clear() const;
		void push(stx::optref<const Item> item);
		
		bool is_ready() const;
		stx::optref<const Item> get() const;
		void discard();

		void prepare();
		bool process();

	private:
		stx::optref<const Item> item;
	};
}