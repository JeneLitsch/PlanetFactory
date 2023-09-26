#include "StorageOutput.hxx"

namespace level {
	void StorageOutput::prepare() {

	}



	void StorageOutput::store(stx::optref<const Item> item) {
		if(this->stack.is_empty()) {
			this->stack = ItemStack{*item, 5};
		}
		if(!this->stack.is_full() && this->stack.get_item() == *item) {
			this->stack.store(1);
		}
	}



	bool StorageOutput::is_clear() const {
		return !this->stack.is_full() || this->stack.is_empty();
	}



	stx::optref<const Item> StorageOutput::peek() const {
		if(!this->stack.is_empty()) {
			return this->stack.get_item();
		} 
		else return stx::nullref;
	}



	void StorageOutput::clear() {
		stack.retrieve(1);
	}
	


	void StorageOutput::render(stx::position2i position, sf::RenderTarget & target) {
		for(std::int32_t i = 0; i < this->stack.get_amount(); i++) {
			sf::RectangleShape item_rect;
			item_rect.setSize({0.5,0.1});
			item_rect.setFillColor(this->stack.get_item()->color),
			item_rect.setPosition(position.x + 0.25, position.y + 0.25 + 0.1 * i);
			target.draw(item_rect);
		}
	}
}