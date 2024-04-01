#include "pyramid.h"
#include "Renderer3D.h"
#include <iostream>
#include <vector>
#include <SDL.h>

// Creates an array of points for a pyramid
std::vector<Point3D> points{
    Point3D{0, 1, 0},    // Top point
    Point3D{-1, 0, -1},  // Bottom-left front
    Point3D{1, 0, -1},   // Bottom-right front
    Point3D{1, 0, 1},    // Bottom-right back
    Point3D{-1, 0, 1}    // Bottom-left back
};

// Creates an array of edges (This holds indices referencing to the points array)
std::vector<Edge> edges{
    Edge{0, 1},  // Top point to bottom-left front
    Edge{0, 2},  // Top point to bottom-right front
    Edge{0, 3},  // Top point to bottom-right back
    Edge{0, 4},  // Top point to bottom-left back
    Edge{1, 2},  // Bottom-left front to bottom-right front
    Edge{2, 3},  // Bottom-right front to bottom-right back
    Edge{3, 4},  // Bottom-right back to bottom-left back
    Edge{4, 1}   // Bottom-left back to bottom-left front
};

// Default C++ function
int main(int argc, char* argv[])
{
    // Creating a window and a renderer
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Creates a centered window with 960 width and 540 height
    window = SDL_CreateWindow("Pyramid Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;

    // Creating an instance of the Renderer3D class
    Renderer3D render3D(window, renderer, points, edges);

    while (running)
    {
        // If the quit button is pressed, the loop breaks
        if (SDL_QuitRequested()) { running = false; break; }

        // Calls the function created in the Renderer3D class (render 3D is an instance of the class defined above)
        render3D.render();
    }

    return 0;
}