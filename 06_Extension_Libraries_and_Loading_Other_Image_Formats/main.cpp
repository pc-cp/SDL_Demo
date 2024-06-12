#include <SDL.h>
#include <SDL_image.h>
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

/* An SDL surface is just an image data type
 * that contains the pixels of an image along
 * with all data needed to render it. SDL surfaces
 * use software rendering which means it uses the CPU to render.
 */
// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// Current displayed PNG image
SDL_Surface* gPNGSurface = NULL;

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
            // Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags)) {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }
            else {
                // Get window surface
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }
    return success;
}

bool loadMedia() {
    // Loading success flag
    bool success = true;

    // Load PNG surface
    gPNGSurface = loadSurface("./loaded.png");
    if(gPNGSurface == NULL) {
        printf( "Unable to load PNG image!");
        success = false;
    }
    return success;
}


void close() {
    // Deallocate surface
    SDL_FreeSurface(gPNGSurface);
    gPNGSurface = NULL;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL subsystem;
    IMG_Quit();
    SDL_Quit();

}

SDL_Surface* loadSurface(std::string path) {

    // The final optimized image
    SDL_Surface * optimizedSurface = NULL;
    // Load image at specified path
    SDL_Surface * loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), IMG_GetError());
    }
    else {
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
    SDL_Event e;
    bool quit = false;
    while(!quit) {
        while(SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                quit = true;
            default:
                break;
            }
        }
        // Apply the PNG image
        //  blit the loaded surface onto the screen surface
        SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, NULL);

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
