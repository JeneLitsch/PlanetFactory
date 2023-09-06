#pragma once
#include "Machine.hxx"
#include "level/ItemSlot.hxx"

namespace level {
	class Stockpile : public Machine {
	public:
		Stockpile(stx::position2i position);

		virtual void tick_pre() override;
		virtual void tick_post() override;

		virtual void fetch() override;
		virtual void produce() override;

		virtual void render(sf::RenderTarget & target) const override;

		virtual void link(stx::reference<Machine> input_machine) override;

		virtual stx::optref<const Item> peek_output() const override;
		virtual void clear_output() override;

		virtual bool is_done() const override;		
	private:

		stx::optref<const Item> input_item;
		stx::optref<const Item> temp_item;
		ItemSlot storage;



		std::vector<stx::reference<Machine>> input_ports;
		std::size_t input_index = 0;
	};
}