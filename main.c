/*
 * This example creates an SDL window and renderer, and then draws some lines,
 * rectangles and points to it every frame.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */

#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_FPoint points[500];
// static SDL_FRect rect = {10, 10, 50, 50};

const int kScreenSizeWidth = 640;
const int kScreenSizeHeight = 480;

struct GameObject
{
    int color[4];
    SDL_FRect rect;
};

static struct GameObject gPlayer = {{0, 255, 0, SDL_ALPHA_OPAQUE}, {10, 10, 10, 50}};
static struct GameObject gEnemy = {{255, 0, 0, SDL_ALPHA_OPAQUE}, {kScreenSizeWidth - 20, kScreenSizeHeight - 60, 10, 50}};

void HandlePlayerMovement(SDL_Event *event)
{
    if (event->key.scancode == SDL_SCANCODE_SPACE)
    {
        // handle shoot/attack? or something
    }
    if (event->key.scancode == SDL_SCANCODE_UP)
    {
        gPlayer.rect.y -= 10;
    }
    if (event->key.scancode == SDL_SCANCODE_DOWN)
    {
        gPlayer.rect.y += 10;
    }
    if (event->key.scancode == SDL_SCANCODE_RIGHT)
    {
        gPlayer.rect.y += 10;
    }
    if (event->key.scancode == SDL_SCANCODE_LEFT)
    {
        gPlayer.rect.y -= 10;
    }
}

void HandleEnemyMovement()
{
    if (gEnemy.rect.y > kScreenSizeHeight - gEnemy.rect.h)
    {
        gEnemy.rect.y -= 0.05;
    }
    else if (gEnemy.rect.y < 5)
    {
        gEnemy.rect.y += 0.05;
    }
    else
    {
        gEnemy.rect.y += 0.01;
    }
}

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    int i;

    SDL_SetAppMetadata("Example Renderer Primitives", "1.0", "com.example.renderer-primitives");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/primitives", kScreenSizeWidth, kScreenSizeHeight, 0, &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /* set up some random points */
    for (i = 0; i < SDL_arraysize(points); i++)
    {
        points[i].x = (SDL_randf() * 440.0f) + 100.0f;
        points[i].y = (SDL_randf() * 280.0f) + 100.0f;
    }

    return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
    }

    if (event->type == SDL_EVENT_KEY_DOWN)
    {
    }

    return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    HandleEnemyMovement();

    /* as you can see from this, rendering draws over whatever was drawn before it. */
    SDL_SetRenderDrawColor(renderer, 33, 33, 33, SDL_ALPHA_OPAQUE); /* dark gray, full alpha */
    SDL_RenderClear(renderer);                                      /* start with a blank canvas. */

    /* draw a filled rectangle in the middle of the canvas. */
    SDL_SetRenderDrawColor(renderer, gPlayer.color[0], gPlayer.color[1], gPlayer.color[2], gPlayer.color[3]); /* blue, full alpha */
    SDL_RenderFillRect(renderer, &gPlayer.rect);

    /* draw a filled rectangle in the middle of the canvas. */
    SDL_SetRenderDrawColor(renderer, gEnemy.color[0], gEnemy.color[1], gEnemy.color[2], gEnemy.color[3]); /* blue, full alpha */
    SDL_RenderFillRect(renderer, &gEnemy.rect);                                                           /* filled rectangle */

    SDL_RenderPresent(renderer); /* put it all on the screen! */

    return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}
