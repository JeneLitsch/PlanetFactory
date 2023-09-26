#pragma once
#include "Output.hxx"

namespace level {
	class SimpleOutput : public Output {
	public:
		virtual void prepare() override;
		virtual void store(stx::optref<const Item> item) override;
		virtual bool is_clear() const override;
		virtual stx::optref<const Item> peek() const override;
		virtual void clear() override;
		virtual void render(stx::position2i position, sf::RenderTarget & target) override;
	private:
		stx::optref<const Item> item;
	};
}