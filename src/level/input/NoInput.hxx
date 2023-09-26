#pragma once
#include "Input.hxx"

namespace level {
	class NoInput : public Input {
	public:

		virtual void prepare() override;
		virtual bool fetch_suply() override;
		virtual stx::optref<const Item> peek() const override;
		virtual void clear() override;
		virtual void link(stx::reference<Output> suplier) override;
		virtual void unlink(stx::reference<Output> suplier) override;
	};
}