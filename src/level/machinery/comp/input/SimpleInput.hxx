#pragma once
#include "stdxx/reference.hxx"
#include "level/Item.hxx"

namespace level {
	class Machine;
	class SimpleInput {
	public:
		void link(stx::reference<Machine> machine);
		
		bool is_ready() const;
		stx::optref<const Item> pull();
		
		void prepare();
		bool process();
	
	private:
		stx::optref<const Item> item;
		std::vector<stx::reference<Machine>> input_ports;
		std::size_t input_index = 0;
	};
}