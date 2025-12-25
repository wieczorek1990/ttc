#include "zasady.h"

int losowa(int min, int max)
{
    return (min + (rand() % (max - min + 1)));
}

void combo_zmiana(WINDOW* win, struct dane* dane, struct zasady* zasady, int zmiana0, int zmiana1, int zmiana2)
{
    dane->zmiana0=zmiana0;
    dane->zmiana1=zmiana1;
    dane->zmiana2=zmiana2;
    if (zasady->combo)
       combo(win, dane, zasady);
}

void gora(WINDOW* win, struct dane* dane, struct zasady* zasady, int a)
{
	int b;
	b=a-3;
	if ((b>=0) && (b<=5) && (dane->karta_plansza_dol[b]<dane->karta_plansza_gora[a]) && (dane->karta_plansza_dol[b]!=0) && (dane->znak[a]!=dane->znak[b]))
	{
		dane->znak[b]=dane->znak[a];
		dane->zbilem=1;
	}
}

void dol(WINDOW* win, struct dane* dane, struct zasady* zasady, int a)
{
	int b;
	b=a+3;
	if ((b>=3) && (b<=8) && (dane->karta_plansza_gora[b]<dane->karta_plansza_dol[a]) && (dane->karta_plansza_gora[b]!=0)  && (dane->znak[a]!=dane->znak[b]))
	{
		dane->znak[b]=dane->znak[a];
        dane->zbilem=1;
	}
}

void lewo(WINDOW* win, struct dane* dane, struct zasady* zasady, int a)
{
	int b;
	b=a-1;
	if ((b>=0) && (b<=7) && (dane->karta_plansza_prawo[b]<dane->karta_plansza_lewo[a]) && (dane->karta_plansza_prawo[b]!=0)  && (dane->znak[a]!=dane->znak[b]))
	{
		dane->znak[b]=dane->znak[a];
        dane->zbilem=1;
	}
}

void prawo(WINDOW* win, struct dane* dane, struct zasady* zasady, int a)
{
	int b;
	b=a+1;
	if ((b>=1) && (b<=8) && (dane->karta_plansza_lewo[b]<dane->karta_plansza_prawo[a]) && (dane->karta_plansza_lewo[b]!=0)  && (dane->znak[a]!=dane->znak[b]))
	{
		dane->znak[b]=dane->znak[a];
		dane->zbilem=1;
	}
}


void bicie(WINDOW* win, struct dane* dane, struct zasady* zasady, int a)
{
	switch (a)
	{
        case 0: dol(win, dane, zasady, a); prawo(win, dane, zasady, a); break;
        case 1: dol(win, dane, zasady, a); lewo(win, dane, zasady, a); prawo(win, dane, zasady, a); break;
        case 2: dol(win, dane, zasady, a); lewo(win, dane, zasady, a); break;
        case 3: gora(win, dane, zasady, a); dol(win, dane, zasady, a); prawo(win, dane, zasady, a); break;
        case 4: gora(win, dane, zasady, a); dol(win, dane, zasady, a); lewo(win, dane, zasady, a); prawo(win, dane, zasady, a); break;
        case 5: gora(win, dane, zasady, a); dol(win, dane, zasady, a); lewo(win, dane, zasady, a); break;
        case 6: gora(win, dane, zasady, a); prawo(win, dane, zasady, a); break;
        case 7: gora(win, dane, zasady, a); lewo(win, dane, zasady, a); prawo(win, dane, zasady, a); break;
        case 8: gora(win, dane, zasady, a); lewo(win, dane, zasady, a); break;
	}
}

int swoje_gora(struct dane* dane, int a)
{
	int b;
	b=a-3;
	if ((b>=0) && (b<=5) && (dane->karta_plansza_dol[b]!=0) && (dane->znak[a]==dane->znak[b]))
        return 1;
	else
        return 0;
}

int swoje_dol(struct dane* dane, int a)
{
	int b;
	b=a+3;
	if ((b>=3) && (b<=8) && (dane->karta_plansza_gora[b]!=0)  && (dane->znak[a]==dane->znak[b]))
        return 1;
	else
        return 0;
}

