#include "SimpleOutput.hxx"

namespace level {
	void SimpleOutput::prepare() {

	}

	
	
	void SimpleOutput::store(stx::optref<const Item> item) {
		this->item = item;
	}

	
	
	bool SimpleOutput::is_clear() const {
		return !this->item;
	}

	
	
	stx::optref<const Item> SimpleOutput::peek() const {
		return this->item;
	}

	
	
	void SimpleOutput::clear() {
		this->item = stx::nullref;
	}
	
	
	
	void SimpleOutput::back_link(stx::reference<Input> succesor_input) {

	}

	
	
	void SimpleOutput::render(stx::position2i position, sf::RenderTarget & target) {
		if(this->item) {
			sf::RectangleShape item_rect;
			item_rect.setSize({0.5,0.5});
			item_rect.setFillColor(this->item->color),
			item_rect.setPosition(position.x + 0.25, position.y + 0.25);
			target.draw(item_rect);
		}
	}
}