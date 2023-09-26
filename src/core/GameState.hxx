#pragma once
#include "Event.hxx"

namespace core {
	class StateManager;
	class GameState {
	public:
		void link(StateManager & state_manager);

		void events(const Event & event);
		virtual void update(double dt) = 0;
		virtual void render(sf::RenderTarget & render_target) = 0;

		virtual ~GameState() = default;
	protected:
		virtual void init() = 0;

		void push(std::unique_ptr<GameState> state);
		void pop();
		
		virtual void on_event(const Closed &) {}
		virtual void on_event(const WindowResized &) {}
		virtual void on_event(const KeyPressed &) {}
		virtual void on_event(const MouseMoved &) {}
		virtual void on_event(const MouseButtonPressed &) {}
		virtual void on_event(const MouseScrolled &) {}
	private:

		StateManager * state_manager = nullptr;
	};
}