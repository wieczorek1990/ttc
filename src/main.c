//      TripleTriadConsole.c
//
//      Copyright 2010 £ukasz Wieczorek <wieczorek1990@gmail.com>
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

#include <time.h>
#include "struktury.h"
#include "pliki.h"
#include "zasady.h"
#include "interfejs.h"

int main(int argc, char** argv)
{
    struct zasady zasady;
    struct dane dane;
    zasady.same=1, zasady.plus=1; zasady.minus=1;
    zasady.open=0; zasady.order=0; zasady.order_counter=1;
    zasady.wall=0; zasady.combo=1;
    zasady.muzyka=1;
    dane.zmiana0=0; dane.zmiana1=0; dane.zmiana2=0; dane.zbilem=0; dane.wall_value=9;
    odczyt(stdscr, &dane, &zasady);
	srand(time(0));
    initscr();
    wlacz_kolory();
    noecho();
    cbreak();
    curs_set(0);
    menu_glowne(&dane, &zasady);
    endwin();
	return 0;
}
