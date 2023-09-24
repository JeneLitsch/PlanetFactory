#pragma once
#include "Input.hxx"

namespace level {
	class SimpleInput : public Input {
	public:

		virtual void prepare() override {
			if(!std::empty(ports)) {
				this->index = (this->index + 1) % std::size(this->ports); 
			}
		}

		virtual stx::optref<const Item> peek_suplier() const override {
			if(std::empty(this->ports)) return stx::nullref;
			return this->ports[this->index]->peek();
		}

		virtual void clear_suplier() override {
			this->ports[this->index]->clear();
		}

		virtual void store(stx::optref<const Item> item) override {
			this->item = item;
		}

		virtual stx::optref<const Item> peek() const override {
			return this->item;
		}
		
		virtual void clear() override {
			this->item = stx::nullref;
		}

		virtual void link(stx::reference<Output> suplier) override {
			ports.push_back(suplier);
		}
		
		virtual void unlink(stx::reference<Output> suplier) override {
			throw std::runtime_error{""};
		}

	private:
		stx::optref<const Item> item;
		std::vector<stx::reference<Output>> ports;
		std::size_t index = 0;
		void * machinery;
	};
}