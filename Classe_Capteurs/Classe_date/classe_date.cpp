#include "classe_date.h"

long Classe_date::gday(void)
{       /* convert date to day number */
  long  y, m;

  m = (date.m + 9)%12;                /* mar=0, feb=11 */
  y = date.y - m/10;                     /* if Jan/Feb, year-- */
  return y*365 + y/4 - y/100 + y/400 + (m*306 + 5)/10 + (date.d - 1);
}

void Classe_date::incremanteDate (void)
{
    long y, ddd, mi;

    j++;
    y = (10000*j + 14780)/3652425;
    ddd = j - (y*365 + y/4 - y/100 + y/400);
    if (ddd < 0)
    {
        y--;
        ddd = j - (y*365 + y/4 - y/100 + y/400);
    }
    mi = (52 + 100*ddd)/3060;
    date.y = y + (mi + 2)/12;
    date.m = (mi + 2)%12 + 1;
    date.d = ddd - (mi*306 + 5)/10 + 1;
}

void Classe_date::incremanteTemp(void)
{
    temp.seconde++;
    if(temp.seconde >= 60)
    {
        temp.seconde = 0;
        temp.minute++;

        if(temp.minute >= 60)
        {
            temp.minute = 0;
            temp.heure++;
            if(temp.heure >= 24)
            {
                temp.heure = 0;
                incremanteDate();
            }
        }
    }
}

//fonction pour prendre la date

char *Classe_date::getDateComplete(void)
{
    char strDate[30];
	int anne = date.y+dOffset;
	int mois = date.m;
	int jours = date.d;
	int heures = temp.heure;
	int minutes = temp.minute;
	int secondes = temp.seconde;

    sprintf(strDate,"%04d-%02d-%02d %02d:%02d:%02d",anne, mois, jours, heures, minutes, secondes);
    return strDate;
}

char *Classe_date::getDate(void)
{
    char strDate[15] = "2015:3:26";
	int anne = date.y+dOffset;
	int mois = date.m;
	int jours = date.d;
	
    sprintf(strDate,"%04d-02d-%02d",anne, mois, jours);
    return strDate;
}

char *Classe_date::getDateFichier(void)
{
    char strDate[13] = "20150326.txt";

	int anne = date.y+dOffset;
	int mois = date.m;
	int jours = date.d;
	
    sprintf(strDate,"%04d%02d%02d.txt",anne, mois, jours);
    return strDate;
}

char *Classe_date::getHeure(void)
{
    char strDate[10] = "01:11:26";

	int heures = temp.heure;
	int minutes = temp.minute;
	int secondes = temp.seconde;
	
    sprintf(strDate,"%02d:%02d:%02d",heures,
            minutes, secondes);
    return strDate;
}

void Classe_date::setDate(int y, char m, char d)
{
    date.y = 0;
    dOffset = y;
    date.m = m;
    date.d = d;
    j = gday();
}

void Classe_date::setHeure(char h, char m, char s)
{
    temp.heure = h;
    temp.minute = m;
    temp.seconde = s;

}

