#pragma once
#include "stdxx/math.hxx"
#include "SFML/Graphics.hpp"

namespace level {
	class Tool {
	public:
		virtual ~Tool() = default;
		virtual void apply(stx::position2i position) = 0;
		virtual void render(stx::position2i position, sf::RenderTarget & target) = 0;

		void rotate_cw();
		void rotate_ccw();
		stx::position2i get_rotation() const;
	private:
		stx::position2i rotation {0, -1};
	};
}