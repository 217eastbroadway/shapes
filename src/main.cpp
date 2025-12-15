#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

//I FUCKING HATE WINDOWS.H
//THIS SHIT CLASHES WITH EVERYTHING INSIDE RAYLIB.H FUCK THIS SHIT I WANNA BLOW UP MICROSOFT HQ
namespace win{
    #include <windows.h>
}

//Graphics Lib
#include <raylib/raylib.h>

//defs
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define MAX_RECT 20
#define MAX_CIRCLE 7
#define MAX_LINES 20
#define STR_LEN 9

typedef struct {
    int centerX, centerY;
    float radius;
    Color color;
}Circle;

typedef struct {
    Rectangle rectangle;
    Color color;
}ColorRectangle;

typedef struct {
    int startX, startY, endX, endY;
    Color color;
}Line;

int main() {
    //Window Init
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "shapes <demo> - @217eastbroadway");
    win::MessageBoxA(NULL, "Press F12 to capture a screenshot!", "Tip", MB_OK);
    
    //rng seed init
    srand(time(NULL));

    //Font used for displaying random text
    Font font = LoadFontEx("res/fonts/helvetica_neue_65.ttf", 20, NULL, 0);

    //Random text string (will be drawn)
    char randString[STR_LEN];
    for(int i = 0; i < STR_LEN; i++)
        randString[i] = 48 + rand() % (122 - 48 + 1); // 0 to Z


    Color backgroundColor = (Color){rand() % 255, rand() % 255, rand() % 255, 1};

    //array element counters
    int nRect, nLines, nCircles, nShapes;
    nRect = rand() % MAX_RECT;
    nLines = rand() % MAX_LINES;
    nCircles = rand() % MAX_CIRCLE;
    nShapes = nRect + nLines + nCircles;
    int *drawingOrder = (int*)calloc(sizeof(int), nShapes); //array containing the randomly ordered indexes of elements that will be drawn

     for(int i = 0; i < nShapes; i++) //Array Init
        drawingOrder[i] = 0;
    
    //Index generation
    for(int i = 0; i < nShapes; i++) {
        bool isPresent;
        int randI = 0;
            do {
                isPresent = false;
                randI = rand() % nShapes + 1;
            
                for(int j = 0; j < nShapes; j++) 
                    if(drawingOrder[j] == randI) 
                        isPresent = true;
                            
            }while(isPresent);
        drawingOrder[i] = randI;
    }

    for(int i = 0; i < nShapes; i++) //offsetting each index by -1 (by default they go from 1 to N instead of 0 to N - 1)
        drawingOrder[i]--;

    //Shape arrays
    ColorRectangle *rectangles = (ColorRectangle*)malloc(sizeof(ColorRectangle) * nRect);
    Line *lines = (Line*)malloc(sizeof(Line) * nLines);
    Circle *circles = (Circle*)malloc(sizeof(Circle) * nCircles);
    if(!rectangles || !lines || !circles) //pointer check
        exit(EXIT_FAILURE);
    
    //Random shape generation
    for(int i = 0; i < nRect; i++) { //Rectangles
        rectangles[i].rectangle = (Rectangle){(float)(rand() % WINDOW_WIDTH), (float)(rand() % WINDOW_HEIGHT), (float)(rand() % 200), (float)(rand() % 200)};
        rectangles[i].color = (Color){rand() % 255, rand() % 255, rand() % 255, 150 + rand() % (255 - 150 + 1)};
    }

    for(int i = 0; i < nLines; i++) { //Lines
        lines[i].startX = rand() % WINDOW_WIDTH;
        lines[i].startY= rand() % WINDOW_HEIGHT;
        lines[i].endX = rand() % WINDOW_WIDTH;
        lines[i].endY= rand() % WINDOW_HEIGHT;

        lines[i].color = (Color){rand() % 255, rand() % 255, rand() % 255, 150 + rand() % (255 - 150 + 1)};
    }

    for(int i = 0; i < nCircles; i++) { //Circles
        circles[i].centerX = rand() % WINDOW_WIDTH;
        circles[i].centerY = rand() % WINDOW_HEIGHT;
        circles[i].radius = (float)(250 + rand() % (1000 - 250 + 1)) / pow(10, 1);

        circles[i].color = (Color){rand() % 255, rand() % 255, rand() % 255, 150 + rand() % (255 - 150 + 1)};
    }

    //Resources Initialization
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(backgroundColor);

        for(int i = 0; i < nShapes; i++) {
            if(drawingOrder[i] >= nRect + nLines) {
                DrawCircle(circles[drawingOrder[i] - (nRect + nLines)].centerX, circles[drawingOrder[i] - (nRect + nLines)].centerY, circles[drawingOrder[i] - (nRect + nLines)].radius, circles[drawingOrder[i] - (nRect + nLines)].color);
            }
            else if (drawingOrder[i] >= nRect) {
                DrawLine(lines[drawingOrder[i] - nRect].startX, lines[drawingOrder[i] - nRect].startY, lines[drawingOrder[i] - nRect].endX, lines[drawingOrder[i] - nRect].endY, lines[drawingOrder[i] - nRect].color);
            }
            else {
                DrawRectangle(rectangles[drawingOrder[i]].rectangle.x, rectangles[drawingOrder[i]].rectangle.y, rectangles[drawingOrder[i]].rectangle.width, rectangles[drawingOrder[i]].rectangle.height, rectangles[drawingOrder[i]].color);
            }
        }

        DrawTextPro(font, randString, (Vector2){10.0f, 10.0f}, (Vector2){0.0f, 0.0f}, 0.0f, 20.0f, 0.0f, WHITE);

        EndDrawing();
    }

    return 0;
}