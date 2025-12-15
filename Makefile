CC = g++

ifeq ($(OS),Windows_NT)
	CFLAGS = -lRaylib -lwinmm -lgdi32 -w -g
else
	CFLAGS = -lRaylib -w -g
endif

INCLUDE = include
LIB = lib
TARGET = bin/shapes

$(TARGET): main.o
	$(CC) main.o -L$(LIB) $(CFLAGS) -o $(TARGET)

main.o: src/main.cpp
	$(CC) src/main.cpp -I$(INCLUDE) -c $(CFLAGS)

PHONY:
clean:
	rm *.o
	rm bin/*