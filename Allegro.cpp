#include "Allegro.h"

void Allegro::initialize(const int width, const int height,const char* title)
{
    al_init();

    al_install_keyboard();
    al_install_mouse();

    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(8);
    al_set_blender(ALLEGRO_ADD,ALLEGRO_ALPHA,ALLEGRO_INVERSE_ALPHA);

    construct(width, height,title);
}

void Allegro::shutDown(void)
{
    destruct();

    if(al_is_audio_installed()) al_uninstall_audio();

    al_shutdown_image_addon();
    al_shutdown_primitives_addon();
    al_shutdown_ttf_addon();
    al_shutdown_font_addon();

    if(al_is_keyboard_installed()) al_uninstall_keyboard();
    if(al_is_mouse_installed()) al_uninstall_mouse();

    if(al_is_system_installed()) al_uninstall_system();
}

void Allegro::construct(const int width, const int height,const char* title)
{
    display = al_create_display(width, height);
    al_set_window_title(display,title);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    timer = al_create_timer(1.0 / FPS);
    al_start_timer(timer);

    eventQueue = al_create_event_queue();

    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_register_event_source(eventQueue, al_get_keyboard_event_source());

    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
}

void Allegro::destruct(void)
{
    if(display != NULL) al_destroy_display(display);
    if(timer != NULL) al_destroy_timer(timer);
    if(eventQueue != NULL) al_destroy_event_queue(eventQueue);

    display = NULL;
    timer = NULL;
    eventQueue = NULL;
}

const float Allegro::FPS = 60.f;
ALLEGRO_DISPLAY* Allegro::display = NULL;
ALLEGRO_TIMER* Allegro::timer = NULL;
ALLEGRO_EVENT_QUEUE* Allegro::eventQueue = NULL;
const int Allegro::WIDTH = 800;
const int Allegro::HEIGHT = 600;