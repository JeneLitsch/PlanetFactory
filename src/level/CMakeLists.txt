cmake_minimum_required (VERSION 3.8)

add_library(level
	Level.cxx
	render.cxx
	Item.cxx
	ItemStack.cxx
	create.cxx
	Machine.cxx
	ItemStorage.cxx
)

add_subdirectory(input)
add_subdirectory(middle)
add_subdirectory(output)
add_subdirectory(tool)