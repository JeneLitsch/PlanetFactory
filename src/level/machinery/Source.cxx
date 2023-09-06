#include "Source.hxx"

namespace level {
	Source::Source(stx::position2i position, stx::reference<const Item> produced_item) 
		: Machine{position}
		, input{produced_item} {}



	void Source::tick_pre() {
		this->input.prepare();
		this->middle.prepare();
		this->output.prepare();
		
		this->fetching_done = false;
		this->production_done = false;
	}



	void Source::fetch() {
		if(this->output.is_clear() && this->input.process()) {
			this->fetching_done = true;
		}
	}



	void Source::produce() {
		if(this->input.is_ready() && this->middle.is_clear()) {
			this->middle.push(this->input.pull());
			if(this->middle.process()) {
				this->production_done = true;
			}
		}
	}



	void Source::tick_post() {
		if(this->middle.is_ready() && this->output.is_clear()) {
			this->output.push(this->middle.pull());
			this->output.process();
		}
	}

	

	void Source::render(sf::RenderTarget & target) const {
		sf::RectangleShape main_rect;
		main_rect.setSize({1,1});
		main_rect.setFillColor(sf::Color::White),
		main_rect.setPosition(this->get_position().x, this->get_position().y);
		target.draw(main_rect);

		if(this->output.is_ready()) {
			sf::RectangleShape item_rect;
			item_rect.setSize({0.5,0.5});
			item_rect.setFillColor(this->output.get()->color),
			item_rect.setPosition(this->get_position().x + 0.25, this->get_position().y + 0.25);
			target.draw(item_rect);
		}
	}



	void Source::link(stx::reference<Machine> input_machine)  {
		this->input.link(input_machine);
	}



	stx::optref<const Item> Source::peek_output() const {
		return this->output.get();
	}



	void Source::clear_output() {
		this->output.discard();
	}



	bool Source::is_done() const {
		return this->fetching_done && this->production_done;
	}
}