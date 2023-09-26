#include "calc_viewport.hxx"

namespace core {
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
}