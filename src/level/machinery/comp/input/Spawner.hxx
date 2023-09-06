#pragma once
#include "stdxx/reference.hxx"
#include "level/Item.hxx"

namespace level {
	class Machine;
	class Spawner {
	public:
		Spawner(stx::reference<const Item>  to_be_produced);
		void link(stx::reference<Machine> machine);
		
		bool is_ready() const;
		stx::optref<const Item> pull();
		
		void prepare();
		bool process();
	private:
		stx::reference<const Item> to_be_produced;
		stx::optref<const Item> item;

		std::uint32_t counter = 0;
	};
}