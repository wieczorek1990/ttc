#ifndef STRUKTURY_H_INCLUDED
#define STRUKTURY_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <mmsystem.h>
#include <curses.h>

#define WIDTH 80
#define HEIGHT 25

struct dane
{
    char* znak[11];
    int wylozona[11], karta_plansza_gora[11], karta_plansza_dol[11], karta_plansza_lewo[11],
    karta_plansza_prawo[11], karta_gracza_gora[11], karta_gracza_dol[11], karta_gracza_lewo[11],
    karta_gracza_prawo[11], zmiana0, zmiana1, zmiana2, zbilem, wall_value;
};

struct zasady
{
    int same, plus, minus, open, order, order_counter, wall, combo, muzyka;
    MCI_OPEN_PARMS mciOpenParms;
};

#endif // STRUKTURY_H_INCLUDED
