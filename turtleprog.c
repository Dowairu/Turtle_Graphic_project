/*************************************
 * Turtle Graphics Library By David Owairu
 * 
 * 
 * References
 * https://wiki.libsdl.org/APIByCategory
 * https://gigi.nullneuron.net/gigilabs/writing/sdl2-tutorials/
 * turtle logo image:https://www.flaticon.com/free-icon/turtle_849820?term=turtle&page=1&position=17&related_id=849820&origin=search
 * font https://www.dafont.com/error-2.font?text=turtle&back=theme
*************************************/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL_image.h>
#include "turtle.h"

//funtions and structures are in the header and function files

/*based on code by "TalesM" on stackoverflow , originates here:
https://stackoverflow.com/questions/22315980/sdl2-c-taking-a-screenshot/22339011#22339011
saves images.
*/

void SaveImage(SDL_Renderer* renderer,SDL_Rect rect,int num)
{
    SDL_Surface* brdsurf = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(renderer, &rect, SDL_PIXELFORMAT_ABGR8888, brdsurf->pixels, brdsurf->pitch);
    if (num == 1)
    {
        IMG_SavePNG(brdsurf, "savedpic.png");
        printf("saved as png\n");
    }  
    else if (num == 2)
    {
        IMG_SaveJPG(brdsurf, "savedpic.jpg", 100);
        printf("saved as jpg\n");
    }
    else if (num == 3)
    {
        SDL_SaveBMP(brdsurf, "savedpic.bmp");
        printf("saved as bmp\n");
    }
        
    SDL_FreeSurface(brdsurf);
}
/*code based on "TalesM" ends here.*/

void loadImage(SDL_Renderer* renderer, char* imgpath)
{
    SDL_Surface* UIimage = IMG_Load(imgpath);
    SDL_Texture* UIimgtexture = SDL_CreateTextureFromSurface(renderer, UIimage);

    SDL_RenderCopy(renderer, UIimgtexture, NULL, NULL);

    SDL_FreeSurface(UIimage);
    SDL_DestroyTexture(UIimgtexture);


}

void loadUI(SDL_Renderer* renderer,turtle* turtle,SDL_Rect rect)
{
    //loading UI image
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    loadImage(renderer, "images/TurtleUI.png");
}

void curcolDisplay(SDL_Renderer* renderer,SDL_Rect rect,turtle* turtle)
{
    SDL_SetRenderDrawColor(renderer, turtle->colour.r, turtle->colour.g, turtle->colour.b, 0);
    SDL_RenderFillRect(renderer, &rect);
}


//menu funtions: used to get keyboard in put when a menu has been opened
void ExampleMenu(SDL_Renderer* renderer,turtle* turtle, SDL_Rect rect,double angle, char* menu, char* menuReset)
{
    loadImage(renderer, menu);

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    running = false;
                    loadImage(renderer, menuReset);
                    break;
                case SDLK_1:
                    example1(renderer, turtle, angle);
                    printf("loading example project 1 ....\n");
                    break;
                case SDLK_2:
                    example2(renderer, turtle, angle);
                    printf("loading example project 2 ....\n");
                    break;
                case SDLK_3:
                    example3(renderer, turtle, angle);
                    printf("loading example project 3 ....\n");
                    break;
                case SDLK_4:
                    example4(renderer, turtle, angle);
                    printf("loading example project 4 ....\n");
                    break;
                }
                break;
            }
        }
        SDL_RenderPresent(renderer);//update
    }
}

void saveMenu(SDL_Renderer* renderer,SDL_Rect rect,char* menu,char* menuReset)
{
    loadImage(renderer, menu);

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            running = false;
                            loadImage(renderer, menuReset);
                            break;
                        case SDLK_1:
                            SaveImage(renderer, rect, 1);
                            break;
                        case SDLK_2:
                            SaveImage(renderer, rect, 2);
                            break;
                        case SDLK_3:
                            SaveImage(renderer, rect, 3);
                            break;
                        case SDLK_4:
                            //saveLoadMenu(renderer, rect, "images/SaveLoadUI.png", "images/TurtleSaveUI.png");
                            break;
                    }
                break;
            }
        }
        SDL_RenderPresent(renderer);//update
    }
}

void HelpMenu(SDL_Renderer* renderer, char* menu, char* menuReset)
{
    loadImage(renderer, menu);

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    running = false;
                    loadImage(renderer, menuReset);
                    break;
                }
                break;
            }
        }
        SDL_RenderPresent(renderer);//update
    }
}

