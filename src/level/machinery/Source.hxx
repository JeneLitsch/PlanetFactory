#pragma once
#include "Machine.hxx"

namespace level {
	class Source : public Machine {
	public:
		Source(stx::position2i position, stx::reference<const Item> produced_item);

		virtual void tick_pre() override;
		virtual void tick_main() override;
		virtual void tick_post() override;

		virtual void render(sf::RenderTarget & target) const override;

		virtual void link(stx::reference<Machine> input_machine) override;

		virtual stx::optref<const Item> peek_output() const override;
		virtual void clear_output() override;

		virtual bool is_done() const override;		
	private:
		stx::optref<const Item> produced_item;
		stx::optref<const Item> output_item;

		bool fetching_done = false;
		bool production_done = false;
	};
}