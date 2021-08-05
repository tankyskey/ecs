test: main
	g++ -lSDL2 -lSDL2_image -pthread obj/*.o -o test -Og

main: main.cpp core
	g++ -c main.cpp -o obj/main.o -Og

core: core.hpp
	g++ -c core.cpp -o obj/core.o -Og


release: rel_main
	g++ -lSDL2 -lSDL2_image -pthread obj/*.o -o test -O3

rel_main: main.cpp
	g++ -c main.cpp -o obj/main.o -O3

clean:
	rm obj/*.o test
