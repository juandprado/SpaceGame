all: 
	g++ -Iinclude -c main.cpp src/*.cpp
	g++ -o game *.o -L/usr/lib/x86_64-linux-gnu -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm *.o game