PROJECT = framework
IN      = src/*.c src/**/*.c
OUT     = bin/$(PROJECT)

CC      = gcc
CFLAGS  = -Os -Wall -ansi -pedantic -g -std=c99
LFLAGS  = -lGL -lGLU -lSDL

all: $(PROJECT)

$(PROJECT): $(IN)
	$(CC) $(CFLAGS) $(IN) -o "$(OUT)" $(LFLAGS)

strip:
	strip $(OUT) 
	sstrip $(OUT) 
	upx -9 $(OUT) 
