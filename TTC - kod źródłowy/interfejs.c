#include "interfejs.h"
#include "pliki.h"

void wynik2(WINDOW *win, struct dane* dane)
{
    int wynik1=0, wynik2=0, i;
    //Niewykorzystane karty graczy
    for(i=1;i<6;i++)
        if (dane->wylozona[i]==0)
            wynik1++;
    for(i=6;i<11;i++)
        if (dane->wylozona[i]==0)
            wynik2++;
    //Karty na planszy
    for(i=1;i<10;i++)
    {
        if (dane->znak[i]==(char*)177)
            wynik1++;
        else if (dane->znak[i]==(char*)178)
            wynik2++;
    }
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 0, 36, "%d : %d",wynik1,wynik2);
    wattroff(win, COLOR_PAIR(1));
    wrefresh(win);
}

void wynik(WINDOW *win, struct dane* dane, struct zasady* zasady, int tura)
{
    int wynik1=0, wynik2=1, i;
    for(i=0;i<9;i++)
    {
        if (dane->znak[i]==(char*)177)
            wynik1++;
        else
            wynik2++;
    }
    midi_stop(zasady);
	plansza(win, dane);
//	wypisz_karty(win, dane, zasady, tura);
    czysc_linie(win, 0, 0);
    czysc_linie(win, 13, 24);
	wattron(win, COLOR_PAIR(1));
	mvwprintw(win, 15, 36, "%d : %d", wynik1, wynik2);
	if (wynik1>wynik2)
	{
		print_in_middle(win, 17, 0, 0, "Wygrywa gracz pierwszy!");
		midi_start(zasady, "midi\\fan.mid");
	}
	else if (wynik1<wynik2)
	{
		print_in_middle(win, 17, 0, 0, "Wygrywa gracz drugi!");
		midi_start(zasady, "midi\\fan2.mid");
	}
	else
	{
		print_in_middle(win, 17, 0, 0, "Remis!\n");
		midi_start(zasady, "midi\\fan3.mid");
	}
    wrefresh(win);
    wgetch(win);
	wattron(win, A_REVERSE);
	print_in_middle(win, 19, 0, 0, "-> Powrot do menu");
	wattroff(win, A_REVERSE);
    wrefresh(win);
	wgetch(win);
    wattroff(win, COLOR_PAIR(1));
    midi_stop(zasady);
}

void plansza(WINDOW *win, struct dane* dane)
{
    int color;
    int i, j, karta=0;

    for (i=0;i<11;i+=3)
    {
        for(j=31;j<43;j+=6)
        {
            wattron(win, COLOR_PAIR(6));
            mvwprintw(win, i+1, j+4, "|");
            mvwprintw(win, i+2, j+4, "|");
            mvwprintw(win, i+3, j+4, "|");
            wattroff(win, COLOR_PAIR(6));
        }
        i++;
    }

    for (i=0;i<8;i+=3)
    {
        for(j=31;j<46;j+=6)
        {
            wattron(win, COLOR_PAIR(6));
            mvwprintw(win, i+4, j, "---");
            wattroff(win, COLOR_PAIR(6));
        }
        i++;
    }

    for (i=0;i<11;i+=3)
    {
        for(j=31;j<46;j+=6)
        {
            if (dane->znak[karta]==(char*)32) color=4; else if (dane->znak[karta]==(char*)177) color=2; else color=3;
            wattron(win, COLOR_PAIR(color));
            mvwprintw(win, i+1, j, "%c%d%c",dane->znak[karta], dane->karta_plansza_gora[karta], dane->znak[karta]);
            mvwprintw(win, i+2, j, "%d%c%d",dane->karta_plansza_lewo[karta], dane->znak[karta], dane->karta_plansza_prawo[karta]);
            mvwprintw(win, i+3, j, "%c%d%c",dane->znak[karta], dane->karta_plansza_dol[karta], dane->znak[karta]);
            wattroff(win, COLOR_PAIR(color));
            karta++;
        }
        i++;
    }
}

