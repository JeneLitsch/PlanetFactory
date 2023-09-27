#include "Place.hxx"
#include <algorithm>
#include "level/create.hxx"

namespace level {
	Place::Place(stx::reference<std::vector<std::unique_ptr<Machine>>> machines) 
		: machines{machines} {}
	


	void Place::apply(stx::position2i position) {
		auto begin = std::begin(*this->machines);
		auto end = std::end(*this->machines);
		auto pred = [&] (const auto & machine) {
			return machine->position == position;
		};
		if(std::none_of(begin, end, pred)) {
			this->machines->push_back(create_conveyor(position, this->get_rotation()));
			auto & new_machine = this->machines->back();
			for(std::unique_ptr<Machine> & m : *this->machines) {
				const auto own_input = new_machine->position + new_machine->rotation; 
				const auto own_ouput = new_machine->position - new_machine->rotation;
				const auto other_input = m->position + m->rotation;
				const auto other_ouput = m->position - m->rotation;

				if(m->position == own_input) {
					link_machines(*m, *new_machine);
				}
				
				if(m->position == own_ouput) {
					link_machines(*new_machine, *m);
				}

				if(other_ouput == position) {
					link_machines(*m, *new_machine);
				}

				if(other_input == position) {
					link_machines(*new_machine, *m);
				}

			}
		}
	}



	void Place::render(stx::position2i position, sf::RenderTarget & target) {
		sf::RectangleShape rect;
		rect.setSize({1.f,1.f});
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Blue);
		rect.setOutlineThickness(-1.f/16.f);
		rect.setPosition(position.x, position.y);
		target.draw(rect);

		auto position_input 
			= stx::position2f{position + this->get_rotation()}
			+ stx::position2f{0.25f};

		sf::RectangleShape input_rect;
		input_rect.setSize({0.5f,0.5f});
		input_rect.setFillColor(sf::Color::Red);
		input_rect.setOutlineColor(sf::Color::Blue);
		input_rect.setOutlineThickness(-1.f/16.f);
		input_rect.setPosition(position_input.to<sf::Vector2f>());
		target.draw(input_rect);

		auto position_output 
			= stx::position2f{position - this->get_rotation()}
			+ stx::position2f{0.25f};

		sf::RectangleShape ouput_rect;
		ouput_rect.setSize({0.5f,0.5f});
		ouput_rect.setFillColor(sf::Color::Green);
		ouput_rect.setOutlineColor(sf::Color::Blue);
		ouput_rect.setOutlineThickness(-1.f/16.f);
		ouput_rect.setPosition(position_output .to<sf::Vector2f>());
		target.draw(ouput_rect);
	}
}