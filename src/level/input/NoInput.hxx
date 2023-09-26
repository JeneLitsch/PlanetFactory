#pragma once
#include "Input.hxx"

namespace level {
	class NoInput : public Input {
	public:

		virtual void prepare() override;
		virtual stx::optref<const Item> peek_suplier() const override;
		virtual void clear_suplier() override;
		virtual void store(stx::optref<const Item> item) override;
		virtual stx::optref<const Item> peek() const override;
		virtual void clear() override;
		virtual void link(stx::reference<Output> suplier) override;
		virtual void unlink(stx::reference<Output> suplier) override;
	};
}