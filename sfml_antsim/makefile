##
# ant simulating
#
# @file
# @version 0.1
antsim-release: ./run.cpp
	g++ -c ./ant.cpp -Wall -w -o ./adds/ant.o -lsfml-graphics -lsfml-window -lsfml-system  -lImGui-SFML
	g++ -c ./antSim.cpp -Wall -w -o ./adds/antSim.o -lsfml-graphics -lsfml-window -lsfml-system  -lImGui-SFML
	g++ -c ./run.cpp -Wall -w -o ./adds/run.o  -lsfml-graphics -lsfml-window -lsfml-system  -lImGui-SFML
	g++ ./adds/run.o ./utils.hpp ./controls.hpp ./adds/ant.o ./adds/antSim.o -Wall -w -o ./bin/antsim -lsfml-graphics -lsfml-window -lsfml-system  -lImGui-SFML
antsim-debug: ./run.cpp
	g++ -c ./ant.cpp -Wall -w -g -o ./adds/debug/ant.o -lsfml-graphics -lsfml-window -lsfml-system  -lImGui-SFML
	g++ -c ./antSim.cpp -Wall -w -g -o ./adds/debug/antSim.o -lsfml-graphics -lsfml-window -lsfml-system  -lImGui-SFML
	g++ -c ./run.cpp -Wall -w -g -o ./adds/debug/run.o  -lsfml-graphics -lsfml-window -lsfml-system  -lImGui-SFML
	g++ ./adds/run.o ./utils.hpp ./controls.hpp ./adds/debug/ant.o ./adds/debug/antSim.o -Wall -w -g -o ./bin/antsim -lsfml-graphics -lsfml-window -lsfml-system  -lImGui-SFML
# end
