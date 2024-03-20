#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "rectangle.h"

int main() {
    // Declarations
    ALLEGRO_DISPLAY * game_display = NULL;
    ALLEGRO_COLOR red = {0};
    ALLEGRO_TIMER * timer = NULL;
    ALLEGRO_EVENT_QUEUE * fifo = NULL;
    ALLEGRO_EVENT event = {0};
    RECTANGLE p = {0, 0, 50, 30, 10, 20};
    bool fini = false;
    bool flag_left = false;
    bool flags [4];

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
                if (flag_left) {
                    if (p.x > 0) {
                        p.x = p.x - p.dx;
                    }
                }
                al_clear_to_color(al_map_rgb(0,0,0));
                al_draw_filled_rectangle(p.x, p.y, p.x + p.w, p.y +p.h,red);
                al_flip_display();
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_LEFT:
                        flag_left = true;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        if(p.x < (WDISPLAY-p.w)) {
                            p.x = p.x + p.dx;
                        }
                        break;
                    case ALLEGRO_KEY_UP:
                        if(p.y>0){
                            p.y = p.y - p.dy;
                        }
                        break;
                    case ALLEGRO_KEY_DOWN:
                        if((p.y+p.h) < HDISPLAY){
                            p.y = p.y + p.dy;
                        }
                        break;

                }
                // gerer le déplacement
                break;
            case ALLEGRO_KEY_UP:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_LEFT:
                        flag_left = false;
                        break;
                }
        }


    }


    // Liberation
    al_destroy_display(game_display);
    al_destroy_timer(timer);
    al_destroy_event_queue(fifo);

    return 0;
}
