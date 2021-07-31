test: system manager main
	g++ obj/*.o -o test

main: main.cpp
	g++ -c main.cpp -o obj/main.o

system: system/*.hpp
	g++ -c system/*.hpp -o obj/$(patsubst .hpp, .o, $^)

manager: manager/*.hpp
	g++ -c manager/*.hpp -o obj/$(patsubst .hpp, .o, $^)

engine: system manager
	g++ -c engine.hpp -o obj/engine.o
