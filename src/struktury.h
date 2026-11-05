#ifndef STRUKTURY_H_INCLUDED
#define STRUKTURY_H_INCLUDED

#include <curses.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 80
#define HEIGHT 25

struct dane {

    int znak[12];

    int wylozona[12], karta_plansza_gora[12], karta_plansza_dol[12], karta_plansza_lewo[12],
        karta_plansza_prawo[12], karta_gracza_gora[12], karta_gracza_dol[12], karta_gracza_lewo[12],
        karta_gracza_prawo[12], zmiana0, zmiana1, zmiana2, zbilem, wall_value;
};

struct zasady {

    int same, plus, minus, open, order, order_counter, wall, combo, muzyka;

    int midi_playing;

    char midi_file[256];
};

#endif /* // STRUKTURY_H_INCLUDED */
