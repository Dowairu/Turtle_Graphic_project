#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL_image.h>
#include "turtle.h"



//angle conversion funtions
double degtorad(double angle)
{
    double radang = angle * (M_PI / 180);
    return radang;
}

double radtodeg(double angle)
{
    double degang = angle * (180/M_PI);
    return degang;
}

//turtle funtions
void clrscreen(SDL_Renderer* renderer,turtle* turtle,SDL_Rect rect, SDL_Rect rect1)
{
    SDL_SetRenderDrawColor(renderer,turtle->colour.r, turtle->colour.g, turtle->colour.b, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect1);
    initTurtle(turtle,rect);
}

void colour(turtle* turtle, RGBcolour colour) 
{
    //source from eike anderson begins here
    memcpy(&(turtle->colour), &colour, 3 * sizeof(Uint8));
    //reference edns here
    printf("turtle colour is now: r-%d g-%d b-%d\n", turtle->colour.r, turtle->colour.g, turtle->colour.b);
}

void left(turtle* turtle,double value) 
{
    turtle->angle -= value;
    printf("added %f to angle\n", turtle->angle);
}

void right(turtle* turtle,double value)
{
    turtle->angle += value;
    printf("the angle is now: %f\n", turtle->angle);
}

bool pen_up(turtle* turtle) {
    turtle->drawing = false;
    return turtle->drawing;
}

bool pen_down(turtle* turtle) {
    turtle->drawing = true;
    return turtle->drawing;
}

void forward(turtle* turtle, SDL_Renderer* renderer,int value)
{
    turtle->xpos = value * cos(turtle->angle)+turtle->stxpos;
    turtle->ypos = value * sin(turtle->angle)+turtle->stypos;

    if (turtle->drawing == 1)
    {
        SDL_SetRenderDrawColor(renderer, turtle->colour.r, turtle->colour.g, turtle->colour.b, 255);
        SDL_RenderDrawLine(renderer, turtle->stxpos, turtle->stypos, turtle->xpos, turtle->ypos);
    }

    turtle->stxpos = turtle->xpos;
    turtle->stypos = turtle->ypos;

}

void backward(turtle* turtle, SDL_Renderer* renderer,int value)
{
    turtle->xpos =   turtle->stxpos - value * cos(turtle->angle);
    turtle->ypos =   turtle->stypos - value * sin(turtle->angle);

    if (turtle->drawing == 1)
    {
        SDL_SetRenderDrawColor(renderer, turtle->colour.r, turtle->colour.g, turtle->colour.b, 255);
        SDL_RenderDrawLine(renderer, turtle->stxpos, turtle->stypos, turtle->xpos, turtle->ypos);
    }

    turtle->stxpos = turtle->xpos;
    turtle->stypos = turtle->ypos;

}

void initTurtle(turtle* turtle,SDL_Rect rect) {
    turtle->length = 20;
    turtle->loops = 1;
    turtle->lines = 1;
    turtle->drawing = false;
    turtle->angle = degtorad(0);
    turtle->xpos = 775;
    turtle->ypos = 400;
    turtle->stxpos = rect.w/2+(305);
    turtle->stypos = rect.h/2+(35);

    printf("turtle initialised\n");
    printf("turtle loops is: %d\n", turtle->loops);
    printf("turtle lines is: %d\n", turtle->lines);
    printf("turtle angle is: %f\n", turtle->angle);
    printf("turtle drawing is: %d\n", turtle->drawing);
}

void example1(SDL_Renderer* renderer, turtle* turtle, double angle)
{
    pen_down(turtle);
    for (int j = 1; j <= turtle->loops; j++)
    {
        for (int i = 1; i <= turtle->lines; i++)
        {
            left(turtle, angle);
            forward(turtle, renderer, turtle->length * i);
        }
    }
}

void example2(SDL_Renderer* renderer, turtle* turtle, double angle)
{
    pen_down(turtle);
    for (int j = 1; j <= turtle->loops; j++)
    {
        for (int i = 1; i <= turtle->lines; i++)
        {
            forward(turtle, renderer, turtle->length * i);
            right(turtle, angle);

        }
    }
}

void example3(SDL_Renderer* renderer, turtle* turtle, double angle)
{
    angle = degtorad(144);
    pen_down(turtle);
    for (int j = 1; j <= turtle->loops; j++)
    {
        for (int i = 1; i <= turtle->lines; i++)
        {
            forward(turtle, renderer, turtle->length * i);
            right(turtle, angle);

        }
    }
}

void example4(SDL_Renderer* renderer, turtle* turtle, double angle)
{
    angle = degtorad(72);
    pen_down(turtle);
    for (int j = 1; j <= turtle->loops; j++)
    {
        for (int i = 1; i <= turtle->lines; i++)
        {
            forward(turtle, renderer, turtle->length * i);
            right(turtle, angle);

        }
    }
}