int swoje_lewo(struct dane* dane, int a)
{
	int b;
	b=a-1;
	if ((b>=0) && (b<=7) && (dane->karta_plansza_prawo[b]!=0)  && (dane->znak[a]==dane->znak[b]))
        return 1;
	else
        return 0;
}

int swoje_prawo(struct dane* dane, int a)
{
	int b;
	b=a+1;
	if ((b>=1) && (b<=8) && (dane->karta_plansza_lewo[b]!=0)  && (dane->znak[a]==dane->znak[b]))
        return 1;
	else
        return 0;
}

int sgora(struct dane* dane, int a)
{
	int w=0, b;
	b=a-3;
	if ((b>=0) && (b<=5) && (dane->karta_plansza_dol[b]==dane->karta_plansza_gora[a]) && (dane->karta_plansza_dol[b]!=0))
		w=1;
	return w;
}

int sdol(struct dane* dane, int a)
{
	int w=0, b;
	b=a+3;
	if ((b>=3) && (b<=8) && (dane->karta_plansza_gora[b]==dane->karta_plansza_dol[a]) && (dane->karta_plansza_gora[b]!=0))
		w=1;
	return w;
}

int slewo(struct dane* dane, int a)
{
	int w=0, b;
	b=a-1;
	if ((b>=0) && (b<=7) && (dane->karta_plansza_prawo[b]==dane->karta_plansza_lewo[a]) && (dane->karta_plansza_prawo[b]!=0))
		w=1;
	return w;
}

int sprawo(struct dane* dane, int a)
{
	int w=0, b;
	b=a+1;
	if ((b>=1) && (b<=8) && (dane->karta_plansza_lewo[b]==dane->karta_plansza_prawo[a]) && (dane->karta_plansza_lewo[b]!=0))
		w=1;
	return w;
}

int pgora(struct dane* dane, int a)
{
	int w, b;
	b=a-3;
	if ((b>=0) && (b<=5) && (dane->karta_plansza_dol[b]!=0))
	{
		w=dane->karta_plansza_dol[b]+dane->karta_plansza_gora[a];
		return w;
	}
	else
		return 0;
}

int pdol(struct dane* dane, int a)
{
	int w, b;
	b=a+3;
	if ((b>=3) && (b<=8) && (dane->karta_plansza_gora[b]!=0))
	{
		w=dane->karta_plansza_gora[b]+dane->karta_plansza_dol[a];
		return w;
	}
	else
		return 0;
}

int plewo(struct dane* dane, int a)
{
	int w, b;
	b=a-1;
	if ((b>=0) && (b<=7) && (dane->karta_plansza_prawo[b]!=0))
	{
		w=dane->karta_plansza_prawo[b]+dane->karta_plansza_lewo[a];
		return w;
	}
	else
		return 0;
}

int pprawo(struct dane* dane, int a)
{
	int w, b;
	b=a+1;
	if ((b>=1) && (b<=8) && (dane->karta_plansza_lewo[b]!=0))
	{
		w=dane->karta_plansza_lewo[b]+dane->karta_plansza_prawo[a];
		return w;
	}
	else
		return 0;
}

void plus_change(WINDOW *win, struct dane* dane, struct zasady* zasady, int a, int b, int c)
{
    dane->znak[b]=dane->znak[c]=dane->znak[a];
    wmove(win, 24, 1);
    wclrtoeol(win);
    wattron(win, COLOR_PAIR(1));
	mvwprintw(win, 24, 1, "Plus!");
	wattroff(win, COLOR_PAIR(1));
	wrefresh(win);
	wgetch(win);
    combo_zmiana(win, dane, zasady, a, b, c);
}

