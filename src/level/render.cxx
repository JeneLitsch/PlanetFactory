#include "render.hxx"

namespace level {
	void render_tiles(const stx::grid2<Tile> & tiles, sf::RenderTarget & target) {
		sf::VertexArray vertex_array;
		vertex_array.setPrimitiveType(sf::Quads);
		for(std::size_t y = 0; y < tiles.size().y; ++y) {
			for(std::size_t x = 0; x < tiles.size().x; ++x) {
				const auto & tile = tiles(x,y);
				const float x1 = static_cast<float>(x);
				const float y1 = static_cast<float>(y);
				const float x2 = x1 + 1.f;
				const float y2 = y1 + 1.f;

				const sf::Vertex nw {{x1, y1}, tile.type->color };
				const sf::Vertex ne {{x2, y1}, tile.type->color };
				const sf::Vertex se {{x2, y2}, tile.type->color };
				const sf::Vertex sw {{x1, y2}, tile.type->color };
				vertex_array.append(nw);
				vertex_array.append(ne);
				vertex_array.append(se);
				vertex_array.append(sw);
			}
		}
		target.draw(vertex_array);
	}



	void render_machine(const Machine & machine, sf::RenderTarget & target) {
		auto * transform = machine.get_if<Transform>();
		auto * output = machine.get_if<Output>();
		auto * sprite = machine.get_if<Sprite>();
		auto * storage = machine.get_if<Storage>();

		if(transform && sprite) {
			sf::RectangleShape main_rect;
			main_rect.setSize({1,1});
			main_rect.setFillColor(sprite->color),
			main_rect.setPosition(transform->position.x, transform->position.y);
			target.draw(main_rect);
		}

		if(transform && output && output->item) {
			sf::RectangleShape item_rect;
			item_rect.setSize({0.5,0.5});
			item_rect.setFillColor(output->item->color),
			item_rect.setPosition(transform->position.x + 0.25, transform->position.y + 0.25);
			target.draw(item_rect);
		}

		if(transform && storage) {
			for(std::int32_t i = 0; i < storage->stack.get_amount(); i++) {
				sf::RectangleShape item_rect;
				item_rect.setSize({0.5,0.1});
				item_rect.setFillColor(storage->stack.get_item()->color),
				item_rect.setPosition(transform->position.x + 0.25, transform->position.y + 0.25 + 0.1 * i);
				target.draw(item_rect);
			}
		}
	}
}