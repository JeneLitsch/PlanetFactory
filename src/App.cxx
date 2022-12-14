#include "App.hxx"
#include "level/Level.hxx"
#include <iostream>

sf::FloatRect calc_view_port(
	const sf::Window & window,
	const sf::View & view){

	const float aspect_ratio_window 
		= float(window.getSize().x)
		/ float(window.getSize().y);

	const float aspect_ratio_buffer 
		= float(view.getSize().x)
		/ float(view.getSize().y);

	if(aspect_ratio_buffer > aspect_ratio_window){
		const float relative_height = aspect_ratio_window/aspect_ratio_buffer;
		const float offset = (1.f - relative_height) / 2.f;
		return sf::FloatRect(0.f, offset, 1.f, relative_height);
	}
	else{
		const float relative_width = aspect_ratio_buffer/aspect_ratio_window;
		const float offset = (1.f - relative_width) / 2.f;
		return sf::FloatRect(offset, 0.f, relative_width, 1.f);
	}
}



App::App() {
	this->window.create(sf::VideoMode{256,256}, "Creature Simulator");
	this->state_manager.push(std::make_unique<level::Level>(stx::size2u{32,32}, 42));
}





void App::run() {
	std::size_t i = 0;
	while (this->window.isOpen()) {
		this->state_manager.handle_queue();
		while (auto event = core::fetch_event(this->window)) {
			std::visit([this] (const auto & e) { this->on_event(e); }, *event);
			this->state_manager.events(*event);
		}

		const double dt = clock(); 

		// std::cout << 1.f / (this->now - this->then).asSeconds() << "\n";
		this->state_manager.update(dt);
		this->window.clear(sf::Color::Black);
		this->state_manager.render(this->window);

		this->window.display();
		// ++i;
		// if(i > 10) return;
	}
}



void App::on_event(const core::Closed &) {
	this->window.close();
}



void App::on_event(const core::WindowResized & event) {
	sf::View view;
	view.setSize(32,32);
	view.setCenter(16,16);
	view.setViewport(calc_view_port(this->window, view));
	this->window.setView(view);
}
