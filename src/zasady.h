#ifndef ZASADY_H_INCLUDED
#define ZASADY_H_INCLUDED

#include "struktury.h"

int losowa(int min, int max);

int combo_zmiana(WINDOW *win, struct dane *dane, struct zasady *zasady, int zmiana0, int zmiana1, int zmiana2);

void gora(WINDOW *win, struct dane *dane, struct zasady *zasady, int a);

void dol(WINDOW *win, struct dane *dane, struct zasady *zasady, int a);

void lewo(WINDOW *win, struct dane *dane, struct zasady *zasady, int a);

void prawo(WINDOW *win, struct dane *dane, struct zasady *zasady, int a);

void bicie(WINDOW *win, struct dane *dane, struct zasady *zasady, int a);

int swoje_gora(struct dane *dane, int a);

int swoje_dol(struct dane *dane, int a);

int swoje_lewo(struct dane *dane, int a);

int swoje_prawo(struct dane *dane, int a);

int sgora(struct dane *dane, int a);

int sdol(struct dane *dane, int a);

int slewo(struct dane *dane, int a);

int sprawo(struct dane *dane, int a);

int pgora(struct dane *dane, int a);

int pdol(struct dane *dane, int a);

int plewo(struct dane *dane, int a);

int pprawo(struct dane *dane, int a);

int plus_change(WINDOW *win, struct dane *dane, struct zasady *zasady, int a, int b, int c);

int plus(WINDOW *win, struct dane *dane, struct zasady *zasady, int a);

int mgora(struct dane *dane, int a);

int mdol(struct dane *dane, int a);

int mlewo(struct dane *dane, int a);

int mprawo(struct dane *dane, int a);

int minus_change(WINDOW *win, struct dane *dane, struct zasady *zasady, int a, int b, int c);

int minus(WINDOW *win, struct dane *dane, struct zasady *zasady, int a);

int same_change(WINDOW *win, struct dane *dane, struct zasady *zasady, int a, int b, int c);

int same(WINDOW *win, struct dane *dane, struct zasady *zasady, int a);

int combo(WINDOW *win, struct dane *dane, struct zasady *zasady);

int wykonaj_zasady(WINDOW *win, struct dane *dane, struct zasady *zasady, int a);

#endif /* // ZASADY_H_INCLUDED */
