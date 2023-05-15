BIN= bin
LNAME= liboblivision.a
LOC= $(BIN)/$(LNAME)

CC= gcc
CFLAGS= -m32 -g -I "SDL/include"
LFLAGS= -L "$(BIN)" -loblivision \
	-L "SDL/lib" -lSDL


COMMON_C= src/oblivision.c
COMMON_O= oblivision.o

COMMON_TEST= test/test.c
NAME= test

all: base

base:
	$(CC) $(CFLAGS) -L "SDL/lib" -lSDL -L src -c $(COMMON_C)
	$(AR) rcs $(LOC) $(COMMON_O)

test_:
	$(CC) -o $(NAME) $(COMMON_TEST) $(CFLAGS) $(LFLAGS)

