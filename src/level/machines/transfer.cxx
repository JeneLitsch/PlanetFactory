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
		if(connects->machine_ids.empty()) return;
		const auto output = connects->next_output;
		Machine * connected_machine = machines.get_if(connects->machine_ids[output]);
		// std::cout << output << "\n";
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

		connects->next_output += 1;
		connects->next_output %= connects->machine_ids.size();
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
				bool connected_is_visited = true;
				for(const auto id : connects_to->machine_ids) {
					connected_is_visited &= visited.contains(id);
				}
				if(!connected_is_visited) return;
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