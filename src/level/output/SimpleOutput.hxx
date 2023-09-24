#pragma once
#include "Output.hxx"

namespace level {
	class SimpleOutput : public Output {
	public:
		virtual void prepare() override {

		}

		virtual void store(stx::optref<const Item> item) override {
			this->item = item;
		}

		virtual bool is_clear() const override {
			return !this->item;
		}

		virtual stx::optref<const Item> peek() const override {
			return this->item;
		}

		virtual void clear() override {
			this->item = stx::nullref;
		}
		
		virtual void back_link(stx::reference<Input> succesor_input) override {

		}

		virtual void render(stx::position2i position, sf::RenderTarget & target) override {
			if(this->item) {
				sf::RectangleShape item_rect;
				item_rect.setSize({0.5,0.5});
				item_rect.setFillColor(this->item->color),
				item_rect.setPosition(position.x + 0.25, position.y + 0.25);
				target.draw(item_rect);
			}
		}
	private:
		stx::optref<const Item> item;
	};
}