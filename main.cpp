/*
 * Logic implementation of the Snake game. It is designed to efficiently
 * represent the state of the game in memory.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */

#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
// #include <SDL3/SDL_ttf.h>
#include "render_context.h"
#include "main_menu.h"

#define STEP_RATE_IN_MILLISECONDS  125
#define SNAKE_BLOCK_SIZE_IN_PIXELS 24
#define SDL_WINDOW_WIDTH           (SNAKE_BLOCK_SIZE_IN_PIXELS * SNAKE_GAME_WIDTH)
#define SDL_WINDOW_HEIGHT          (SNAKE_BLOCK_SIZE_IN_PIXELS * SNAKE_GAME_HEIGHT)

#define SNAKE_GAME_WIDTH  24U
#define SNAKE_GAME_HEIGHT 18U
#define SNAKE_MATRIX_SIZE (SNAKE_GAME_WIDTH * SNAKE_GAME_HEIGHT)

#define THREE_BITS  0x7U /* ~CHAR_MAX >> (CHAR_BIT - SNAKE_CELL_MAX_BITS) */
#define SHIFT(x, y) (((x) + ((y) * SNAKE_GAME_WIDTH)) * SNAKE_CELL_MAX_BITS)

typedef enum
{
    SNAKE_CELL_NOTHING = 0U,
    SNAKE_CELL_SRIGHT = 1U,
    SNAKE_CELL_SUP = 2U,
    SNAKE_CELL_SLEFT = 3U,
    SNAKE_CELL_SDOWN = 4U,
    SNAKE_CELL_FOOD = 5U
} SnakeCell;

#define SNAKE_CELL_MAX_BITS 3U /* floor(log2(SNAKE_CELL_FOOD)) + 1 */

typedef enum
{
    SNAKE_DIR_RIGHT,
    SNAKE_DIR_UP,
    SNAKE_DIR_LEFT,
    SNAKE_DIR_DOWN
} SnakeDirection;

typedef struct
{
    unsigned char cells[(SNAKE_MATRIX_SIZE * SNAKE_CELL_MAX_BITS) / 8U];
    char head_xpos;
    char head_ypos;
    char tail_xpos;
    char tail_ypos;
    char next_dir;
    char inhibit_tail_step;
    unsigned occupied_cells;
} SnakeContext;

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    Uint64 last_step;
} AppState;

MainMenu* mainMenu = new MainMenu();

static SDL_AppResult handle_key_event_(SnakeContext *ctx, SDL_Scancode key_code)
{
    switch (key_code) {
    /* Quit. */
    case SDL_SCANCODE_ESCAPE:
    case SDL_SCANCODE_Q:
        return SDL_APP_SUCCESS;
    /* Restart the game as if the program was launched. */
    case SDL_SCANCODE_R:
    /* Decide new direction of the snake. */
    case SDL_SCANCODE_RIGHT:
    case SDL_SCANCODE_UP:
        break;
    case SDL_SCANCODE_LEFT:
        break;
    case SDL_SCANCODE_DOWN:
        break;
    default:
        break;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    AppState *as = (AppState *)appstate;
    const Uint64 now = SDL_GetTicks();
    // run game logic if we're at or past the time to run it.
    // if we're _really_ behind the time to run it, run it
    // several times.
    while ((now - as->last_step) >= STEP_RATE_IN_MILLISECONDS) {
        // update logic
        as->last_step += STEP_RATE_IN_MILLISECONDS;
    }
    SDL_SetRenderDrawColor(as->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(as->renderer);
    mainMenu->tick();
    SDL_RenderPresent(as->renderer);
    return SDL_APP_CONTINUE;
}

static const struct
{
    const char *key;
    const char *value;
} extended_metadata[] =
{
    { SDL_PROP_APP_METADATA_URL_STRING, "https://examples.libsdl.org/SDL3/demo/01-snake/" },
    { SDL_PROP_APP_METADATA_CREATOR_STRING, "SDL team" },
    { SDL_PROP_APP_METADATA_COPYRIGHT_STRING, "Placed in the public domain" },
    { SDL_PROP_APP_METADATA_TYPE_STRING, "game" }
};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    size_t i;

    if (!SDL_SetAppMetadata("Example Snake game", "1.0", "com.example.Snake")) {
        return SDL_APP_FAILURE;
    }

    for (i = 0; i < SDL_arraysize(extended_metadata); i++) {
        if (!SDL_SetAppMetadataProperty(extended_metadata[i].key, extended_metadata[i].value)) {
            return SDL_APP_FAILURE;
        }
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return SDL_APP_FAILURE;
    }

    AppState *as = (AppState *)SDL_calloc(1, sizeof(AppState));
    if (!as) {
        return SDL_APP_FAILURE;
    }

    *appstate = as;

    if (!SDL_CreateWindowAndRenderer("shooting game", SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT, 0, &as->window, &as->renderer)) {
        return SDL_APP_FAILURE;
    }

    getRenderContext()->init(as->renderer);

    mainMenu->init();

    as->last_step = SDL_GetTicks();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    case SDL_EVENT_KEY_DOWN: {
        mainMenu->handleEvent(event);
        // return handle_key_event_(ctx, event->key.scancode);
    }
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    if (appstate != NULL) {
        AppState *as = (AppState *)appstate;
        SDL_DestroyRenderer(as->renderer);
        SDL_DestroyWindow(as->window);
        SDL_free(as);
    }
}
