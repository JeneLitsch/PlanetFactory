#pragma once
#include "Output.hxx"
#include "level/ItemStack.hxx"

namespace level {
	class StorageOutput : public Output {
	public:
		virtual void prepare() override {

		}

		virtual void store(stx::optref<const Item> item) override {
			if(this->stack.is_empty()) {
				this->stack = ItemStack{*item, 5};
			}
			if(!this->stack.is_full() && this->stack.get_item() == *item) {
				this->stack.store(1);
			}
		}

		virtual bool is_clear() const override {
			return !this->stack.is_full() || this->stack.is_empty();
		}

		virtual stx::optref<const Item> peek() const override {
			if(!this->stack.is_empty()) {
				return this->stack.get_item();
			} 
			else return stx::nullref;
		}

		virtual void clear() override {
			stack.retrieve(1);
		}
		
		virtual void back_link(stx::reference<Input> succesor_input) override {

		}

		virtual void render(stx::position2i position, sf::RenderTarget & target) override {
			for(std::int32_t i = 0; i < this->stack.get_amount(); i++) {
				sf::RectangleShape item_rect;
				item_rect.setSize({0.5,0.1});
				item_rect.setFillColor(this->stack.get_item()->color),
				item_rect.setPosition(position.x + 0.25, position.y + 0.25 + 0.1 * i);
				target.draw(item_rect);
			}
		}
	private:
		ItemStack stack;
	};
}