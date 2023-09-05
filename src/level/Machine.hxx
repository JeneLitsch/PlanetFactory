#pragma once
#include "SFML/Graphics.hpp"
#include "stdxx/math.hxx"
#include "stdxx/reference.hxx"
#include "Item.hxx"

namespace level {
	class Machine {
	public:
		Machine(stx::position2i position);

		virtual void tick_pre() = 0;
		virtual void tick_main() = 0;
		virtual void tick_post() = 0;

		virtual void render(sf::RenderTarget & target) const = 0;

		virtual void link(stx::reference<Machine> input_machine) = 0;

		virtual stx::optref<const Item> take_output() = 0;

		stx::position2i get_position() const;

		virtual bool is_done() const = 0;

	private:
		stx::position2i position;
	};
}