all: server

debug:
	gcc --std=gnu11 -g -Wall -pedantic -lwebsockets server.c snake_protocol.c -o server.o

server:
	gcc --std=gnu11 -Wall -pedantic -lwebsockets server.c snake_protocol.c -o server.o

clean:
	@rm -rf server.o
