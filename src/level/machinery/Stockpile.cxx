#include "Stockpile.hxx"

namespace level {
	Stockpile::Stockpile(stx::position2i position) 
		: Machine{position} {}



	void Stockpile::tick_pre() {
		this->fetching_done = false;
		this->production_done = false;
		this->input_index = (this->input_index + 1) % std::size(this->input_ports); 
	}



	void Stockpile::tick_main() {
		if(!this->fetching_done) {
			this->fetch();
		} 

		if(!this->production_done) {
			this->produce();
		} 
	}



	void Stockpile::fetch() {
		if(!std::empty(this->input_ports) && (!this->storage.is_full() || this->storage.is_empty())) {
			if(auto item = this->input_ports[this->input_index]->take_output()) {
				this->input_item = item;
				this->fetching_done = true;
			}
		}
	}



	void Stockpile::produce() {
		if(this->input_item && !this->temp_item) {
			this->temp_item = this->input_item;
			this->input_item = stx::nullref;
			this->production_done = true;
		}
	}



	void Stockpile::tick_post() {
		if(this->temp_item) {
			if(this->storage.is_empty()) {
				this->storage = ItemSlot{*this->temp_item, 5};
			}
			if(!this->storage.is_full() && this->storage.get_item() == this->temp_item) {
				this->storage.store(1);
			}
		}
		this->temp_item = stx::nullref;
		std::cout << this->storage.get_amount() << "\n";
	}

	

	void Stockpile::render(sf::RenderTarget & target) const {
		sf::RectangleShape main_rect;
		main_rect.setSize({1,1});
		main_rect.setFillColor(sf::Color{32,32,32}),
		main_rect.setPosition(this->get_position().x, this->get_position().y);
		target.draw(main_rect);

		for(std::int32_t i = 0; i < this->storage.get_amount(); i++) {
			sf::RectangleShape item_rect;
			item_rect.setSize({0.5,0.1});
			item_rect.setFillColor(this->storage.get_item()->color),
			item_rect.setPosition(this->get_position().x + 0.25, this->get_position().y + 0.25 + 0.1 * i);
			target.draw(item_rect);
		}
	}



	void Stockpile::link(stx::reference<Machine> input_machine)  {
		this->input_ports.push_back(input_machine);
	}



	stx::optref<const Item> Stockpile::peek_output() const {
		if(this->storage.is_empty()) {
			return stx::nullref;
		} 
		else {
			return this->storage.get_item();
		}
	}



	void Stockpile::clear_output() {
		this->storage.retrieve(1);
	}



	bool Stockpile::is_done() const {
		return this->fetching_done && this->production_done;
	}
}