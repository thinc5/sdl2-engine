# executable name
SERVER_TARGET			:= server.out
CLIENT_TARGET			:= client.out
# compiler to use
CC						:= gcc
# compiler flags
CFLAGS   				:= --std=gnu11 -Wall -pedantic -O2
# linker to use
LINKER   				:= gcc
# linking flags
LFLAGS					:= -ldatachannel

#-------------- Helper scripts
rm						:= rm -rf

#-------------- Rules
# default rules
all: server client

# compile and link
server:
	@$(CC) $(CFLAGS) -c server.c -o server.o
	@$(CC) $(LFLAGS) server.o -o ${SERVER_TARGET}
	@$(rm) server.o

client:
	@$(CC) $(CFLAGS) -c client.c -o client.o
	@$(CC) $(LFLAGS) client.o -o ${CLIENT_TARGET}
	@$(rm) client.o

clean:
	@$(rm) *.o
	@$(rm) $(SERVER_TARGET)
	@$(rm) $(CLIENT_TARGET)
	@echo "Cleanup complete!"