void plus(WINDOW *win, struct dane* dane, struct zasady* zasady, int a)
{
	switch (a)
	{
	case 0: if ((pdol(dane, a) == pprawo(dane, a)) && (pdol(dane, a)*pprawo(dane, a) != 0) && (swoje_dol(dane, a)+swoje_prawo(dane, a)!=2))
				plus_change(win, dane, zasady, 0,1,3);
				break;
	case 1: if ((pdol(dane, a) == plewo(dane, a)) && (pdol(dane, a)*plewo(dane, a) != 0) && (swoje_dol(dane, a)+swoje_lewo(dane, a)!=2))
				plus_change(win, dane, zasady, 1,0,4);
			if ((pdol(dane, a) == pprawo(dane, a)) && (pdol(dane, a)*pprawo(dane, a) != 0) && (swoje_dol(dane, a)+swoje_prawo(dane, a)!=2))
				plus_change(win, dane, zasady, 1,2,4);
			if ((plewo(dane, a) == pprawo(dane, a)) && (plewo(dane, a)*pprawo(dane, a) != 0) && (swoje_lewo(dane, a)+swoje_prawo(dane, a)!=2))
				plus_change(win, dane, zasady, 1,0,2);
				break;
	case 2: if ((pdol(dane, a) == plewo(dane, a)) && (pdol(dane, a)*plewo(dane, a) != 0) && (swoje_dol(dane, a)+swoje_lewo(dane, a)!=2))
				plus_change(win, dane, zasady, 2,1,5);
				break;
	case 3: if ((pdol(dane, a) == pgora(dane, a)) && (pdol(dane, a)*pgora(dane, a) != 0) && (swoje_dol(dane, a)+swoje_gora(dane, a)!=2))
				plus_change(win, dane, zasady, 3,0,6);
			if ((pdol(dane, a) == pprawo(dane, a)) && (pdol(dane, a)*pprawo(dane, a) != 0) && (swoje_dol(dane, a)+swoje_prawo(dane, a)!=2))
				plus_change(win, dane, zasady, 3,4,6);
			if ((pprawo(dane, a) == pgora(dane, a)) && (pgora(dane, a)*pprawo(dane, a) != 0) && (swoje_prawo(dane, a)+swoje_gora(dane, a)!=2))
				plus_change(win, dane, zasady, 3,0,4);
				break;
	case 4: if ((pdol(dane, a) == plewo(dane, a)) && (pdol(dane, a)*plewo(dane, a) != 0) && (swoje_dol(dane, a)+swoje_lewo(dane, a)!=2))
				plus_change(win, dane, zasady, 4,3,7);
			if ((pdol(dane, a) == pgora(dane, a)) && (pdol(dane, a)*pgora(dane, a) != 0) && (swoje_dol(dane, a)+swoje_gora(dane, a)!=2))
				plus_change(win, dane, zasady, 4,1,7);
			if ((pdol(dane, a) == pprawo(dane, a)) && (pdol(dane, a)*pprawo(dane, a) !=0) && (swoje_dol(dane, a)+swoje_prawo(dane, a)!=2))
				plus_change(win, dane, zasady, 4,5,7);
			if ((plewo(dane, a) == pgora(dane, a)) && (plewo(dane, a)*pgora(dane, a) !=0) && (swoje_gora(dane, a)+swoje_lewo(dane, a)!=2))
				plus_change(win, dane, zasady, 4,1,3);
			if ((plewo(dane, a) == pprawo(dane, a)) && (plewo(dane, a)*pprawo(dane, a) != 0) && (swoje_lewo(dane, a)+swoje_prawo(dane, a)!=2))
				plus_change(win, dane, zasady, 4,3,5);
			if ((pprawo(dane, a) == pgora(dane, a)) && (pprawo(dane, a)*pgora(dane, a)!=0) && (swoje_prawo(dane, a)+swoje_gora(dane, a)!=2))
				plus_change(win, dane, zasady, 4,1,5);
			break;
	case 5: if ((pdol(dane, a) == plewo(dane, a)) && (pdol(dane, a)*plewo(dane, a) != 0) && (swoje_dol(dane, a)+swoje_lewo(dane, a)!=2))
				plus_change(win, dane, zasady, 5,4,8);
			if ((pdol(dane, a) == pgora(dane, a)) && (pdol(dane, a)*pgora(dane, a) != 0) && (swoje_dol(dane, a)+swoje_gora(dane, a)!=2))
				plus_change(win, dane, zasady, 5,2,8);
			if  ((plewo(dane, a) == pgora(dane, a)) && (plewo(dane, a)*pgora(dane, a) != 0) && (swoje_gora(dane, a)+swoje_lewo(dane, a)!=2))
				plus_change(win, dane, zasady, 5,2,4);
			break;
	case 6: if ((pprawo(dane, a) == pgora(dane, a)) && (pgora(dane, a)*pprawo(dane, a) != 0) && (swoje_prawo(dane, a)+swoje_gora(dane, a)!=2))
				plus_change(win, dane, zasady, 6,3,7);
	case 7: if (((pgora(dane, a) == plewo(dane, a)) && (pgora(dane, a)*plewo(dane, a)) != 0) && (swoje_gora(dane, a)+swoje_lewo(dane, a)!=2))
				plus_change(win, dane, zasady, 7,4,6);
			if ((pprawo(dane, a) == pgora(dane, a)) && (pprawo(dane, a)*pgora(dane, a) != 0) && (swoje_prawo(dane, a)+swoje_gora(dane, a)!=2))
				plus_change(win, dane, zasady, 7,4,8);
			if ((plewo(dane, a) == pprawo(dane, a)) && (plewo(dane, a)*pprawo(dane, a) != 0) && (swoje_lewo(dane, a)+swoje_prawo(dane, a)!=2))
				plus_change(win, dane, zasady, 7,6,8);
			break;
	case 8: if ((pgora(dane, a) == plewo(dane, a)) && (pgora(dane, a)*plewo(dane, a) != 0) && (swoje_gora(dane, a)+swoje_lewo(dane, a)!=2))
				plus_change(win, dane, zasady, 8,5,7);
				break;
	}
}