void wypisz_karty(WINDOW *win, struct dane* dane, struct zasady* zasady, int tura)
{
    //2 BLUE 3 RED 4 BLACK
    int j, karta=1, color1, color2, kolumna=23;
    if (zasady->open)
    {
        color1=2;
        color2=3;
    }
    else
        if (tura%2==0)
        {
            color1=2;
            color2=4;
        }
        else
        {
            color1=4;
            color2=3;
        }
    czysc_linie(win, 23, 23);
	wattron(win, COLOR_PAIR(5));
        mvwprintw(win, 23, 23, "Tura gracza 1.");
	wattroff(win, COLOR_PAIR(5));
	wattron(win, COLOR_PAIR(color1));
	mvwprintw(win, 13, 23, "Karty gracza 1:");
	wattroff(win, COLOR_PAIR(color1));
    if (!zasady->open && tura%2==0)
        wgetch(win);
    for(j=0;j<5;j++)
    {
        if (tura%2==0 && !zasady->open)
        {
             if(dane->wylozona[karta]==1)
                color1=4;
             else
                color1=2;
        }
         if (zasady->open)
         {
             if(dane->wylozona[karta]==1)
                color1=4;
             else
                color1=2;
         }
         wattron(win, COLOR_PAIR(color1));
         mvwprintw(win, 14, kolumna, "%c%d%c", 177, dane->karta_gracza_gora[karta], 177);
         mvwprintw(win, 15, kolumna, "%d%c%d", dane->karta_gracza_lewo[karta], 177, dane->karta_gracza_prawo[karta]);
         mvwprintw(win, 16, kolumna, "%c%d%c", 177, dane->karta_gracza_dol[karta], 177);
         wattroff(win, COLOR_PAIR(color1));
         kolumna+=7;
         karta++;
    }

    czysc_linie(win, 23, 23);
	wattron(win, COLOR_PAIR(5));
        mvwprintw(win, 23, 23, "Tura gracza 2.");
	wattroff(win, COLOR_PAIR(5));
    kolumna=23;
    wattron(win, COLOR_PAIR(color2));
    mvwprintw(win, 18, 23, "Karty gracza 2:");
    wattroff(win, COLOR_PAIR(color2));
    if (!zasady->open && tura%2==1)
        wgetch(win);
    for(j=5;j<10;j++)
    {
        if (tura%2==1 && !zasady->open)
        {
            if(dane->wylozona[karta]==1)
                color2=4;
            else
                color2=3;
        }
        if (zasady->open)
        {
            if(dane->wylozona[karta]==1)
                color2=4;
            else
                color2=3;
        }
        wattron(win, COLOR_PAIR(color2));
        mvwprintw(win, 19, kolumna, "%c%d%c", 178, dane->karta_gracza_gora[karta], 178);
        mvwprintw(win, 20, kolumna, "%d%c%d", dane->karta_gracza_lewo[karta], 178, dane->karta_gracza_prawo[karta]);
        mvwprintw(win, 21, kolumna, "%c%d%c", 178, dane->karta_gracza_dol[karta], 178);
        wattroff(win, COLOR_PAIR(color2));
        kolumna+=7;
        karta++;
    }
    wrefresh(win);
}

void idz_pole(WINDOW *win, int wybor)
{
        switch(wybor)
        { //Co 6
            case 1: wmove(win, 2,32); break;
            case 2: wmove(win, 2,38); break;
            case 3: wmove(win, 2,44); break;
            case 4: wmove(win, 6,32); break;
            case 5: wmove(win, 6,38); break;
            case 6: wmove(win, 6,44); break;
            case 7: wmove(win, 10,32); break;
            case 8: wmove(win, 10,38); break;
            case 9: wmove(win, 10,44); break;
        }
    wrefresh(win);
    return;
}

int wybieranie_pola(WINDOW *win, struct dane* dane, struct zasady* zasady, int *karta, int tura)
{
    int wybor=0, w=5, c;
    curs_set(1);
    idz_pole(win, w);
    while(1)
	{	c=wgetch(win);
		switch(c)
		{	case KEY_UP: //GORA
				if(w <= 3)
                    w+=6;
				else
					w-=3;
				break;
			case KEY_DOWN: //DOL
				if(w >= 7)
					w-=6;
				else
					w+=3;
				break;
            case KEY_LEFT: //LEWO
                if (w==1)
                    w=9;
                else
                    w--;
                break;
			case KEY_RIGHT: //PRAWO
                if (w==9)
                    w=1;
                else
                    w++;
				break;
			case 10: //ENTER
                wybor=w;
				break;
			case 27: //ESC
                midi_stop(zasady);
                menu_glowne(dane, zasady);
				break;
			/*case 8: //BACKSPACE
                *karta=wybieranie_karty(win, dane, zasady, tura);
                break;*/
		}
		idz_pole(win, w);
		if(wybor != 0)
            break;
	}
    curs_set(0);
    return wybor-1;
}

