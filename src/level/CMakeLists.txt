cmake_minimum_required (VERSION 3.8)

add_library(level
	Level.cxx
	render.cxx
	Item.cxx
	ItemSlot.cxx
)

add_subdirectory(machinery)