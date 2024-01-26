CC = g++

SnakeGame: main.cpp
	$(CC) main.cpp -o SnakeGame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network