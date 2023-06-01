BIN= bin
LNAME= liboblivision.a
LOC= $(BIN)/$(LNAME)

CC= gcc
CFLAGS= -g -I "SDL/include"
LFLAGS= -L "$(BIN)" -loblivision \
	-L "SDL/lib" -lSDL2 -L "SDL_ttf/lib" -lSDL2_ttf


COMMON_C= src/oblivision.c
COMMON_O= oblivision.o

COMMON_TEST= test/test.c
COLOR_TEST= test/wincolor.c
NAME= test

all: base test_

base:
	$(CC) $(CFLAGS) -L "SDL/lib" -lSDL2 -L "ttf/lib" -lSDL2_ttf -L src -c $(COMMON_C)
	$(AR) rcs $(LOC) $(COMMON_O)

test_:
	$(CC) -o $(NAME) $(COMMON_TEST) $(CFLAGS) $(LFLAGS)
	$(CC) -o colors $(COLOR_TEST) $(CFLAGS) $(LFLAGS)

base-x32:
	$(CC) -m32 $(CFLAGS) -L "SDL/lib" -lSDL2 -L "ttf/lib" -lSDL2_ttf -L src -c $(COMMON_C)
	$(AR) rcs $(LOC) $(COMMON_O)

test_-x32:
	$(CC) -o $(NAME) $(COMMON_TEST) -m32 $(CFLAGS) $(LFLAGS)
	$(CC) -o colors $(COLOR_TEST) -m32 $(CFLAGS) $(LFLAGS)


