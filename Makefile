CXX = g++
CPPFLAGS = -std=c++98 -Wall -pedantic-errors -g -O0
##CXX = clang++
WARNINGS = -Wall -Wno-global-constructors #-Wno-weak-vtables -Wno-padded -Wno-reserved-id-macro -Wno-shadow -Wglobal-constructors
##CPPFLAGS = -std=c++98 -pedantic-errors -g -O0

all: tp0 clean

tp0: main.o cmdline.o
	$(CXX) $(CPPFLAGS) $(WARNINGS) $^ -o $@

cmdline.o: cmdline.cpp
	$(CXX) -c $(CPPFLAGS) $^ -o $@

main.o: main.cpp query.hpp sensors.hpp vector.hpp errors.hpp
	$(CXX) -c $(CPPFLAGS) $(WARNINGS) $< -o $@


clean :
	rm -f *.o



