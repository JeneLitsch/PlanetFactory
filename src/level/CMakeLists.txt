cmake_minimum_required (VERSION 3.8)

add_library(level
	Level.cxx
	render.cxx
	Item.cxx
	machines/render.cxx
	machines/transfer.cxx
	machines/create.cxx
	machines/produce.cxx
)