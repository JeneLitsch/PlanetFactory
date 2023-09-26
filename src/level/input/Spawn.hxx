#pragma once
#include "Input.hxx"

namespace level {
	struct Spawn : public Input {
	public:
		Spawn(stx::reference<const Item> item);

		virtual void prepare() override;
		virtual bool fetch_suply() override;
		virtual stx::optref<const Item> peek() const override;
		virtual void clear() override;
		virtual void link(stx::reference<Output> suplier) override;
		virtual void unlink(stx::reference<Output> suplier) override;

	private:
		stx::reference<const Item> item;
		std::uint32_t counter = 0;
		std::uint32_t delay = 4;
	};
}