void idz_karta(WINDOW *win, int tura, int wybor)
{
    int y;
    if (tura%2==0)
        y=15;
    else
        y=20;
    switch(wybor)
        { //Co 7
            case 1: wmove(win, y,24); break;
            case 2: wmove(win, y,31); break;
            case 3: wmove(win, y,38); break;
            case 4: wmove(win, y,45); break;
            case 5: wmove(win, y,52); break;
        }
    wrefresh(win);
    return;
}

int wybieranie_karty(WINDOW *win, struct dane* dane, struct zasady* zasady, int tura)
{
    int wybor=0, w=3, c;
    curs_set(1);
    idz_karta(win, tura, w);
    while(1)
	{	c=wgetch(win);
		switch(c)
		{
            case KEY_LEFT: //LEWO
                if (w==1)
                    w=5;
                else
                    w--;
                break;
			case KEY_RIGHT: //PRAWO
                if (w==5)
                    w=1;
                else
                    w++;
				break;
			case 10:
                wybor=w;
				break;
			case 27: //ESC
                midi_stop(zasady);
                menu_glowne(dane, zasady);
				break;
		}
		idz_karta(win, tura, w);
		if(wybor != 0)
            break;
	}
    curs_set(0);
    return wybor;
}

void ruch(WINDOW *win, struct dane* dane, struct zasady* zasady, int tura)
{
    int wybor, karta;
    niekarta:
        if(!zasady->order)
        {
            wmove(win, 24, 1);
            wclrtoeol(win);
            wattron(win, COLOR_PAIR(5));
            mvwprintw(win, 24, 23, "Wybierz karte:");
            wattroff(win, COLOR_PAIR(5));
            wrefresh(win);
            karta=wybieranie_karty(win, dane, zasady, tura);
        }
        else
        {
            wmove(win, 24, 1);
            wclrtoeol(win);
            wrefresh(win);
            karta=zasady->order_counter;
            if (tura%2==1)
                zasady->order_counter++;
        }
            if (tura%2!=0)
            {
                karta=karta+5;
            }
            if (dane->wylozona[karta]==1)
            {
                /*wmove(win, 24, 1);
                wclrtoeol(win);
                wattron(win, COLOR_PAIR(5));
                mvwprintw(win, 24, 1, "Karta jest juz na stole!");
                wattroff(win, COLOR_PAIR(5));
                wrefresh(win);
                getch();*/
                goto niekarta;
            }
    niepole:
        wmove(win, 24, 1);
        wclrtoeol(win);
        wattron(win, COLOR_PAIR(5));
        mvwprintw(win, 24, 23, "Wybierz pole:");
        wattroff(win, COLOR_PAIR(5));
        wrefresh(win);
        wybor=wybieranie_pola(win, dane, zasady, &karta, tura);
        if (dane->znak[wybor]!=(char*)32)
        {
            wmove(win, 24, 1);
            wclrtoeol(win);
            wattron(win, COLOR_PAIR(5));
            mvwprintw(win, 24, 23, "Nie mozesz tam polozyc karty!");
            wattroff(win, COLOR_PAIR(5));
            wrefresh(win);
            getch();
            goto niepole;
        }
        if (tura%2==0)
            dane->znak[wybor]=(char*)177;
        else
            dane->znak[wybor]=(char*)178;
        dane->karta_plansza_gora[wybor]=dane->karta_gracza_gora[karta];
        dane->karta_plansza_dol[wybor]=dane->karta_gracza_dol[karta];
        dane->karta_plansza_lewo[wybor]=dane->karta_gracza_lewo[karta];
        dane->karta_plansza_prawo[wybor]=dane->karta_gracza_prawo[karta];
        dane->wylozona[karta]=1;
        wykonaj_zasady(win, dane, zasady, wybor);
}

