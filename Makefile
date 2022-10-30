
all: client

client: main.cpp
	g++ main.cpp -o client -pthread -O0 -ggdb3

