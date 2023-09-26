#pragma once
#include "Middle.hxx"

namespace level {
	struct Spawn : public Middle {
	public:
		Spawn(stx::reference<const Item> item);

		virtual void prepare() override;
		virtual std::tuple<bool, bool> produce(stx::optref<const Item> item) override;
		virtual stx::optref<const Item> take() override;

	private:
		stx::reference<const Item> item;
		std::uint32_t counter = 0;
		std::uint32_t delay = 4;
	};
}