void przygotuj_karty(struct dane* dane)
{
	int i;

	for(i=0;i<12;i++)
	{
	dane->karta_gracza_gora[i]=losowa(1,9);
	dane->karta_gracza_dol[i]=losowa(1,9);
	dane->karta_gracza_lewo[i]=losowa(1,9);
	dane->karta_gracza_prawo[i]=losowa(1,9);
	}
}

void czysc_plansze(struct dane* dane)
{
	int i;
	for(i=0;i<12;i++)
	{
		dane->karta_plansza_gora[i]=0;
		dane->karta_plansza_dol[i]=0;
		dane->karta_plansza_lewo[i]=0;
		dane->karta_plansza_prawo[i]=0;
        dane->znak[i]=(char*)32;
		dane->wylozona[i]=0;
	}
}

void czysc_linie(WINDOW* win, int start, int stop)
{
    int wiersz;
    for(wiersz=start;wiersz<=stop;wiersz++)
    {
        wmove(win, wiersz, 1);
        wclrtoeol(win);
    }
}

void gra(struct dane* dane, struct zasady* zasady)
{
    int tura;
    WINDOW *win;

	win=newwin(HEIGHT, WIDTH, (24 - HEIGHT) / 2, (80 - WIDTH) / 2);
	keypad(win, TRUE);
        midi_stop(zasady);
    if(zasady->muzyka)
        midi_start(zasady, "midi\\sob.mid");

	przygotuj_karty(dane);
	czysc_plansze(dane);

	for(tura=0;tura<9;tura++)
	{
	    wynik2(win, dane);
        plansza(win, dane);
        czysc_linie(win, 13, 21);
        wypisz_karty(win, dane, zasady, tura);
        wrefresh(win);
        ruch(win, dane, zasady, tura);
	}
	wynik(win, dane, zasady, tura);
    if(zasady->muzyka)
        midi_stop(zasady);
    menu_glowne(dane, zasady);
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string)
{
    int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	mvwprintw(win, y, x, "%s", string);
	refresh();
}

char *choices3[] = {
            "Napisz do mnie",
			"-> Powrot do menu",
		  };

int n_choices3 = sizeof(choices3) / sizeof(char *);

void print_autor(WINDOW *win, int highlight)
{
	int x=13, y=17, i;
	box(win, 0, 0);
	wattron(win, COLOR_PAIR(5));
    mvwprintw(win, 11, 13, "O autorze:");
    mvwprintw(win, 13, 13, "Lukasz Wieczorek");
    mvwprintw(win, 14, 13, "Informatyka WIiZ");
    mvwprintw(win, 15, 13, "wieczorek1990@gmail.com");
    mvwprintw(win, 20, 21, "Podziekowania dla Bryki za testy :-)");
    mvwprintw(win, 11, 50, "O sterowaniu:");
    mvwprintw(win, 13, 50, "Dostepne klawisze to:");
    mvwprintw(win, 14, 50, "ENTER, STRZALKI.");
    mvwprintw(win, 15, 50, "A podczas gry takze ESC.");
    x=29;
	for(i = 0; i < n_choices3; ++i)
	{	if(highlight == i + 1)
		{	wattron(win, A_REVERSE);
			mvwprintw(win, y, x, "%s", choices3[i]);
			wattroff(win, A_REVERSE);
		}
		else
			mvwprintw(win, y, x, "%s", choices3[i]);
		++y;
	}
	wattroff(win, COLOR_PAIR(5));
	wrefresh(win);
}

void autor(struct dane* dane, struct zasady* zasady)
{
    WINDOW *win;
	int highlight=1, wybor, c;
	win=newwin(HEIGHT, WIDTH, (24 - HEIGHT) / 2, (80 - WIDTH) / 2);
	keypad(win, TRUE);
	menu:
    print_logo(win);
	print_autor(win, highlight);
	wybor=0;
	while(1)
	{	c = wgetch(win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices3;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices3)
					highlight = 1;
				else
					++highlight;
				break;
			case 10:
				wybor = highlight;
				break;
		}
		print_autor(win, highlight);
		if(wybor != 0)
			break;
	}
    wattron(win, COLOR_PAIR(3));
    wclrtobot(win);
    switch(wybor)
	{
	    case 1: ShellExecute(NULL,"open", "mailto:wieczorek1990@gmail.com", NULL, NULL, SW_SHOW); break;
		case 2: menu_glowne(dane, zasady); return; break;
	}
    wattroff(win, COLOR_PAIR(3));
	wrefresh(win);
    goto menu;
}

