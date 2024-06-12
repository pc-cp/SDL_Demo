#include <SDL.h>
#include <stdio.h>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// Loads individual image
SDL_Surface * loadSurface(std::string path);

// Hack to get window to stay up
void event_loop();

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

// Current displayed image
SDL_Surface *gStretchedSurface = NULL;

bool init() {
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia() {
    // Loading success flag
    bool success = true;

    // Load stretching surface
    gStretchedSurface = loadSurface("./stretch.bmp");
    if(gStretchedSurface == NULL) {
        printf( "Failed to load stretching image!\n");
        success = false;
    }

    return success;
}

void close() {
    // Free loaded image
    SDL_FreeSurface(gStretchedSurface);
    gStretchedSurface = NULL;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL subsystem;
    SDL_Quit();
}


SDL_Surface* loadSurface(std::string path) {

    // The final optimized image
    SDL_Surface * optimizedSurface = NULL;
    // Load image at specified path
    SDL_Surface * loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else {
        /*
         * when you load a bitmap, it's typically loaded in a
         * 24bit format since most bitmaps are 24bit. Most,
         * if not all, modern displays are not 24bit by default.
         * If we blit an image that's 24bit onto a 32bit image,
         * SDL will convert it every single time the image is blitted.
         */
        // Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if(optimizedSurface == NULL) {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

void event_loop() {
    // Main loop flag
    bool quit = false;
    // Event handler
    SDL_Event e;

    // While application is running
    while(!quit) {
        // Handle events on queue
        while(SDL_PollEvent(&e) != 0) {
            // User requests quit
            switch (e.type) {
            case SDL_QUIT:
                quit = true;
                break;
            default:
                break;
            }
        }
        // Apply the image stretched
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = SCREEN_WIDTH;
        stretchRect.h = SCREEN_HEIGHT;
        /*
         * 复制的同时对源图像进行缩放，适应目标表面的尺寸
         */
        SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);

        // Update the surface
        SDL_UpdateWindowSurface(gWindow);

    }
}

int main(int argc, char *argv[]) {
    // Start up SDL and create window
    if(!init()) {
        printf("Failed to initialize!\n");
    }
    else {
        // Load media
        if(!loadMedia()) {
            printf("Failed to load media!\n");
        }
        else {
            event_loop();
        }
    }

    // Free resources and close SDL
    close();
    return 0;
}
