all: generic partial

generic: generic_template.cpp
	g++ $< -o $@

partial: partial_specialization.cpp
	g++ $< -o $@