int mgora(struct dane* dane, int a)
{
	int w, b;
	b=a-3;
	if ((b>=0) && (b<=5) && (dane->karta_plansza_dol[b]!=0))
	{
		w=dane->karta_plansza_dol[b]-dane->karta_plansza_gora[a];
		return abs(w);
	}
	else
		return 0;
}

int mdol(struct dane* dane, int a)
{
	int w, b;
	b=a+3;
	if ((b>=3) && (b<=8) && (dane->karta_plansza_gora[b]!=0))
	{
		w=dane->karta_plansza_gora[b]-dane->karta_plansza_dol[a];
		return abs(w);
	}
	else
		return 0;
}

int mlewo(struct dane* dane, int a)
{
	int w, b;
	b=a-1;
	if ((b>=0) && (b<=7) && (dane->karta_plansza_prawo[b]!=0))
	{
		w=dane->karta_plansza_prawo[b]-dane->karta_plansza_lewo[a];
		return abs(w);
	}
	else
		return 0;
}

int mprawo(struct dane* dane, int a)
{
	int w, b;
	b=a+1;
	if ((b>=1) && (b<=8) && (dane->karta_plansza_lewo[b]!=0))
	{
		w=dane->karta_plansza_lewo[b]-dane->karta_plansza_prawo[a];
		return abs(w);
	}
	else
		return 0;
}

void minus_change(WINDOW *win, struct dane* dane, struct zasady* zasady, int a, int b, int c)
{
    dane->znak[b]=dane->znak[c]=dane->znak[a];
    wmove(win, 24, 1);
    wclrtoeol(win);
    wattron(win, COLOR_PAIR(1));
	mvwprintw(win, 24, 1, "Minus!");
	wattroff(win, COLOR_PAIR(1));
	wrefresh(win);
	wgetch(win);
    combo_zmiana(win, dane, zasady, a, b, c);
}

