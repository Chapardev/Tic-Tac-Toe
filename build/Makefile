checks = -Wall -Wextra -pedantic-errors
libs = -lraylib -lopengl32 -lgdi32 -lwinmm
no_console = -Wl,-subsystem,windows

default:
	g++ -std=c++17 -O2 ../src/*.cpp -o TicTacToe $(checks) -I ../include -L ../lib $(libs) $(no_console)