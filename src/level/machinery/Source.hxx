#pragma once
#include "Machine.hxx"
#include "comp/input/Spawner.hxx"
#include "comp/middle/PassThrough.hxx"
#include "comp/output/SimpleOutput.hxx"

namespace level {
	class Source : public Machine {
	public:
		Source(stx::position2i position, stx::reference<const Item> produced_item);

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
		Spawner input;
		PassThrough middle;
		SimpleOutput output;
	};
}