#pragma once
#include <memory>
#include <set>
#include "stdxx/reference.hxx"
#include "stdxx/math.hxx"
#include "stdxx/oop.hxx"
#include "level/Item.hxx"
#include "SFML/Graphics.hpp"

namespace level {
	struct Input;
	struct Output : stx::non_copyable {
		virtual ~Output();

		virtual void prepare() = 0;

		virtual void store(stx::optref<const Item> item) = 0;

		virtual bool is_clear() const = 0;
		virtual stx::optref<const Item> peek() const = 0;
		virtual void clear() = 0;
		
		void back_link(stx::reference<Input> succesor_input);
		void unlink(stx::reference<Input> succesor_input);

		virtual void render(stx::position2i position, sf::RenderTarget & target) = 0;

	private:
		std::set<stx::reference<Input>> connected_inputs;
	};
}