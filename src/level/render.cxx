#include "render.hxx"

namespace level {
	void render_tiles(const stx::grid2<stx::optref<const Tile>> & tiles, sf::RenderTarget & target) {
		sf::VertexArray vertex_array;
		vertex_array.setPrimitiveType(sf::Quads);
		for(std::size_t y = 0; y < tiles.size().y; ++y) {
			for(std::size_t x = 0; x < tiles.size().x; ++x) {
				const auto & tile = tiles(x,y);
				if(!tile) continue;
				const float x1 = static_cast<float>(x);
				const float y1 = static_cast<float>(y);
				const float x2 = x1 + 1.f;
				const float y2 = y1 + 1.f;

				const sf::Vertex nw {{x1, y1}, tile->color };
				const sf::Vertex ne {{x2, y1}, tile->color };
				const sf::Vertex se {{x2, y2}, tile->color };
				const sf::Vertex sw {{x1, y2}, tile->color };
				vertex_array.append(nw);
				vertex_array.append(ne);
				vertex_array.append(se);
				vertex_array.append(sw);
			}
		}
		target.draw(vertex_array);
	}



	void render_resources(
		const stx::grid2<stx::optref<const Item>> & resources,
		sf::RenderTarget & target) {

		sf::VertexArray vertex_array;
		vertex_array.setPrimitiveType(sf::Quads);
		for(std::size_t y = 0; y < resources.size().y; ++y) {
			for(std::size_t x = 0; x < resources.size().x; ++x) {
				const auto & item = resources(x,y);
				if(!item) continue;
				const float x1 = static_cast<float>(x) + 0.25f;
				const float y1 = static_cast<float>(y) + 0.25f;
				const float x2 = x1 + 0.5f;
				const float y2 = y1 + 0.5f;

				const sf::Vertex nw {{x1, y1}, item->color };
				const sf::Vertex ne {{x2, y1}, item->color };
				const sf::Vertex se {{x2, y2}, item->color };
				const sf::Vertex sw {{x1, y2}, item->color };
				vertex_array.append(nw);
				vertex_array.append(ne);
				vertex_array.append(se);
				vertex_array.append(sw);
			}
		}
		target.draw(vertex_array);
		
	}


	void render_machine(const Machine & machine, sf::RenderTarget & target, sf::Texture & sprite_sheet, unsigned frame) {
		sf::RectangleShape main_rect;

		main_rect.setOrigin({0.5,0.5});

		if(machine.rotation == stx::position2i{1,0})   main_rect.setRotation(90);
		if(machine.rotation == stx::position2i{-1, 0}) main_rect.setRotation(270);
		if(machine.rotation == stx::position2i{0, 1}) main_rect.setRotation(180);

		main_rect.setSize({1,1});
		main_rect.setPosition(machine.position.x + 0.5, machine.position.y + 0.5);
		main_rect.setTexture(&sprite_sheet);
		main_rect.setTextureRect({(machine.texture_position.x + static_cast<int>(frame)) * 16, (machine.texture_position.y) * 16, 16,16});
		target.draw(main_rect);

		machine.output->render(machine.position, target);
	}
}