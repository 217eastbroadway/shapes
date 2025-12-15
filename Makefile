CC = g++
CFLAGS = -lRaylib -lwinmm -lgdi32 -w -g
INCLUDE = include
LIB = lib
TARGET = bin/shapes.exe

$(TARGET): main.o
	$(CC) main.o -L$(LIB) $(CFLAGS) -o $(TARGET)

main.o: src/main.cpp
	$(CC) src/main.cpp -I$(INCLUDE) -c $(CFLAGS)

PHONY:
clean:
	rm *.o
	rm bin/*.exe