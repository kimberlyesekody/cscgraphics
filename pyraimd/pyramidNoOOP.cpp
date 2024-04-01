#include "pyramidNoOOP.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <SDL.h>

struct Point2D { float x; float y; };
struct Point3D { float x; float y; float z; };
struct Edge { int start; int end; };

int WindowSizeX;
int WindowSizeY;
SDL_Renderer* renderer;
float DeltaTime = 0;
float FL = 5;

// Creates an array of points for a pyramid
std::vector<Point3D> points2{
    Point3D{0, 1, 0},    // Top point
    Point3D{-1, 0, -1},  // Bottom-left front
    Point3D{1, 0, -1},   // Bottom-right front
    Point3D{1, 0, 1},    // Bottom-right back
    Point3D{-1, 0, 1}    // Bottom-left back
};

// Creates an array of edges (This holds indices referencing to the points array)
std::vector<Edge> edges2{
    Edge{0, 1},  // Top point to bottom-left front
    Edge{0, 2},  // Top point to bottom-right front
    Edge{0, 3},  // Top point to bottom-right back
    Edge{0, 4},  // Top point to bottom-left back
    Edge{1, 2},  // Bottom-left front to bottom-right front
    Edge{2, 3},  // Bottom-right front to bottom-right back
    Edge{3, 4},  // Bottom-right back to bottom-left back
    Edge{4, 1}   // Bottom-left back to bottom-left front
};

Point2D projection2(Point3D point)
{
    return Point2D{WindowSizeX / 2 + (point.x * FL) / (FL + point.z) * 100, WindowSizeY / 2 + (point.y * FL) / (FL + point.z) * 100};
}

void render2(std::vector<Point3D> points, std::vector<Edge> edges)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    for (auto& edge : edges) {
        Point2D start = projection2(points[edge.start]);
        Point2D end = projection2(points[edge.end]);

        SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
    }

    SDL_RenderPresent(renderer);
}

// Default C++ function
int main(int argc, char* argv[])
{
    // Creating a window and a renderer
    SDL_Window* window;

    // Creates a centered window with 960 width and 540 height
    window = SDL_CreateWindow("Pyramid Renderer No OOP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_GetWindowSize(window, &WindowSizeX, &WindowSizeY);

    bool running = true;

    while (running)
    {
        // If the quit button is pressed, the loop breaks
        if (SDL_QuitRequested()) { running = false; break; }

        // Calls the function to render the pyramid
        render2(points2, edges2);
    }

    return 0;
}