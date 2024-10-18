#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

typedef struct
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect bar1;
    SDL_Rect bar2;
    SDL_Rect ball;
}GameState;


float ball_speed_x = 7.0f;
float ball_speed_y = 1.0f;

bool init(GameState* state);

bool draw(GameState* state);

void collisions(GameState* state);

void update(GameState* state);


int main(int argc, char* args[])
{

    GameState state = {NULL,NULL};

    bool is_drawn = draw(&state);


    if(!(init(&state)))
    {
        printf("failed to initialise");
    }
    else
    {
        if(!draw(&state))
        {
            printf("failed to draw image");
        }
        else
        {
            bool quit = false;


            SDL_Event e;

            while(!quit)
            {
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN)
                    {
                        switch(e.key.keysym.sym)
                        {
                            case SDLK_UP:
                                if(state.bar2.y != 0)
                                {
                                    state.bar2.y -= 10;
                                }
                                break;
                            
                            case SDLK_DOWN:
                                if(state.bar2.y != 380)
                                {
                                    state.bar2.y += 10;
                                }
                                break;

                            case SDLK_w:
                                if(state.bar1.y != 0)
                                {
                                    state.bar1.y -= 10;
                                }
                                break;
                            
                            case SDLK_s:
                                if(state.bar1.y != 380)
                                {
                                    state.bar1.y += 10;
                                }
                                break;
                                
                            default:
                                break;
                        }
                    }
                    
                    if(state.ball.x == 640 - state.ball.w)
                    {
                        is_drawn = false;
                    }
                
                }

                
                update(&state);
                collisions(&state);
                if (state.ball.x == 500)
                {   
                    printf("asdasd");
                }
                        

                //Update screen
                SDL_SetRenderDrawColor(state.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(state.renderer);

                draw(&state);
                SDL_RenderPresent(state.renderer);

                SDL_Delay(16);

                

                
            }
        }
    }
}

bool init(GameState* state)
{

    //Load success flag
    bool success = true;

    //Initialise SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialise\n");
        success = false;
    }
    else
    {   
        //Create window
        state->window = SDL_CreateWindow("2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(state->window == NULL)
        {
            printf("Failed to create window\n");
            success = false;
        }
        else
        {
            //Create renderer
            state->renderer = SDL_CreateRenderer(state->window, -1, SDL_RENDERER_ACCELERATED);
            if(state->renderer == NULL)
            {
                printf("Failed to create renderer\n");
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(state->renderer, 0xFF, 0xFF, 255, 0xFF);
                state->bar1.x = 0;
                state->bar1.y = 380;
                state->bar1.w = 15;
                state->bar1.h = 100;

                state->bar2.x = 625;
                state->bar2.y = 380;
                state->bar2.w = 15;
                state->bar2.h = 100;

                state->ball.x = 200;
                state->ball.y = 240;
                state->ball.w = 15;
                state->ball.h = 15;
            }
        }
    }

    return success;
}

bool draw(GameState* state)
{   
    
    bool drawn = true;

    SDL_SetRenderDrawColor(state->renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(state->renderer, &state->bar1);

    SDL_SetRenderDrawColor(state->renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(state->renderer, &state->bar2);

    SDL_SetRenderDrawColor(state->renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(state->renderer, &state->ball);

    return drawn;
}

void collisions(GameState* state)
{
    if (state->ball.x < state->bar1.x + state->bar1.w &&
        state->ball.x + state->ball.w > state->bar1.x &&
        state->ball.y < state->bar1.y + state->bar1.h &&
        state->ball.y + state->ball.h > state->bar1.y)
        {
            ball_speed_x = -ball_speed_x;
        }

    if (state->ball.x < state->bar2.x + state->bar2.w &&
        state->ball.x + state->ball.w > state->bar2.x &&
        state->ball.y < state->bar2.y + state->bar2.h &&
        state->ball.y + state->ball.h > state->bar2.y)
        {
            ball_speed_x = -ball_speed_x;
        }

}

void update(GameState* state)
{
    state->ball.x += ball_speed_x;
    state->ball.y += ball_speed_y;

    if(state->ball.x < 0 || state->ball.x + state->ball.w > SCREEN_WIDTH)
    {
        ball_speed_x = -ball_speed_x;
    }

    if(state->ball.y < 0 || state->ball.y + state->ball.h > SCREEN_HEIGHT)
    {
        ball_speed_y = -ball_speed_y;
    }

}