//main funtion*/
int main(int argc, char* argv[])
{
    //window and drawing areas
    SDL_Rect winrect = {0,0,1280,800};
    SDL_Rect brdrect = {305,35,940,730};
    SDL_Rect curcol = {33,700,237,50};
    

    //SDL Initializations
    if(SDL_Init(SDL_INIT_EVERYTHING) !=0){
        printf("error: %s\n",SDL_GetError());
        return 1;
    }
    
    SDL_Window *window = SDL_CreateWindow("Turtle Program",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,winrect.w,winrect.h,SDL_WINDOW_SHOWN); 
    if(window == NULL){
        printf("unfortunately window was not created %s\n",SDL_GetError());
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    
    if(IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG|IMG_INIT_TIF) !=7){
        printf("failed to inialise SDL_image, error:%s\n",SDL_GetError());
        return false;
    }

    
    RGBcolour white = { 255,255,255 };
    RGBcolour grey = { 128,128,128 };
    RGBcolour pink = { 255,192,203 };
    RGBcolour purple = { 128,0,128 };
    RGBcolour red = { 255,0,0 };
    RGBcolour black = { 0,0,0 };
    RGBcolour blue = { 0,0,255 };
    RGBcolour yellow = { 255,255,0 };
    RGBcolour orange = { 255,128,0 }; 
    RGBcolour aqua = { 0,238,238 };
    RGBcolour green = { 0,255,0 };
    
    RGBcolour pigments[11] = {white,grey,pink,purple,red,black,blue,yellow,orange,aqua,green};
    
    int curcolnum = 0;
    double angle = degtorad(0);

    turtle myturtle;
    initTurtle(&myturtle,brdrect);
    colour(&myturtle, black);
    curcolDisplay(renderer, curcol, &myturtle);
    loadUI(renderer,&myturtle,brdrect);
    
    
    //event loop
    bool running = true;

    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
                    printf("quit button pressed");
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            running = false;
                            printf("quit button pressed");
                            break;
                        case SDLK_RETURN:
                            if ((myturtle.xpos > 305 && myturtle.xpos < 1245) && (myturtle.ypos > 38 && myturtle.ypos < 760))
                                /*input you personal turtle commands here.
                                * 
                                * 
                                * 
                                */
                                break;

                        case SDLK_b:
                            clrscreen(renderer,&myturtle,brdrect,curcol);
                            loadImage(renderer, "images/TurtleUI.png");
                            break;

                            //cycle through colours
                        case SDLK_c:
                            if (curcolnum > 10) curcolnum = 0;
                            colour(&myturtle, pigments[curcolnum]);
                            curcolDisplay(renderer, curcol, &myturtle);
                            loadImage(renderer, "images/TurtleUI.png");
                            curcolnum++;
                            break;

                            //cycle through no. loops(q) and lines(e)
                        case SDLK_q:
                            if (myturtle.loops <6) myturtle.loops++;
                            if (myturtle.loops > 5) myturtle.loops = 1;
                            printf("the no. loops is now: %d\n", myturtle.loops);
                            break;
                        case SDLK_e:
                            if (myturtle.lines < 11) myturtle.lines++;
                            if (myturtle.lines > 10) myturtle.lines = 1;
                            printf("the no. lines is now: %d\n", myturtle.lines);
                            break;

                            //angle control
                        case SDLK_d:
                            angle += degtorad(5);
                            printf("the angle is now: %f\n", radtodeg(angle));
                            break;
                        case SDLK_a:
                            angle -= degtorad(5);
                            printf("the angle is now: %f\n", radtodeg(angle));
                            break;

                            //line length control
                        case SDLK_w:
                            if (myturtle.length < 40) myturtle.length += 5;
                            printf("line length is now: %d", myturtle.length);
                            break;
                        case SDLK_s:
                            if (myturtle.length >20)myturtle.length -= 5;
                            printf("line length is now: %d", myturtle.length);
                            break;

                            //menu buttons
                        case SDLK_x:
                            saveMenu(renderer, brdrect, "images/TurtleSaveUI.png", "images/TurtleUI.png");
                            break;
                        case SDLK_m:
                            ExampleMenu(renderer, &myturtle,brdrect,angle,"images/TurtleEgUI.png", "images/TurtleUI.png");
                            break;
                        case SDLK_TAB:
                            HelpMenu(renderer, "images/TurtleHelpUI.png", "images/TurtleUI.png");
                            break;
                    }
                    break;
            }
        
        SDL_RenderPresent(renderer);//update
    }
    
    //clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return false;
}