#pragma once
#include "Machine.hxx"
#include "comp/input/SimpleInput.hxx"
#include "comp/middle/PassThrough.hxx"
#include "comp/output/SimpleOutput.hxx"

namespace level {
	class Conveyor : public Machine {
	public:
		Conveyor(stx::position2i position);

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
		SimpleInput input;
		PassThrough middle;
		SimpleOutput output;
	};
}