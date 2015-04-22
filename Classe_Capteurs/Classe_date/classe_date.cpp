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
    char strDate[] = "2015/03/26 01:16:27";

    sprintf(strDate,"%04d/%02d/%02d %02d:%02d:%02d",
            (int)date.y+(int)dOffset, (int)date.m, (int)date.d),
            (int)temp.heure, (int)temp.minute, (int)temp.seconde;
    return strDate;
}

char *Classe_date::getDate(void)
{
<<<<<<< HEAD
<<<<<<< HEAD
    char strDate[30] = "2015:3:26";
	int anne = date.y+dOffset;
	int mois = date.m;
	int jours = date.d;
	
    sprintf(strDate,"%04d-02d-%02d",anne, mois, jours);
=======
=======
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
    char strDate[] = "2015/03/26";

    sprintf(strDate,"%04d/%02d/%02d",
            (int)date.y+(int)dOffset, (int)date.m, (int)date.d);
<<<<<<< HEAD
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
=======
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
    return strDate;
}

char *Classe_date::getDateFichier(void)
{
<<<<<<< HEAD
<<<<<<< HEAD
    char strDate[30] = "20150326.txt";
=======
    char strDate[] = "20150326";
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
=======
    char strDate[] = "20150326";
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++

    sprintf(strDate,"%04d%02d%02d.txt",
            (int)date.y+(int)dOffset, (int)date.m, (int)date.d);
    return strDate;
}

char *Classe_date::getHeure(void)
{
<<<<<<< HEAD
<<<<<<< HEAD
    char strDate[30] = "01:11:26";

	int heures = temp.heure;
	int minutes = temp.minute;
	int secondes = temp.seconde;
	
    sprintf(strDate,"%02d:%02d:%02d",heures,
            minutes, secondes);
=======
=======
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
    char strDate[] = "01:11:26";

    sprintf(strDate,"%02d:%02d:%02d",(int)temp.heure,
            (int)temp.minute, (int)temp.seconde);
<<<<<<< HEAD
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
=======
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
    return strDate;
}

void Classe_date::setDate(long y, long m, long d)
{
    date.y = 0;
    dOffset = y;
    date.m = m;
    date.d = d;
    j = gday();
}

void Classe_date::setHeure(int h, int m, int s)
{
    temp.heure = h;
    temp.minute = m;
    temp.seconde = s;

}

