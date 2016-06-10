template = ../misc/template.cpp
aojcgls = \
	  aojcgl1a.cpp aojcgl1b.cpp aojcgl1c.cpp \
	  aojcgl2a.cpp aojcgl2b.cpp aojcgl2c.cpp aojcgl2d.cpp \
	  aojcgl3a.cpp aojcgl3b.cpp aojcgl3c.cpp \
	  aojcgl5a.cpp \
	  aojcgl7a.cpp aojcgl7d.cpp aojcgl7e.cpp aojcgl7g.cpp
dsts = $(aojcgls)

.PHONY: all
all:	$(dsts)

%.cpp:	src/%.cpp $(template)
	cat $(template) > $@
	g++ -E src/$@ >> $@
	g++ -std=c++11 -fsyntax-only $@

.PHONY:	clean
clean:
	rm -f $(dsts)
