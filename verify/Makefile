template = ../misc/template.cpp
datastructures = \
		 aoj1351.cpp koj0093.cpp \
		 aojdsl2a.cpp aojdsl2b.cpp
aojcgls = \
	  aoj1279.cpp \
	  aoj2402.cpp aoj2448.cpp
strings = \
	  disco2016qualc.cpp
math = \
	   atc001c.cpp
dsts = $(aojcgls) $(datastructures) $(strings) $(math)

.PHONY: all
all:	$(dsts)

%.cpp:	src/%.cpp $(template)
	cat $(template) > $@
	g++ -E src/$@ >> $@
	g++ -std=c++11 -fsyntax-only $@

.PHONY:	clean
clean:
	rm -f $(dsts)
