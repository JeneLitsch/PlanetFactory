#pragma once
#include "stdxx/reference.hxx"
#include "level/Recipe.hxx"
#include "level/ItemStorage.hxx"
#include "level/ItemStorage.hxx"

namespace level {
	class RecipeBuilder {
	public:
		RecipeBuilder(stx::reference<const Recipe> recipe);

		bool push(stx::reference<const Item> item);
		bool process();
		stx::optref<const Item> pull();

	private:
		bool verify_recipe() const;
		
		stx::reference<const Recipe> recipe;
		ItemStorage materials;
		stx::optref<const Item> product;
	};
}