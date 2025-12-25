#ifndef INTERFEJS_H_INCLUDED
#define INTERFEJS_H_INCLUDED

#include "struktury.h"

void wynik2(WINDOW *win, struct dane* dane);
void wynik(WINDOW *win, struct dane* dane, struct zasady* zasady, int tura);
void plansza(WINDOW *win, struct dane* dane);
void wypisz_karty(WINDOW *win, struct dane* dane, struct zasady* zasady, int tura);
void idz_pole(WINDOW *win, int wybor);
int wybieranie_pola(WINDOW *win, struct dane* dane, struct zasady* zasady, int *karta, int tura);
void idz_karta(WINDOW *win, int tura, int wybor);
int wybieranie_karty(WINDOW *win, struct dane* dane, struct zasady* zasady, int tura);
void ruch(WINDOW *win, struct dane* dane, struct zasady* zasady, int tura);
void przygotuj_karty(struct dane* dane);
void czysc_plansze(struct dane* dane);
void czysc_linie(WINDOW* win, int start, int stop);
void gra(struct dane* dane, struct zasady* zasady);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);
void print_logo(WINDOW *win);
void print_menu(WINDOW *menu_win, int highlight);
void print_settings(WINDOW *win, int highlight);
void ustawienia(struct dane* dane, struct zasady* zasady);
void menu_glowne(struct dane* dane, struct zasady* zasady);
void wlacz_kolory();
void midi_start(struct zasady* zasady, char* midi);
void midi_stop(struct zasady* zasady);
void www();
extern void wykonaj_zasady(WINDOW *win, struct dane* dane, struct zasady* zasady, int a);
extern int losowa(int min, int max);
void autor(struct dane* dane, struct zasady* zasady);

#endif // INTERFEJS_H_INCLUDED
