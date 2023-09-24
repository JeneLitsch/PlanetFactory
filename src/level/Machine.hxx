#pragma once
#include <memory>
#include "stdxx/reference.hxx"
#include "stdxx/math.hxx"
#include "stdxx/oop.hxx"
#include "input/Input.hxx"
#include "middle/Middle.hxx"
#include "output/Output.hxx"

namespace level {
	struct Machine;

	struct Machine {
		stx::position2i position;

		std::unique_ptr<Input> input;
		std::unique_ptr<Middle> middle;
		std::unique_ptr<Output> output;

		bool fetching_done;
		bool production_done;

		sf::Color color;

		void tick_pre();
		bool tick_main();
		void tick_post();
	};
}