#include "Tool.hxx"


namespace level {
	void Tool::rotate_cw() {
		this->rotation = stx::rotate_90_cw(this->rotation);
	}



	void Tool::rotate_ccw() {
		this->rotation = stx::rotate_90_ccw(this->rotation);
	}



	stx::position2i Tool::get_rotation() const {
		return this->rotation;
	}
}