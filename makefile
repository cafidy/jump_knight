all: main

main: main.o KNIGHT.o Map.o 
	g++ -o main main.o Map.o KNIGHT.o -std=c++11 -Wall -lbbop -lGLEW -lGL -lglfw -lfreetype

main.o: main.cpp
	g++ -c main.cpp -std=c++11 -Wall -lbbop -lGLEW -lGL -lglfw -lfreetype

Map.o: Map.cpp Map.h 
	g++ -c Map.cpp -std=c++11 -Wall -lbbop -lGLEW -lGL -lglfw -lfreetype

KNIGHT.o: KNIGHT.cpp KNIGHT.h
	g++ -c KNIGHT.cpp -std=c++11 -Wall -lbbop -lGLEW -lGL -lglfw -lfreetype

clean:
	rm -f *.o main
