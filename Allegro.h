#ifndef ALLEGRO_H
#define ALLEGRO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Allegro
{
    public:
        static void initialize(const int WIDTH, const int HEIGHT, const char* title);
        static void shutDown();
        
        static const float FPS;
        static ALLEGRO_DISPLAY* display;
        static ALLEGRO_TIMER* timer;
        static ALLEGRO_EVENT_QUEUE* eventQueue;
        static const int WIDTH;
        static const int HEIGHT;

    private:
        static void construct(const int width, const int height,const char* title);
        static void destruct(void);
};

#endif