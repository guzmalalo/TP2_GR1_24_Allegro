#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "rectangle.h"
enum{LEFT, UP, DOWN , RIGHT};

int main() {
    // Declarations
    ALLEGRO_DISPLAY * game_display = NULL;
    ALLEGRO_COLOR red = {0};
    ALLEGRO_TIMER * timer = NULL;
    ALLEGRO_EVENT_QUEUE * fifo = NULL;
    ALLEGRO_EVENT event = {0};
    RECTANGLE p = {0, 0, 50, 30, 10, 20};
    bool fini = false;
    bool flags[4]= {false};

    // Initialisation
    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_install_keyboard());

    // initialisation des coordonées
    p.x = (WDISPLAY - p.w) / 2.0f;
    p.y = (HDISPLAY - p.h) / 2.0f;

    // Creation
    game_display = al_create_display(WDISPLAY, HDISPLAY);
    timer = al_create_timer(1.0/24.0);
    fifo = al_create_event_queue();
    red = al_map_rgb(255, 0, 0);

    // sources
    al_register_event_source(fifo, al_get_display_event_source(game_display));
    al_register_event_source(fifo, al_get_timer_event_source(timer));
    al_register_event_source(fifo, al_get_keyboard_event_source());

    //boucle d'événements
    al_start_timer(timer);
    while (!fini){
        // piocher un event
        al_wait_for_event(fifo, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
            case ALLEGRO_EVENT_TIMER:
                if (flags[LEFT]) {
                    if (p.x > 0) {
                        p.x = p.x - p.dx;
                    }else{
                        p.x = 0;
                    }
                }
                if(flags[RIGHT]){
                    if(p.x < (WDISPLAY-p.w)) {
                        p.x = p.x + p.dx;
                    }else{
                        p.x = WDISPLAY - p.w;
                    }
                }
                if(flags[UP]) {
                    if (p.y > 0) {
                        p.y = p.y - p.dy;
                    }else{
                        p.y = 0;
                    }
                }
                if(flags[DOWN]) {
                    if((p.y+p.h) < HDISPLAY){
                        p.y = p.y + p.dy;
                    }else{
                        p.y = HDISPLAY - p.h;
                    }
                }


                al_clear_to_color(al_map_rgb(0,0,0));
                al_draw_filled_rectangle(p.x, p.y, p.x + p.w, p.y +p.h,red);
                al_flip_display();
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_LEFT:
                        flags[LEFT] = true;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        flags[RIGHT] = true;
                        break;
                    case ALLEGRO_KEY_UP:
                        flags[UP]= true;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        flags[DOWN] = true;
                        break;
                }
                // gerer le déplacement
                break;
            case ALLEGRO_EVENT_KEY_UP:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_LEFT:
                        flags[LEFT] = false;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        flags[RIGHT] = false;
                        break;
                    case ALLEGRO_KEY_UP:
                        flags[UP]= false;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        flags[DOWN] = false;
                        break;
                }
                break;
        }


    }


    // Liberation
    al_destroy_display(game_display);
    al_destroy_timer(timer);
    al_destroy_event_queue(fifo);

    return 0;
}
