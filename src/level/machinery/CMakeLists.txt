cmake_minimum_required (VERSION 3.13)

target_sources(level PRIVATE
	Conveyor.cxx
	Machine.cxx
	Assembler.cxx
	Source.cxx
	Stockpile.cxx
)

add_subdirectory(comp)