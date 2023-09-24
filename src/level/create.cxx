#include "create.hxx"
#include "input/SimpleInput.hxx"

#include "middle/Pass.hxx"
#include "middle/Spawn.hxx"
#include "middle/Builder.hxx"

#include "output/SimpleOutput.hxx"
#include "output/StorageOutput.hxx"


namespace level {
	void link(Machine & machine, const std::vector<stx::reference<Machine>> & prev) {
		for(const auto & e : prev) {
			machine.input->link(*e->output);
		}
	}

	std::unique_ptr<Machine> create_conveyor(stx::position2i position, const std::vector<stx::reference<Machine>> & prev) {
		auto machine = std::make_unique<Machine>();

		machine->position = position;

		machine->color = sf::Color{64,64,64};

		machine->input = std::make_unique<SimpleInput>();
		machine->middle = std::make_unique<Pass>();
		machine->output = std::make_unique<SimpleOutput>();

		link(*machine, prev);

		return machine;
	}



	std::unique_ptr<Machine> create_source(stx::position2i position, stx::reference<const Item> item, std::uint32_t delay) {
		auto machine = std::make_unique<Machine>();

		machine->position = position;

		machine->color = sf::Color::White;

		machine->input = std::make_unique<SimpleInput>();
		machine->middle = std::make_unique<Spawn>(item);
		machine->output = std::make_unique<SimpleOutput>();

		return machine;
	}



	std::unique_ptr<Machine> create_assembler(stx::position2i position, const std::vector<stx::reference<Machine>> & prev, stx::reference<const Recipe> recipe) {
		auto machine = std::make_unique<Machine>();

		machine->position = position;

		machine->color = sf::Color::White;

		machine->input = std::make_unique<SimpleInput>();
		machine->middle = std::make_unique<Builder>(recipe);
		machine->output = std::make_unique<SimpleOutput>();

		link(*machine, prev);
		return machine;
	}



	std::unique_ptr<Machine> create_container(stx::position2i position, const std::vector<stx::reference<Machine>> & prev) {
		auto machine = std::make_unique<Machine>();

		machine->position = position;

		machine->color = sf::Color{64,64,64};

		machine->input = std::make_unique<SimpleInput>();
		machine->middle = std::make_unique<Pass>();
		machine->output = std::make_unique<StorageOutput>();

		link(*machine, prev);
		return machine;
	}
}