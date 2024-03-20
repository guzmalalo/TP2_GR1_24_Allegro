#ifndef TP2_GR1_24_RECTANGLE_H
#define TP2_GR1_24_RECTANGLE_H

#define WDISPLAY 800
#define HDISPLAY 600

struct rectangle{
    float x, y; // coordonées origine
    float w; // largeur
    float h; // hauteur
    float dx; // increment suivant x par pas de temps
    float dy; // increment suivant y par pas de temps
};

typedef struct rectangle RECTANGLE;

#endif //TP2_GR1_24_RECTANGLE_H
