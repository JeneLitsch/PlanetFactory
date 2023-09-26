#pragma once
#include "Middle.hxx"
#include "level/Recipe.hxx"
#include "level/ItemStorage.hxx"

namespace level {
	class Builder : public Middle {
	public:
		Builder(stx::reference<const Recipe> recipe);
		virtual void prepare() override;
		virtual std::tuple<bool, bool> produce(stx::optref<const Item> item) override;
		virtual stx::optref<const Item> take() override;

	private:
		bool verify_recipe() const;

		stx::reference<const Recipe> recipe;
		ItemStorage materials;
		stx::optref<const Item> product;
	};
}