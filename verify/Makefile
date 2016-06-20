template = ../misc/template.cpp
datastructure = koj0093.cpp
strings = disco2016qualc.cpp
math = atc001c.cpp
dsts = $(datastructures) $(strings) $(math)

.PHONY: all
all:	$(dsts)

%.cpp:	src/%.cpp $(template)
	cat $(template) > $@
	g++ -E src/$@ >> $@
	g++ -std=c++11 -fsyntax-only $@

.PHONY:	clean
clean:
	rm -f $(dsts)
