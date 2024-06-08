#include </opt/homebrew/include/SDL2/SDL.h>
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
// 代表的是窗口的逻辑概念，它是存放在主内存中的一个对象。当我们调用SDL API创建
// 窗口后，它并不会被显示出来。
SDL_Window *gWindow = NULL;

/* An SDL surface is just an image data type
 * that contains the pixels of an image along
 * with all data needed to render it. SDL surfaces
 * use software rendering which means it uses the CPU to render.
 */
// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// The image we will load and show on the screen
SDL_Surface* gXOut = NULL;


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
    gXOut = SDL_LoadBMP("hello.bmp");
    if(gXOut == NULL) {
        printf( "Unable to load image %s! SDL Error: %s\n", "hello.bmp", SDL_GetError() );
        success = false;
    }
    return success;
}

void close() {
    // Deallocate surface
    SDL_FreeSurface(gXOut);
    gXOut = NULL;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL subsystem;
    SDL_Quit();

}

void event_loop() {
    // Main loop flag
    bool quit = false;

    // While application is running
    while(!quit) {
        // Event handler
        SDL_Event e;
        // Handle events on queue
        while(SDL_PollEvent(&e)) {
            // User requests quit
            switch (e.type) {
            case SDL_QUIT:
                quit = true;
            default:
                break;
            }
        }

        // Apply the image
        //  blit the loaded surface onto the screen surface
        SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);

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
