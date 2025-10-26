/*
 * Logic implementation of the Snake game. It is designed to efficiently
 * represent the state of the game in memory.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */

#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "render_context.h"
// #include "main_menu.h"
#include "game_stage.h"

#define SDL_WINDOW_WIDTH        640
#define SDL_WINDOW_HEIGHT       960

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    Uint64 lastTick;
} AppState;

Stage* stage = new GameStage(vec2_t{SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT});

SDL_AppResult SDL_AppIterate(void *appstate)
{
    AppState *as = (AppState *)appstate;
    const Uint64 now = SDL_GetTicks();
    if(now - as->lastTick < 16) {
        return SDL_APP_CONTINUE;
    }
    auto interval = now - as->lastTick;
    as->lastTick = now;
    SDL_SetRenderDrawColor(as->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(as->renderer);
    stage->tick(interval);
    SDL_RenderPresent(as->renderer);
    return SDL_APP_CONTINUE;
}

static const struct
{
    const char *key;
    const char *value;
} extended_metadata[] =
{
    { SDL_PROP_APP_METADATA_URL_STRING, "shooting game" },
    { SDL_PROP_APP_METADATA_CREATOR_STRING, "OK" },
    { SDL_PROP_APP_METADATA_COPYRIGHT_STRING, "OK" },
    { SDL_PROP_APP_METADATA_TYPE_STRING, "game" }
};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    size_t i;

    if (!SDL_SetAppMetadata("GAME", "1.0", "you!")) {
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

    stage->init();

    as->lastTick = SDL_GetTicks();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    case SDL_EVENT_KEY_DOWN: {
        // return handle_key_event_(ctx, event->key.scancode);
    }
    }
    stage->handleEvent(event);
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
