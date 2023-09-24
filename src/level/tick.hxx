#pragma once
#include "Machinery.hxx"

namespace level {
	void tick_pre(Machine & machine);
	bool tick_main(Machine & machine);
	void tick_post(Machine & machine);
}