#include "Conveyor.hxx"

namespace level {
	Conveyor::Conveyor(stx::position2i position) 
		: Machine{position} {}



	void Conveyor::tick_pre() {
		this->input.prepare();
		this->middle.prepare();
		this->output.prepare();
		
		this->fetching_done = false;
		this->production_done = false;
	}



	void Conveyor::fetch() {
		if(this->output.is_clear() && this->input.process()) {
			this->fetching_done = true;
		}
	}



	void Conveyor::produce() {
		if(this->input.is_ready() && this->middle.is_clear()) {
			this->middle.push(this->input.pull());
			if(this->middle.process()) {
				this->production_done = true;
			}
		}
	}



	void Conveyor::tick_post() {
		if(this->middle.is_ready() && this->output.is_clear()) {
			this->output.push(this->middle.pull());
			this->output.process();
		}
	}

	

	void Conveyor::render(sf::RenderTarget & target) const {
		sf::RectangleShape main_rect;
		main_rect.setSize({1,1});
		main_rect.setFillColor(sf::Color{64,64,64}),
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



	void Conveyor::link(stx::reference<Machine> input_machine)  {
		this->input.link(input_machine);
	}



	stx::optref<const Item> Conveyor::peek_output() const {
		return this->output.get();
	}



	void Conveyor::clear_output() {
		this->output.discard();
	}



	bool Conveyor::is_done() const {
		return this->fetching_done && this->production_done;
	}
}