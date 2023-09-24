#pragma once
#include "Middle.hxx"

namespace level {
	struct Pass : public Middle {
	public:
		virtual void prepare() {};

		virtual std::tuple<bool, bool> produce(stx::optref<const Item> item) override {
			if(item && !this->item) {
				this->item = item;
				return {true,true};
			}
			return {false,false};
		}

		virtual stx::optref<const Item> take() override {
			return std::exchange(this->item, stx::nullref);
		}
	private:
		stx::optref<const Item> item;
	};
}