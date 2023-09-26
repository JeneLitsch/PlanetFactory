#pragma once
#include "Input.hxx"

namespace level {
	class SimpleInput : public Input {
	public:
		virtual ~SimpleInput();

		virtual void prepare() override;
		virtual bool fetch_suply() override;
		virtual stx::optref<const Item> peek() const override;
		virtual void clear() override;
		virtual void link(stx::reference<Output> suplier) override;
		virtual void unlink(stx::reference<Output> suplier) override;

	private:
		stx::optref<const Item> item;
		std::vector<stx::reference<Output>> ports;
		std::size_t index = 0;
	};
}