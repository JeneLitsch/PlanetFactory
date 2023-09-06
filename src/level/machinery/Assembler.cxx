#include "Assembler.hxx"

namespace level {
	Assembler::Assembler(
		stx::position2i position, stx::reference<const Recipe> recipe) 
		: Machine{position}
		, recipe{recipe} {

		for(const auto & from : recipe->from) {
			this->input_items.add_slot(ItemSlot{from, 1});
		}
	}



	void Assembler::tick_pre() {
		this->fetching_done = false;
		this->production_done = false;
		this->input_index = (this->input_index + 1) % std::size(this->input_ports); 
	}



	void Assembler::tick_main() {
		if(!this->fetching_done) {
			this->fetch();
		} 

		if(!this->production_done) {
			this->produce();
		} 
	}



	void Assembler::fetch() {
		if(!std::empty(this->input_ports) && !this->output_item) {
			auto & input = *this->input_ports[this->input_index];
			if(auto item = input.peek_output()) {
				if(input_items.store(*item, 1) == 0) {
					input.clear_output();
				}
				this->fetching_done = true;
			}
		}
	}



	bool Assembler::verify_recipe() const {
		for(const auto & from : this->recipe->from) {
			if(this->input_items.get_amount(from) == 0) {
				return false;
			}
		}
		return true;
	}



	void Assembler::produce() {
		if(!this->temp_item) {
			if(this->verify_recipe()) {
				this->temp_item = *this->recipe->to;
				for(const auto & needed : this->recipe->from) {
					this->input_items.retrieve(*needed, 1);
				}
				this->production_done = true;
			}
		}
	}



	void Assembler::tick_post() {
		if(this->temp_item && !this->output_item) {
			this->output_item = this->temp_item;
		}
		this->temp_item = stx::nullref;

	}

	

	void Assembler::render(sf::RenderTarget & target) const {
		sf::RectangleShape main_rect;
		main_rect.setSize({1,1});
		main_rect.setFillColor(sf::Color{200,200,200}),
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



	void Assembler::link(stx::reference<Machine> input_machine)  {
		this->input_ports.push_back(input_machine);
	}



	stx::optref<const Item> Assembler::peek_output() const {
		return this->output_item;
	}



	void Assembler::clear_output() {
		this->output_item = stx::nullref;
	}




	bool Assembler::is_done() const {
		return this->fetching_done && this->production_done;
	}
}