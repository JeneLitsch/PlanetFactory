#pragma once
#include "Middle.hxx"

namespace level {
	struct Spawn : public Middle {
	public:
		Spawn(stx::reference<const Item> item) : item {item} {}

		virtual void prepare() override {
			++this->counter;
		}

		virtual std::tuple<bool, bool> produce(stx::optref<const Item> item) override {
			return {true,true};
		}

		virtual stx::optref<const Item> take() override {
			return (this->counter % this->delay == 0) ? stx::optref{*this->item} : stx::nullref;
		}

	private:
		stx::reference<const Item> item;
		std::uint32_t counter = 0;
		std::uint32_t delay = 4;
	};
}