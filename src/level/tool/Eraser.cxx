#include "Eraser.hxx"
#include <algorithm>

namespace level {
	Eraser::Eraser(stx::reference<std::vector<std::unique_ptr<Machine>>> machines) 
		: machines{machines} {}
	


	void Eraser::apply(stx::position2i position) {
		std::erase_if(*this->machines, [&] (const auto & machine) {
			return machine->position == position;
		});
	}



	void Eraser::render(stx::position2i position, sf::RenderTarget & target) {
		sf::RectangleShape rect;
		rect.setSize({1.f,1.f});
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Red);
		rect.setOutlineThickness(-1.f/16.f);
		rect.setPosition(position.x, position.y);
		target.draw(rect);
	}
}