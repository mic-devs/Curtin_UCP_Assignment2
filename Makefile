CC = gcc
CFLAGS = -Wall -Werror -pedantic -ansi -g
OBJ = main.o build.o game.o terminal.o
EXEC = traffic

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c
	$(CC) -c main.c $(CFLAGS)

build.o : build.c
	$(CC) -c build.c $(CFLAGS)

game.o : game.c
	$(CC) -c game.c $(CFLAGS)

terminal.o : terminal.c
	$(CC) -c terminal.c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)