#ifndef ZASADY_H_INCLUDED
#define ZASADY_H_INCLUDED

#include "struktury.h"

int losowa(int min, int max);
void combo_zmiana(WINDOW* win, struct dane* dane, struct zasady* zasady, int zmiana0, int zmiana1, int zmiana2);
void gora(WINDOW* win, struct dane* dane, struct zasady* zasady, int a);
void dol(WINDOW* win, struct dane* dane, struct zasady* zasady, int a);
void lewo(WINDOW* win, struct dane* dane, struct zasady* zasady, int a);
void prawo(WINDOW* win, struct dane* dane, struct zasady* zasady, int a);
void bicie(WINDOW* win, struct dane* dane, struct zasady* zasady, int a);
int swoje_gora(struct dane* dane, int a);
int swoje_dol(struct dane* dane, int a);
int swoje_lewo(struct dane* dane, int a);
int swoje_prawo(struct dane* dane, int a);
int sgora(struct dane* dane, int a);
int sdol(struct dane* dane, int a);
int slewo(struct dane* dane, int a);
int sprawo(struct dane* dane, int a);
int pgora(struct dane* dane, int a);
int pdol(struct dane* dane, int a);
int plewo(struct dane* dane, int a);
int pprawo(struct dane* dane, int a);
void plus_change(WINDOW *win, struct dane* dane, struct zasady* zasady, int a, int b, int c);
void plus(WINDOW *win, struct dane* dane, struct zasady* zasady, int a);
int mgora(struct dane* dane, int a);
int mdol(struct dane* dane, int a);
int mlewo(struct dane* dane, int a);
int mprawo(struct dane* dane, int a);
void minus_change(WINDOW *win, struct dane* dane, struct zasady* zasady, int a, int b, int c);
void minus(WINDOW *win, struct dane* dane, struct zasady* zasady, int a);
void same_change(WINDOW *win, struct dane* dane, struct zasady* zasady, int a, int b, int c);
void same(WINDOW *win, struct dane* dane, struct zasady* zasady, int a);
void combo(WINDOW* win, struct dane* dane, struct zasady* zasady);
void wykonaj_zasady(WINDOW *win, struct dane* dane, struct zasady* zasady, int a);

#endif // ZASADY_H_INCLUDED
