#include "Item.hxx"

namespace level {
	void render_item(const Item & item, stx::position2f xy, sf::RenderTarget & target) {
		sf::VertexArray vertex_array;
		vertex_array.setPrimitiveType(sf::Quads);
		const float x0 = xy.x;
		const float y0 = xy.y;
		const float x1 = x0 + 0.25f;
		const float y1 = y0 + 0.25f;
		const float x2 = x0 + 0.75f;
		const float y2 = y0 + 0.75f;

		const sf::Vertex nw {{x1, y1}, item.color};
		const sf::Vertex ne {{x2, y1}, item.color};
		const sf::Vertex se {{x2, y2}, item.color};
		const sf::Vertex sw {{x1, y2}, item.color};
		vertex_array.append(nw);
		vertex_array.append(ne);
		vertex_array.append(se);
		vertex_array.append(sw);
		target.draw(vertex_array);
	}
}