char *choices[] = {
			"Nowa gra",
			"Wybierz zasady gry",
			"Nauka gry",
			"O autorze i sterowaniu",
			"Wyjscie"
		  };

int n_choices = sizeof(choices) / sizeof(char *);

void print_logo(WINDOW *win)
{
    wattron(win, COLOR_PAIR(1));
    print_in_middle(win, 1, 0, 0,"____         ____        \n");
    print_in_middle(win, 2, 0, 0," /  _ '  /_   /  _ '_ _/ \n");
    print_in_middle(win, 3, 0, 0,"(  / //)((-  (  / /(/(/  \n");
    print_in_middle(win, 4, 0, 0,"     /                   \n");
    print_in_middle(win, 5, 0, 0,"\n");
    print_in_middle(win, 6, 0, 0,"    _             \n");
    print_in_middle(win, 7, 0, 0,"   / )     _   /_ \n");
    print_in_middle(win, 8, 0, 0,"  (__()/)_) ()((- \n");
	wattroff(win, COLOR_PAIR(1));
}

void print_menu(WINDOW *menu_win, int highlight)
{
	int x=29, y=13, i;
    print_logo(menu_win);
	box(menu_win, 0, 0);
    wattron(menu_win, COLOR_PAIR(5));
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1)
		{	wattron(menu_win, A_REVERSE);
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
    wattroff(menu_win, COLOR_PAIR(5));
	wrefresh(menu_win);
}

char *choices2[] = {
			"Same",
			"Plus",
			"Minus",
			"Open",
			"Order",
			"Combo",
			//"Wall",
			//"Set Wall",
			"Zapisz ustawienia do pliku",
			"Wczytaj ustawienia z pliku",
			"Wylacz/Wlacz dzwiek",
			"Aktualne ustawienia",
			"-> Powrot do menu",
		  };

int n_choices2 = sizeof(choices2) / sizeof(char *);

void print_settings(WINDOW *win, int highlight)
{
	int x=13, y=12, i;
	box(win, 0, 0);
	wattron(win, COLOR_PAIR(5));
    mvwprintw(win, 10, 13, "Ustawienia:\n");
	for(i = 0; i < n_choices2; ++i)
	{	if(highlight == i + 1)
		{	wattron(win, A_REVERSE);
			mvwprintw(win, y, x, "%s", choices2[i]);
			wattroff(win, A_REVERSE);
		}
		else
			mvwprintw(win, y, x, "%s", choices2[i]);
		++y;
	}
	wattroff(win, COLOR_PAIR(5));
	wrefresh(win);
}

