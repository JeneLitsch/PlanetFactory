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
			for(std::unique_ptr<Machine> & m : *this->machines) {
				if(m->position == position + this->get_rotation()) {
					this->machines->back()->input->link(*m->output);
				}

				if(m->position + m->rotation == position) {
					m->input->link(*this->machines->back()->output);
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

		auto position_mini 
			= stx::position2f{position + this->get_rotation()}
			+ stx::position2f{0.25f};

		sf::RectangleShape mini_rect;
		mini_rect.setSize({0.5f,0.5f});
		mini_rect.setFillColor(sf::Color::Transparent);
		mini_rect.setOutlineColor(sf::Color::Blue);
		mini_rect.setOutlineThickness(-1.f/16.f);
		mini_rect.setPosition(position_mini.to<sf::Vector2f>());
		target.draw(mini_rect);
	}
}