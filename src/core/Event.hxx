#pragma once
#include <variant>
#include <optional>
#include <SFML/Graphics.hpp>
#include "stdxx/vector.hxx"

namespace core {
	struct Closed {};
	struct WindowResized {
		stx::size2u size;
		sf::Window * window; 
	};
	struct KeyPressed {
        sf::Keyboard::Key code;    ///< Code of the key that has been pressed
        bool          alt;     ///< Is the Alt key pressed?
        bool          control; ///< Is the Control key pressed?
        bool          shift;   ///< Is the Shift key pressed?
        bool          system;  ///< Is the System key pressed?
    };

	struct MouseMoved {
		stx::vector2i position;
		sf::RenderWindow * window;
	};

	struct MouseButtonPressed {
		sf::Mouse::Button button;
	};

	struct MouseScrolled {
		sf::RenderWindow * window;
		stx::vector2i position;
		float value;
	};

	using Event = std::variant<
		Closed,
		WindowResized,
        KeyPressed,
		MouseMoved,
		MouseButtonPressed,
		MouseScrolled
	>;

	std::optional<Event> fetch_event(sf::RenderWindow & window);
}
