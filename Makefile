BIN= bin
LNAME= liboblivision.a
LOC= $(BIN)/$(LNAME)

CC= gcc
CFLAGS= -g -I "SDL/include" -Iinclude
LFLAGS= -L "$(BIN)" -loblivision \
	-L "SDL/lib" -lSDL2 -L "SDL_ttf/lib" -lSDL2_ttf

CFLAGS_MAC= -g -I /opt/local/include -Iinclude
LFLAGS_MAC= -L/opt/local/lib -lSDL2 -lSDL2_ttf -lSDL2_image

COMMON_C= src/oblivision.c src/log.c
COMMON_O= oblivision.o log.o

COMMON_TEST= test/test.c
COMMON_TEST_O= test.o
COLOR_TEST= test/winbuffer.c
NAME= tests

all: base test_

base:
	$(CC) $(CFLAGS) -L "SDL/lib" -lSDL2 -L "ttf/lib" -lSDL2_ttf -c $(COMMON_C)
	$(AR) rcs $(LOC) $(COMMON_O)

test_:
	$(CC) -o $(NAME) $(COMMON_TEST) $(CFLAGS) $(LFLAGS)
	$(CC) -o colors $(COLOR_TEST) $(CFLAGS) $(LFLAGS)

test_mac:
	$(CC) $(CFLAGS_MAC) -c $(COMMON_TEST) $(COMMON_C)
	$(CC) -o $(NAME) $(COMMON_TEST_O) $(COMMON_O) $(LFLAGS_MAC)
	$(CC) $(CFLAGS_MAC) -c test/opengl.c $(COMMON_C)
	$(CC) -o ovogl opengl.o $(COMMON_O) $(LFLAGS_MAC)

base-x32:
	$(CC) -m32 $(CFLAGS) -L "SDL/lib" -lSDL2 -L "ttf/lib" -lSDL2_ttf -L src -c $(COMMON_C)
	$(AR) rcs $(LOC) $(COMMON_O)

test_-x32:
	$(CC) -o $(NAME) $(COMMON_TEST) -m32 $(CFLAGS) $(LFLAGS)
	$(CC) -o colors $(COLOR_TEST) -m32 $(CFLAGS) $(LFLAGS)
