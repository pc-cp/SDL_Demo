#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

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

// The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;


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

    // Load splash image
    gHelloWorld = SDL_LoadBMP("hello.bmp");
    if(gHelloWorld == NULL) {
        printf( "Unable to load image %s! SDL Error: %s\n", "hello.bmp", SDL_GetError() );
        success = false;
    }
    return success;
}


void close() {
    // Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL subsystem;
    SDL_Quit();

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
            // Apply the image
            //  blit the loaded surface onto the screen surface
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

            // Update the surface
            SDL_UpdateWindowSurface(gWindow);

            event_loop();
        }
    }

    // Free resources and close SDL
    close();
    return 0;
}
