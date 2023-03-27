#include "pliki.h"

int zapis(WINDOW *win, struct dane* dane, struct zasady* zasady)
{
    FILE *fp;
    if ((fp=fopen("rules.txt", "wt"))==NULL)
    {
        wattron(win, COLOR_PAIR(3));
        mvwprintw(win, 23, 1, "Zapisywanie zasad nie udalo sie!");
        wattroff(win, COLOR_PAIR(3));
        return 1;
    }
    fprintf(fp, "Same\t%d\nPlus\t%d\nMinus\t%d\nOrder\t%d\nOpen\t%d\nWall\t%d\nWall Value\t%d\nCombo\t%d\nMuzyka\t%d\n",
    zasady->same, zasady->plus, zasady->minus, zasady->order, zasady->open, zasady->wall, dane->wall_value, zasady->combo, zasady->muzyka);
    fclose (fp);
    return 0;
}

int odczyt(WINDOW *win, struct dane* dane, struct zasady* zasady)
{
    FILE *fp;
    if ((fp=fopen("rules.txt", "rt"))==NULL)
    {
        wattron(win, COLOR_PAIR(3));
        mvwprintw(win, 21, 1, "Wczytywanie zasad nie udalo sie!");
        mvwprintw(win, 22, 1, "Korzystam z ustawien domyslnych.");
        mvwprintw(win, 23, 1, "Zapisz swoje zasady!");
        wattroff(win, COLOR_PAIR(3));
        return 1;
    }
    fscanf(fp, "Same\t%d\nPlus\t%d\nMinus\t%d\nOrder\t%d\nOpen\t%d\nWall\t%d\nWall Value\t%d\nCombo\t%d\nMuzyka\t%d\n",
    &zasady->same, &zasady->plus, &zasady->minus, &zasady->order, &zasady->open, &zasady->wall, &dane->wall_value, &zasady->combo, &zasady->muzyka);
    fclose (fp);
    return 0;
}