void ustawienia(struct dane* dane, struct zasady* zasady)
{
    WINDOW *settings_win;
	int highlight=1, wybor, c;
	settings_win=newwin(HEIGHT, WIDTH, (24 - HEIGHT) / 2, (80 - WIDTH) / 2);
	keypad(settings_win, TRUE);
	menu:
    print_logo(settings_win);
	print_settings(settings_win, highlight);
	wybor=0;
	while(1)
	{	c = wgetch(settings_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices2;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices2)
					highlight = 1;
				else
					++highlight;
				break;
			case 10:
				wybor = highlight;
				break;
		}
		print_settings(settings_win, highlight);
		if(wybor != 0)
			break;
	}
    wattron(settings_win, COLOR_PAIR(3));
    wclrtobot(settings_win);
	switch(wybor)
	{
		case 1: wmove(settings_win, 12, 1);
                wclrtobot(settings_win);
                zasady->same=!zasady->same;
				if (zasady->same)
					mvwprintw(settings_win, 12, 45, "Same wlaczone");
				else
					mvwprintw(settings_win, 12, 45, "Same wylaczone");
				break;
		case 2: wmove(settings_win, 12, 1);
                wclrtobot(settings_win);
                zasady->plus=!zasady->plus;
				if (zasady->plus)
					mvwprintw(settings_win, 13, 45, "Plus wlaczone");
				else
					mvwprintw(settings_win, 13, 45, "Plus wylaczone");
				break;
		case 3: wmove(settings_win, 12, 1);
                wclrtobot(settings_win);
                zasady->minus=!zasady->minus;
				if (zasady->minus)
					mvwprintw(settings_win, 14, 45, "Minus wlaczone");
				else
					mvwprintw(settings_win, 14, 45, "Minus wylaczone");
				break;
		case 4: wmove(settings_win, 12, 1);
                wclrtobot(settings_win);
                zasady->open=!zasady->open;
				if (zasady->open)
					mvwprintw(settings_win, 15, 45, "Open wlaczone");
				else
					mvwprintw(settings_win, 15, 45, "Open wylaczone");
				break;
		case 5: wmove(settings_win, 12, 1);
                wclrtobot(settings_win);
                zasady->order=!zasady->order;
				if (zasady->order)
					mvwprintw(settings_win, 16, 45, "Order wlaczone");
				else
					mvwprintw(settings_win, 16, 45, "Order wylaczone");
				break;
		case 6: wmove(settings_win, 12, 1);
                wclrtobot(settings_win);
                zasady->combo=!zasady->combo;
				if (zasady->combo)
					mvwprintw(settings_win, 17, 45, "Combo wlaczone");
				else
					mvwprintw(settings_win, 17, 45, "Combo wylaczone");
				break;
		/*case 7: wmove(settings_win, 12, 1);
                wclrtobot(settings_win);
                zasady->wall=!zasady->wall;
				if (zasady->wall)
					mvwprintw(settings_win, 18, 45, "Wall wlaczone");
				else
					mvwprintw(settings_win, 18, 45, "Wall wylaczone");
				break;
		case 8: wmove(settings_win, 12, 1);
                wclrtobot(settings_win);
                zasady->set_wall=!zasady->set_wall;
				if (zasady->set_wall)
				{
				    while(true)
				    {   wmove(settings_win, 12, 1);
                        wclrtoeol(settings_win);
                        mvwprintw(settings_win, 12, 1, "Jaka wartosc ma miec sciana?");
                        curs_set(1); echo();
                        mvwscanw(settings_win, 12, 30, "%d", &dane->wall_value);
                        if (dane->wall_value>0 && dane->wall_value<11)
                            break;
                        else
                        {
                            mvwprintw(settings_win, 13, 1, "Podaj wartosc z zakresu od 1 do 10 ");
                        }
				    }
					mvwprintw(settings_win, 19, 45, "Set Wall = %d wlaczone", dane->wall_value);
				}
				else
				{
				    wmove(settings_win, 19, 45);
                    wclrtoeol(settings_win);
					mvwprintw(settings_win, 19, 45, "Set Wall wylaczone");
				}
				curs_set(0); noecho();
				wmove(settings_win, 12, 1);
                wclrtoeol(settings_win);
                wmove(settings_win, 13, 1);
                wclrtoeol(settings_win);
				break;*/
        case 7: wmove(settings_win, 12, 1);
                wclrtobot(settings_win);
                zapis(settings_win, dane, zasady);
                mvwprintw(settings_win, 18, 45, "Zapisalem");
                break;
		case 8: wmove(settings_win, 12, 1);
                wclrtobot(settings_win);
                odczyt(settings_win, dane, zasady);
                mvwprintw(settings_win, 19, 45, "Wczytalem");
                break;
 		case 9: wmove(settings_win, 12, 1);
                wclrtobot(settings_win);
                zasady->muzyka=!zasady->muzyka;
				if (zasady->muzyka)
				{
					mvwprintw(settings_win, 20, 45, "Muzyka wlaczona");
                    midi_start(zasady, "midi\\fh.mid");
				}
				else
				{
					mvwprintw(settings_win, 20, 45, "Muzyka wylaczona");
                    midi_stop(zasady);
				}
				break;
		case 10: wmove(settings_win, 12, 1);
                wclrtobot(settings_win);
				if (zasady->same)
					mvwprintw(settings_win, 12, 45, "Same wlaczone");
				else
					mvwprintw(settings_win, 12, 45, "Same wylaczone");
				if (zasady->plus)
					mvwprintw(settings_win, 13, 45, "Plus wlaczone");
				else
					mvwprintw(settings_win, 13, 45, "Plus wylaczone");
				if (zasady->minus)
					mvwprintw(settings_win, 14, 45, "Minus wlaczone");
				else
					mvwprintw(settings_win, 14, 45, "Minus wylaczone");
				if (zasady->open)
					mvwprintw(settings_win, 15, 45, "Open wlaczone");
				else
					mvwprintw(settings_win, 15, 45, "Open wylaczone");
				if (zasady->order)
					mvwprintw(settings_win, 16, 45, "Order wlaczone");
				else
					mvwprintw(settings_win, 16, 45, "Order wylaczone");
				if (zasady->combo)
					mvwprintw(settings_win, 17, 45, "Combo wlaczone");
				else
					mvwprintw(settings_win, 17, 45, "Combo wylaczone");
				/*if (zasady->wall)
					mvwprintw(settings_win, 18, 45, "Wall wlaczone");
				else
					mvwprintw(settings_win, 18, 45, "Wall wylaczone");
				if (zasady->set_wall)
					mvwprintw(settings_win, 19, 45, "Set Wall wlaczone");
				else
					mvwprintw(settings_win, 19, 45, "Set Wall wylaczone");*/
				if (zasady->muzyka)
					mvwprintw(settings_win, 20, 45, "Muzyka wlaczona");
				else
					mvwprintw(settings_win, 20, 45, "Muzyka wylaczona");
                break;
		case 11: menu_glowne(dane, zasady); return; break;
	}
	wattroff(settings_win, COLOR_PAIR(3));
	wrefresh(settings_win);
    goto menu;
}


