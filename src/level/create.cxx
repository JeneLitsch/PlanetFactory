#include "create.hxx"
#include "input/SimpleInput.hxx"
#include "input/NoInput.hxx"
#include "input/Spawn.hxx"

#include "middle/Pass.hxx"
#include "middle/Builder.hxx"

#include "output/SimpleOutput.hxx"
#include "output/StorageOutput.hxx"


namespace level {
	std::unique_ptr<Machine> create_conveyor(stx::position2i position, stx::position2i rotation) {
		auto machine = std::make_unique<Machine>();

		machine->position = position;
		machine->rotation = rotation;
		machine->texture_position = {0,0};

		machine->color = sf::Color{64,64,64};

		machine->input = std::make_unique<SimpleInput>();
		machine->middle = std::make_unique<Pass>();
		machine->output = std::make_unique<SimpleOutput>();

		return machine;
	}



	std::unique_ptr<Machine> create_source(stx::position2i position, stx::position2i rotation, stx::reference<const Item> item, std::uint32_t delay) {
		auto machine = std::make_unique<Machine>();

		machine->position = position;
		machine->rotation = rotation;
		machine->texture_position = {0,1};

		machine->color = sf::Color::White;

		machine->input = std::make_unique<Spawn>(item);
		machine->middle = std::make_unique<Pass>();
		machine->output = std::make_unique<SimpleOutput>();

		return machine;
	}



	std::unique_ptr<Machine> create_assembler(stx::position2i position, stx::position2i rotation, stx::reference<const Recipe> recipe) {
		auto machine = std::make_unique<Machine>();

		machine->position = position;
		machine->rotation = rotation;
		machine->texture_position = {0,3};

		machine->color = sf::Color::White;

		machine->input = std::make_unique<SimpleInput>();
		machine->middle = std::make_unique<Builder>(recipe);
		machine->output = std::make_unique<SimpleOutput>();

		return machine;
	}



	std::unique_ptr<Machine> create_container(stx::position2i position, stx::position2i rotation) {
		auto machine = std::make_unique<Machine>();

		machine->position = position;
		machine->rotation = rotation;
		machine->texture_position = {0,2};

		machine->color = sf::Color{64,64,64};

		machine->input = std::make_unique<SimpleInput>();
		machine->middle = std::make_unique<Pass>();
		machine->output = std::make_unique<StorageOutput>();

		return machine;
	}



	void link_machines(Machine & from, Machine & to) {
		to.input->link(*from.output);
	}
}