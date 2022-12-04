#include "transfer.hxx"
#include <unordered_set>

namespace level {
	void item_transfer(Machine & machine, MachineEcs & machines) {
		// std::cout << "TRANSFER\n";
		auto * connects = machine.get_if<Connects>();
		auto * storage = machine.get_if<Storage>();

		// No connection
		if(!connects) return;

		// Expired/non-existing machine
		auto * connected_machine =  machines.get_if(connects->machine_id);
		if(!connected_machine) return;

		// No storage
		if(!storage) return;
		
		// Has storage
		if(!storage->item) return;

		// Connected machine has no storage
		auto * connected_storage = connected_machine->get_if<Storage>();
		if(!connected_storage) return;

		// Connected is full
		if(connected_storage->item) return;

		connected_storage->item = storage->item;
		storage->item = stx::nullref;
	}



	std::vector<std::uint64_t> determine_transfer_order(const MachineEcs & machines) {
		std::vector<std::uint64_t> order;
		std::unordered_set<std::uint64_t> visited;

		// End pieces
		machines.run_system([&] (const Machine & machine) {
			if(!machine.has<Connects>()) {
				order.push_back(machine.get_id());
				visited.insert(machine.get_id());
			}
		});

		while(true) {
			bool changed = false;
			machines.run_system([&] (const Machine & machine) {
				auto * connects_to = machine.get_if<Connects>();
				if(!connects_to) return;
				if(!visited.contains(connects_to->machine_id)) return;
				if(visited.contains(machine.get_id())) return;
				order.push_back(machine.get_id());
				visited.insert(machine.get_id());
				changed = true;
			});
			if(!changed) break;
		}

		return order;
	}
}