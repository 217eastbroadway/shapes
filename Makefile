CC = g++

ifeq ($(OS),Windows_NT)
	CFLAGS = -lRaylib -lwinmm -lgdi32 -w -g
else
	CFLAGS = -lraylib -w -g
endif

INCLUDE = include

ifeq ($(OS),Windows_NT)
	LIB = lib
else
	LIB =
endif

TARGET = bin/shapes

$(TARGET): main.o
	$(CC) main.o $(CFLAGS) -o $(TARGET)

main.o: src/main.cpp
	$(CC) src/main.cpp -I$(INCLUDE) -c $(CFLAGS)

PHONY:
clean:
	rm *.o
	rm bin/*