void minus(WINDOW *win, struct dane* dane, struct zasady* zasady, int a)
{
	switch (a)
	{
	case 0: if ((mdol(dane, a) == mprawo(dane, a)) && (mdol(dane, a)*mprawo(dane, a) != 0) && (swoje_dol(dane, a)+swoje_prawo(dane, a)!=2))
				minus_change(win, dane, zasady, 0,1,3);
				break;
	case 1: if ((mdol(dane, a) == mlewo(dane, a)) && (mdol(dane, a)*mlewo(dane, a) != 0) && (swoje_dol(dane, a)+swoje_lewo(dane, a)!=2))
				minus_change(win, dane, zasady, 1,0,4);
			if ((mdol(dane, a) == mprawo(dane, a)) && (mdol(dane, a)*mprawo(dane, a) != 0) && (swoje_dol(dane, a)+swoje_prawo(dane, a)!=2))
				minus_change(win, dane, zasady, 1,2,4);
			if ((mlewo(dane, a) == mprawo(dane, a)) && (mlewo(dane, a)*mprawo(dane, a) != 0) && (swoje_lewo(dane, a)+swoje_prawo(dane, a)!=2))
				minus_change(win, dane, zasady, 1,0,2);
				break;
	case 2: if ((mdol(dane, a) == mlewo(dane, a)) && (mdol(dane, a)*mlewo(dane, a) != 0) && (swoje_dol(dane, a)+swoje_lewo(dane, a)!=2))
				minus_change(win, dane, zasady, 2,1,5);
				break;
	case 3: if ((mdol(dane, a) == mgora(dane, a)) && (mdol(dane, a)*mgora(dane, a) != 0) && (swoje_dol(dane, a)+swoje_gora(dane, a)!=2))
				minus_change(win, dane, zasady, 3,0,6);
			if ((mdol(dane, a) == mprawo(dane, a)) && (mdol(dane, a)*mprawo(dane, a) != 0) && (swoje_dol(dane, a)+swoje_prawo(dane, a)!=2))
				minus_change(win, dane, zasady, 3,4,6);
			if ((mprawo(dane, a) == mgora(dane, a)) && (mgora(dane, a)*mprawo(dane, a) != 0) && (swoje_prawo(dane, a)+swoje_gora(dane, a)!=2))
				minus_change(win, dane, zasady, 3,0,4);
				break;
	case 4: if ((mdol(dane, a) == mlewo(dane, a)) && (mdol(dane, a)*mlewo(dane, a) != 0) && (swoje_dol(dane, a)+swoje_lewo(dane, a)!=2))
				minus_change(win, dane, zasady, 4,3,7);
			if ((mdol(dane, a) == mgora(dane, a)) && (mdol(dane, a)*mgora(dane, a) != 0) && (swoje_dol(dane, a)+swoje_gora(dane, a)!=2))
				minus_change(win, dane, zasady, 4,1,7);
			if ((mdol(dane, a) == mprawo(dane, a)) && (mdol(dane, a)*mprawo(dane, a) !=0) && (swoje_dol(dane, a)+swoje_prawo(dane, a)!=2))
				minus_change(win, dane, zasady, 4,5,7);
			if ((mlewo(dane, a) == mgora(dane, a)) && (mlewo(dane, a)*mgora(dane, a) !=0) && (swoje_gora(dane, a)+swoje_lewo(dane, a)!=2))
				minus_change(win, dane, zasady, 4,1,3);
			if ((mlewo(dane, a) == mprawo(dane, a)) && (mlewo(dane, a)*mprawo(dane, a) != 0) && (swoje_lewo(dane, a)+swoje_prawo(dane, a)!=2))
				minus_change(win, dane, zasady, 4,3,5);
			if ((mprawo(dane, a) == mgora(dane, a)) && (mprawo(dane, a)*mgora(dane, a)!=0) && (swoje_prawo(dane, a)+swoje_gora(dane, a)!=2))
				minus_change(win, dane, zasady, 4,1,5);
			break;
	case 5: if ((mdol(dane, a) == mlewo(dane, a)) && (mdol(dane, a)*mlewo(dane, a) != 0) && (swoje_dol(dane, a)+swoje_lewo(dane, a)!=2))
				minus_change(win, dane, zasady, 5,4,8);
			if ((mdol(dane, a) == mgora(dane, a)) && (mdol(dane, a)*mgora(dane, a) != 0) && (swoje_dol(dane, a)+swoje_gora(dane, a)!=2))
				minus_change(win, dane, zasady, 5,2,8);
			if  ((mlewo(dane, a) == mgora(dane, a)) && (mlewo(dane, a)*mgora(dane, a) != 0) && (swoje_gora(dane, a)+swoje_lewo(dane, a)!=2))
				minus_change(win, dane, zasady, 5,2,4);
			break;
	case 6: if ((mprawo(dane, a) == mgora(dane, a)) && (mgora(dane, a)*mprawo(dane, a) != 0) && (swoje_prawo(dane, a)+swoje_gora(dane, a)!=2))
				minus_change(win, dane, zasady, 6,3,7);
	case 7: if (((mgora(dane, a) == mlewo(dane, a)) && (mgora(dane, a)*mlewo(dane, a)) != 0) && (swoje_gora(dane, a)+swoje_lewo(dane, a)!=2))
				minus_change(win, dane, zasady, 7,4,6);
			if ((mprawo(dane, a) == mgora(dane, a)) && (mprawo(dane, a)*mgora(dane, a) != 0) && (swoje_prawo(dane, a)+swoje_gora(dane, a)!=2))
				minus_change(win, dane, zasady, 7,4,8);
			if ((mlewo(dane, a) == mprawo(dane, a)) && (mlewo(dane, a)*mprawo(dane, a) != 0) && (swoje_lewo(dane, a)+swoje_prawo(dane, a)!=2))
				minus_change(win, dane, zasady, 7,6,8);
			break;
	case 8: if ((mgora(dane, a) == mlewo(dane, a)) && (mgora(dane, a)*mlewo(dane, a) != 0) && (swoje_gora(dane, a)+swoje_lewo(dane, a)!=2))
				minus_change(win, dane, zasady, 8,7,5);
				break;
	}
}

