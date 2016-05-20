all: 
	g++ -I SFML-1.6/include -Iinclude -c main.cpp src/*.cpp
	g++ -o game *.o -L SFML-1.6/lib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm *.o game
