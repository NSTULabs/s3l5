deps:
	@sudo apt install libsfml-dev
build:
	@g++ main.cpp -o miner -lsfml-graphics -lsfml-window -lsfml-system