void menu_glowne(struct dane* dane, struct zasady* zasady)
{
    WINDOW *menu_win;
	int highlight=1, wybor, c;
	menu_win=newwin(HEIGHT, WIDTH, (24 - HEIGHT) / 2, (80 - WIDTH) / 2);
	keypad(menu_win, TRUE);
	menu:
	wybor=0;
    if(zasady->muzyka)
        midi_start(zasady, "midi\\fh.mid");
	print_menu(menu_win, highlight);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else
					++highlight;
				break;
			case 10:
				wybor = highlight;
				break;
		}
		print_menu(menu_win, highlight);
		if(wybor != 0)
			break;
	}
	switch(wybor)
	{
		case 1: if(zasady->muzyka)
                    midi_stop(zasady);
                gra(dane, zasady); break;
		case 2: ustawienia(dane, zasady); break;
		case 3: www(); break;
		case 4: autor(dane, zasady); break;
		case 5: if(zasady->muzyka)
                    midi_stop(zasady);
                exit(0); break;
	}
	goto menu;
}

void wlacz_kolory()
{
    start_color();
    init_color(COLOR_BLACK, 100, 100, 130);
    init_color(COLOR_YELLOW, 1000, 800, 0);
    init_color(COLOR_RED, 1000, 400, 200);
    init_color(COLOR_GREEN, 0, 500, 0);
    init_color(COLOR_BLUE, 200, 400, 1000);
    init_color(COLOR_MAGENTA, 400, 400, 400);
    init_color(COLOR_WHITE, 600, 600, 600);
    assume_default_colors(COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
}

void midi_start(struct zasady* zasady, char* midi)
{
    zasady->mciOpenParms.lpstrDeviceType="sequencer";
    zasady->mciOpenParms.lpstrElementName=midi;
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,(DWORD)&zasady->mciOpenParms);
    MCI_PLAY_PARMS mciPlayParms;
    mciSendCommand(zasady->mciOpenParms.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)&mciPlayParms);
}

void midi_stop(struct zasady* zasady)
{
    if (zasady->mciOpenParms.wDeviceID)
        mciSendCommand(zasady->mciOpenParms.wDeviceID, MCI_CLOSE, 0, 0);
    zasady->mciOpenParms.wDeviceID=0;
}

void www()
{
    ShellExecute(NULL, "open", "http://tripletriad.wikia.com/wiki/Triple_Triad:Triple_Triad_101", NULL, NULL, SW_SHOW);
    ShellExecute(NULL, "open", "http://www.ttadvance.ca/tutorial.php", NULL, NULL, SW_SHOW);
    ShellExecute(NULL, "open", "http://www.tripletriadextreme.com/GameInfo/What-Is-How-To-Play-Triple-Triad.aspx", NULL, NULL, SW_SHOW);
}