void same_change(WINDOW *win, struct dane* dane, struct zasady* zasady, int a, int b, int c)
{
    dane->znak[b]=dane->znak[c]=dane->znak[a];
    wmove(win, 24, 1);
    wclrtoeol(win);
    wattron(win, COLOR_PAIR(1));
	mvwprintw(win, 24, 1, "Same!");
	wattroff(win, COLOR_PAIR(1));
	wrefresh(win);
	wgetch(win);
    combo_zmiana(win, dane, zasady, a, b, c);
}

void same(WINDOW *win, struct dane* dane, struct zasady* zasady, int a)
{
	switch (a)
	{
	case 0: if (sdol(dane, a) && sprawo(dane, a) && (swoje_dol(dane, a)+swoje_prawo(dane, a)!=2))
				same_change(win, dane, zasady, 0,1,3);
			break;
	case 1: if (sdol(dane, a) && slewo(dane, a) && (swoje_dol(dane, a)+swoje_lewo(dane, a)!=2))
				same_change(win, dane, zasady, 1,0,4);
			if (sdol(dane, a) && sprawo(dane, a) && (swoje_dol(dane, a)+swoje_prawo(dane, a)!=2))
				same_change(win, dane, zasady, 1,2,4);
			if (slewo(dane, a) && sprawo(dane, a) && (swoje_lewo(dane, a)+swoje_prawo(dane, a)!=2))
				same_change(win, dane, zasady, 1,0,2);
			break;
	case 2: if (sdol(dane, a) && slewo(dane, a) && (swoje_dol(dane, a)+swoje_lewo(dane, a)!=2))
				same_change(win, dane, zasady, 2,1,5);
			break;
	case 3: if (sdol(dane, a) && sgora(dane, a) && (swoje_dol(dane, a)+swoje_gora(dane, a)!=2))
				same_change(win, dane, zasady, 3,0,6);
			if (sdol(dane, a) && sprawo(dane, a) && (swoje_dol(dane, a)+swoje_prawo(dane, a)!=2))
				same_change(win, dane, zasady, 3,4,6);
			if (sgora(dane, a) && sprawo(dane, a) && (swoje_prawo(dane, a)+swoje_gora(dane, a)!=2))
				same_change(win, dane, zasady, 3,0,4);
			break;
	case 4: if (sdol(dane, a) && slewo(dane, a) && (swoje_dol(dane, a)+swoje_lewo(dane, a)!=2))
				same_change(win, dane, zasady, 4,3,7);
			if (sdol(dane, a) && sgora(dane, a) && (swoje_dol(dane, a)+swoje_gora(dane, a)!=2))
				same_change(win, dane, zasady, 4,1,7);
			if (sdol(dane, a) && sprawo(dane, a) && (swoje_dol(dane, a)+swoje_prawo(dane, a)!=2))
				same_change(win, dane, zasady, 4,5,7);
			if (slewo(dane, a) && sgora(dane, a) && (swoje_gora(dane, a)+swoje_lewo(dane, a)!=2))
				same_change(win, dane, zasady, 4,1,3);
			if (slewo(dane, a) && sprawo(dane, a) && (swoje_lewo(dane, a)+swoje_prawo(dane, a)!=2))
				same_change(win, dane, zasady, 4,3,5);
			if (sprawo(dane, a) && sgora(dane, a) && (swoje_prawo(dane, a)+swoje_gora(dane, a)!=2))
				same_change(win, dane, zasady, 4,1,5);
			break;
	case 5: if (sdol(dane, a) && slewo(dane, a) && (swoje_dol(dane, a)+swoje_lewo(dane, a)!=2))
				same_change(win, dane, zasady, 5,4,8);
			if (sdol(dane, a) && sgora(dane, a) && (swoje_dol(dane, a)+swoje_gora(dane, a)!=2))
				same_change(win, dane, zasady, 5,2,8);
			if (slewo(dane, a) && sgora(dane, a) && (swoje_lewo(dane, a)+swoje_gora(dane, a)!=2))
				same_change(win, dane, zasady, 5,2,4);
			break;
	case 6: if (sgora(dane, a) && sprawo(dane, a) && (swoje_prawo(dane, a)+swoje_gora(dane, a)!=2))
				same_change(win, dane, zasady, 6,3,7);
			break;
	case 7: if (sgora(dane, a) && slewo(dane, a) && (swoje_gora(dane, a)+swoje_lewo(dane, a)!=2))
				same_change(win, dane, zasady, 7,4,6);
			if (sprawo(dane, a) && sgora(dane, a) && (swoje_prawo(dane, a)+swoje_gora(dane, a)!=2))
				same_change(win, dane, zasady, 7,4,8);
			if (slewo(dane, a) && sprawo(dane, a) && (swoje_lewo(dane, a)+swoje_prawo(dane, a)!=2))
				same_change(win, dane, zasady, 7,6,8);
			break;
	case 8: if (sgora(dane, a) && slewo(dane, a) && (swoje_gora(dane, a)+swoje_lewo(dane, a)!=2))
				same_change(win, dane, zasady, 8,5,7);
			break;
	}
}

void combo(WINDOW* win, struct dane* dane, struct zasady* zasady)
{
    dane->zbilem=0;
    if(dane->zmiana1)
    {
        bicie(win, dane, zasady, dane->zmiana1);
    }
    if(dane->zmiana2)
    {
        bicie(win, dane, zasady, dane->zmiana2);
    }
    if (dane->zbilem)
    {
        wmove(win, 24, 1);
        wclrtoeol(win);
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 24, 1, "Combo!");
        wattroff(win, COLOR_PAIR(1));
        wrefresh(win);
        wgetch(win);
    }
    dane->zmiana0=0;
    dane->zmiana1=0;
    dane->zmiana2=0;
    dane->zbilem=0;
}

void wykonaj_zasady(WINDOW *win, struct dane* dane, struct zasady* zasady, int a)
{
    if (zasady->same)
		same(win, dane, zasady, a);
	if (zasady->plus)
		plus(win, dane, zasady, a);
	if (zasady->minus)
		minus(win, dane, zasady, a);
	bicie(win, dane, zasady, a);
}
