CXX = g++
CPPFLAGS = -std=c++98 -Wall -pedantic-errors -g -O0
##CXX = clang++
WARNINGS = -Wall -Wno-global-constructors #-Wno-weak-vtables -Wno-padded -Wno-reserved-id-macro -Wno-shadow -Wglobal-constructors
##CPPFLAGS = -std=c++98 -pedantic-errors -g -O0

all: tp1_orig tp1_tree diff_data performance clean

diff_data: diff_data.o cmdline.o
	$(CXX) $(CPPFLAGS) $(WARNINGS) $^ -o $@

performance: performance.o cmdline.o
	$(CXX) $(CPPFLAGS) $(WARNINGS) $^ -o $@

tp1_tree: main2.o cmdline.o
	$(CXX) $(CPPFLAGS) $(WARNINGS) $^ -o $@

tp1_orig: main.o cmdline.o
	$(CXX) $(CPPFLAGS) $(WARNINGS) $^ -o $@

performance.o: performance.cpp segment_tree.hpp sensor_data.hpp utils.hpp
	$(CXX) -c $(CPPFLAGS) $< -o $@

cmdline.o: cmdline.cpp
	$(CXX) -c $(CPPFLAGS) $^ -o $@

diff_data.o: diff_data.cpp
	$(CXX) -c $(CPPFLAGS) $^ -o $@

main.o: main.cpp sensor_data.hpp query.hpp sensors.hpp vector.hpp errors.hpp
	$(CXX) -c $(CPPFLAGS) $(WARNINGS) $< -o $@

main2.o: main2.cpp sensor_data.hpp query_tree.hpp segment_tree.hpp utils.hpp sensors.hpp vector.hpp errors.hpp
	$(CXX) -c $(CPPFLAGS) $(WARNINGS) $< -o $@

clean :
	rm -f *.o



