#pragma once
#include <memory>
#include "stdxx/reference.hxx"
#include "stdxx/math.hxx"
#include "stdxx/oop.hxx"
#include "level/Item.hxx"
#include "SFML/Graphics.hpp"

namespace level {
	struct Input;
	struct Output : stx::non_copyable {
		~Output() = default;

		virtual void prepare() = 0;

		virtual void store(stx::optref<const Item> item) = 0;

		virtual bool is_clear() const = 0;
		virtual stx::optref<const Item> peek() const = 0;
		virtual void clear() = 0;
		
		virtual void back_link(stx::reference<Input> succesor_input) = 0;

		virtual void render(stx::position2i position, sf::RenderTarget & target) = 0;
	};
}