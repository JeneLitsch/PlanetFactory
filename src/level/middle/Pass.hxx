#pragma once
#include "Middle.hxx"

namespace level {
	struct Pass : public Middle {
	public:
		virtual void prepare();
		virtual std::tuple<bool, bool> produce(stx::optref<const Item> item) override;
		virtual stx::optref<const Item> take() override;

	private:
		stx::optref<const Item> item;
	};
}