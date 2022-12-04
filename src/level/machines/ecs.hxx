#pragma once
#include "nanocomp/nanocomp.hpp"
#include "components.hxx"

namespace level {
	using MachineEcs = nc::Ecs<
		Location,
		Storage,
		Sprite,
		Connects,
		Source,
		Sink,
		Recipe
	>;

	using Machine = MachineEcs::Entity;
}