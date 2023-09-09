#pragma once
#include <set>
#include "Machine.hxx"
#include "level/Recipe.hxx"
#include "level/ItemStack.hxx"
#include "level/ItemStorage.hxx"
#include "utils/RecipeBuilder.hxx"

namespace level {
	class Assembler : public Machine {
	public:
		Assembler(stx::position2i position, stx::reference<const Recipe> recipe);

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
		RecipeBuilder builder;

		stx::optref<const Item> output_item;

		std::vector<stx::reference<Machine>> input_ports;
		std::size_t input_index = 0;
	};
}