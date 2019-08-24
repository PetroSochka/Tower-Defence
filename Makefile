Lab4: map.o texture.o main.o enemy.o menu.o tower.o
	g++ -g map.o texture.o main.o menu.o enemy.o tower.o -o lab4 -LD:\SFML\SFML-2.5.1\lib -lsfml-graphics -lsfml-system -lsfml-window

map.o: map.cpp
	g++ -g map.cpp -c -ID:\SFML\SFML-2.5.1\include

texture.o: texture.cpp
	g++ -g texture.cpp -c -ID:\SFML\SFML-2.5.1\include

main.o: main.cpp
	g++  -g main.cpp -c -ID:\SFML\SFML-2.5.1\include

enemy.o: enemy.cpp
	g++ -g enemy.cpp -c -ID:\SFML\SFML-2.5.1\include

menu.o: menu.cpp
	g++ -g menu.cpp -c -ID:\SFML\SFML-2.5.1\include

tower.o: tower.cpp
	g++ -g tower.cpp -c -ID:\SFML\SFML-2.5.1\include
