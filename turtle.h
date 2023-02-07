#pragma once
#ifndef _TURTLE_H
#define _TURTLE_H

//source from Dr. Eike Anderson starts here
typedef struct RGBcolour
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
} RGBcolour;
//source from Dr. Eike Anderson ends here

//turtle struct
typedef struct turtle
{
    int length;
    int loops;
    int lines;
    bool drawing;
    RGBcolour colour;
    double angle;
    float xpos, ypos;
    float stxpos, stypos;
}turtle;

//turtle funtions prototypes

void colour(turtle* turtle, RGBcolour colour);

void left(turtle* turtle,double value);
   
void right(turtle* turtle,double value);
  
bool pen_up(turtle* turtle);
  
bool pen_down(turtle* turtle);
   
void forward(turtle* turtle, SDL_Renderer* renderer,int value);

void backward(turtle* turtle, SDL_Renderer* renderer, int value);

void initTurtle(turtle* turtle,SDL_Rect rect);

void clrscreen(SDL_Renderer* renderer,turtle* turtle,SDL_Rect rect,SDL_Rect rect1);

double degtorad(double angle);

double radtodeg(double angle);

void example1(SDL_Renderer* renderer, turtle* turtle, double angle);

void example2(SDL_Renderer* renderer, turtle* turtle, double angle);

void example3(SDL_Renderer* renderer, turtle* turtle, double angle);

void example4(SDL_Renderer* renderer, turtle* turtle, double angle);
#endif
