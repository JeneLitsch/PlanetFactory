#pragma once
#include "stdxx/reference.hxx"
#include "Machine.hxx"

namespace level {
	class Conveyor : public Machine {
	public:
		Conveyor(stx::position2i position);

		virtual void tick_pre() override;
		virtual void tick_main() override;
		virtual void tick_post() override;

		virtual void render(sf::RenderTarget & target) const override;

		virtual void link(stx::reference<Machine> input_machine) override;

		virtual stx::optref<const Item> peek_output() const override;
		virtual void clear_output() override;

		virtual bool is_done() const override;		
	private:
		void fetch();
		void produce();

		stx::optref<const Item> input_item;
		stx::optref<const Item> temp_item;
		stx::optref<const Item> output_item;

		bool fetching_done = false;
		bool production_done = false;

		std::vector<stx::reference<Machine>> input_ports;
		std::size_t input_index = 0;
	};
}