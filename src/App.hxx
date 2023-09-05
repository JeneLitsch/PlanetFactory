#pragma once
#include "stdxx/chrono.hxx"
#include "SFML/Graphics.hpp"
#include "core/Event.hxx"
#include "core/StateManager.hxx"

class App {
public:
	App();
	void run();
private:
	void on_event(const core::Closed & event);
	void on_event(const core::WindowResized & event);
	void on_event(auto) {}
	sf::RenderWindow window;
	core::StateManager state_manager;
	stx::chrono::clock_d clock;
};