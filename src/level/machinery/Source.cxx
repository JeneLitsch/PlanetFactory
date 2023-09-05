#include "Source.hxx"

namespace level {
	Source::Source(stx::position2i position, stx::reference<const Item> produced_item) 
		: Machine{position}
		, produced_item{*produced_item} {}



	void Source::tick_pre() {
		this->fetching_done = false;
		this->production_done = false;
	}



	void Source::tick_main() {
	}



	void Source::tick_post() {
		this->output_item = this->produced_item;
	}

	

	void Source::render(sf::RenderTarget & target) const {
		sf::RectangleShape main_rect;
		main_rect.setSize({1,1});
		main_rect.setFillColor(sf::Color::White),
		main_rect.setPosition(this->get_position().x, this->get_position().y);
		target.draw(main_rect);

		if(this->output_item) {
			sf::RectangleShape item_rect;
			item_rect.setSize({0.5,0.5});
			item_rect.setFillColor(this->output_item->color),
			item_rect.setPosition(this->get_position().x + 0.25, this->get_position().y + 0.25);
			target.draw(item_rect);
		}
	}



	void Source::link(stx::reference<Machine> input_machine)  {}




	stx::optref<const Item> Source::peek_output() const {
		return this->output_item;
	}



	void Source::clear_output() {
		this->output_item = stx::nullref;
	}



	bool Source::is_done() const {
		return true;
	}
}