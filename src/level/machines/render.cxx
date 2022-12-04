#include "render.hxx"

namespace level {
	void render_machine(const Machine & machine, sf::RenderTarget & target) {
		auto * sprite = machine.get_if<Sprite>();
		auto * location = machine.get_if<Location>();
		auto * storage = machine.get_if<Storage>();
		
		if(sprite && location) {
			sf::VertexArray vertex_array;
			vertex_array.setPrimitiveType(sf::Quads);
			const float x1 = static_cast<float>(location->xy.x);
			const float y1 = static_cast<float>(location->xy.y);
			const float x2 = x1 + 1.f;
			const float y2 = y1 + 1.f;

			const sf::Vertex nw {{x1, y1}, sprite->color };
			const sf::Vertex ne {{x2, y1}, sprite->color };
			const sf::Vertex se {{x2, y2}, sprite->color };
			const sf::Vertex sw {{x1, y2}, sprite->color };
			vertex_array.append(nw);
			vertex_array.append(ne);
			vertex_array.append(se);
			vertex_array.append(sw);

			target.draw(vertex_array);
		}


		if(storage && storage->item && location) {
			render_item(*storage->item, stx::position2f{location->xy}, target);
		}
	}
}