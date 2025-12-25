#ifndef PLIKI_H_INCLUDED
#define PLIKI_H_INCLUDED

#include "struktury.h"

int zapis(WINDOW *win, struct dane* dane, struct zasady* zasady);
int odczyt(WINDOW *win, struct dane* dane, struct zasady* zasady);

#endif // PLIKI_H_INCLUDED
