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
		Sink
	>;

	using Machine = MachineEcs::Entity;
}