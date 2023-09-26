#pragma once
#include <vector>
#include "stdxx/reference.hxx"
#include "level/Machine.hxx"
#include "Tool.hxx"

namespace level {
	class Eraser : public Tool {
	public:
		Eraser(stx::reference<std::vector<std::unique_ptr<Machine>>> machines);
		virtual void apply(stx::position2i position) override;
		virtual void render(stx::position2i position, sf::RenderTarget & target) override;
	private:
		stx::reference<std::vector<std::unique_ptr<Machine>>> machines;
	};
}