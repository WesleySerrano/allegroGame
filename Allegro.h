#ifndef ALLEGRO_H
#define ALLEGRO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

/**
* Class for initializing and managing Allegro directives
*/

class Allegro
{
    public:
        /**
        * Initializes allegro, audio, graphics and input directives
        * also initializes the windows for rendering
        * @param WIDTH The window's width
        * @param HEIGHT The window's height
        * @param title The window's title
        */
        static void initialize(const int WIDTH, const int HEIGHT, const char* title);
        
        /**
        * Closes all the Allegro directives previously started
        */
        static void shutDown();
        
        static const float FPS;
        static ALLEGRO_DISPLAY* display;
        static ALLEGRO_TIMER* timer;
        static ALLEGRO_EVENT_QUEUE* eventQueue;
        static const int WIDTH;
        static const int HEIGHT;

    private:
        /**
        * Creates the window and adds the event listener to it
        * @param WIDTH The window's width
        * @param HEIGHT The window's height
        * @param title The window's title
        */
        static void construct(const int width, const int height,const char* title);
        
        /**
        * Destroys the event listener, the windows and the timer
        */
        static void destruct(void);
};

#endif