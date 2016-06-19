template = ../misc/template.cpp
datastructures = \
		 aoj1351.cpp koj0093.cpp \
		 aojdsl2a.cpp aojdsl2b.cpp
aojcgls = \
	  aojcgl1a.cpp aojcgl1b.cpp aojcgl1c.cpp \
	  aojcgl2a.cpp aojcgl2b.cpp aojcgl2c.cpp aojcgl2d.cpp \
	  aojcgl3a.cpp aojcgl3b.cpp aojcgl3c.cpp \
	  aojcgl4a.cpp \
	  aojcgl5a.cpp \
	  aojcgl7a.cpp aojcgl7d.cpp aojcgl7e.cpp aojcgl7g.cpp \
	  aoj1279.cpp \
	  aoj2402.cpp
aojgrl = \
		 aojgrl1a.cpp aojgrl1b.cpp \
		 aojgrl2a_k.cpp \
		 aojgrl3a.cpp aojgrl3b.cpp aojgrl3c.cpp \
		 aojgrl4b.cpp \
		 aojgrl5b.cpp
strings = \
	  disco2016qualc.cpp
math = \
	   atc001c.cpp
dsts = $(aojcgls) $(datastructures) $(strings) $(math) $(aojgrl)

.PHONY: all
all:	$(dsts)

%.cpp:	src/%.cpp $(template)
	cat $(template) > $@
	g++ -E src/$@ >> $@
	g++ -std=c++11 -fsyntax-only $@

.PHONY:	clean
clean:
	rm -f $(dsts)
