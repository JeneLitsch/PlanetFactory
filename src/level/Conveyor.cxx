#include "Conveyor.hxx"

namespace level {
	Conveyor::Conveyor(stx::position2i position) 
		: Machine{position} {}



	void Conveyor::tick_pre() {
		this->fetching_done = false;
		this->production_done = false;
		this->input_index = (this->input_index + 1) % std::size(this->input_ports); 
	}



	void Conveyor::tick_main() {
		if(!this->fetching_done) {
			this->fetch();
		} 

		if(!this->production_done) {
			this->produce();
		} 
	}



	void Conveyor::fetch() {
		if(!std::empty(this->input_ports) && !this->output_item) {
			if(auto item = this->input_ports[this->input_index]->take_output()) {
				this->input_item = item;
				this->fetching_done = true;
			}
		}
	}



	void Conveyor::produce() {
		if(this->input_item && !this->temp_item) {
			this->temp_item = this->input_item;
			this->input_item = stx::nullref;
			this->production_done = true;
		}
	}



	void Conveyor::tick_post() {
		if(this->temp_item && !this->output_item) {
			this->output_item = this->temp_item;
		}
		this->temp_item = stx::nullref;
	}

	

	void Conveyor::render(sf::RenderTarget & target) const {
		sf::RectangleShape main_rect;
		main_rect.setSize({1,1});
		main_rect.setFillColor(sf::Color{64,64,64}),
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



	void Conveyor::link(stx::reference<Machine> input_machine)  {
		this->input_ports.push_back(input_machine);
	}



	stx::optref<const Item> Conveyor::take_output() {
		return std::exchange(this->output_item, stx::nullref);
	}



	bool Conveyor::is_done() const {
		return this->fetching_done && this->production_done;
	}
}