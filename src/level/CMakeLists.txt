cmake_minimum_required (VERSION 3.8)

add_library(level
	Level.cxx
	render.cxx
	Item.cxx
	ItemStack.cxx
	create.cxx
	tick_pre.cxx
	tick_post.cxx
	tick.cxx
	ItemStorage.cxx
)