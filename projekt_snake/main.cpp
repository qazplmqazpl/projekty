#define _REENTRANT
#include <pthread.h>
#include<unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include<iostream>
#include <ctype.h>
#define MAKSYMALNADLUGOSCMEGAWENSZABYDLAKA 1000 //trzeba ifnąć gdy wonszkoniec/wonszpoczątek będzie równy 1000
#define ILOSCPRZESZKODDLAWENSZABYDLAKA 15
#define CZASMIEDZYOWOCKAMIDLAWENSZABYDLAKA 20
#define SZYBKOSCLADOWANIAPOZIOMUDLAWENSZABYDLAKA 8000
#include <unistd.h>
#include <Windows.h>
struct zmienne
{

int wonszx[MAKSYMALNADLUGOSCMEGAWENSZABYDLAKA];
int wonszy[MAKSYMALNADLUGOSCMEGAWENSZABYDLAKA];
int przeszkodyx[ILOSCPRZESZKODDLAWENSZABYDLAKA];
int przeszkodyy[ILOSCPRZESZKODDLAWENSZABYDLAKA];
int jedzonkox[100];
int jedzonkoy[100];
int jedzonkopoczatek;
int jedzonkokoniec;
pthread_t thread_id;
int wonszkoniec;
int wonszpoczatek;
int kierunek; // 0=gora 1=dol 2=lewo 3=prawo
int szer;
int wys;
bool czyplansza;
};
int plansza(int szerokoscparametr,int wysokoscparametr,zmienne* strukturka)
{
printf("\033[;f");
int szerokosc=0;
int wysokosc=0;
int helper = system("stty -echo");
int x,y;
printf("\033[41m");
while(szerokosc < szerokoscparametr)
	{
	printf("#");
	printf("\033[1C");
	usleep(SZYBKOSCLADOWANIAPOZIOMUDLAWENSZABYDLAKA);
	fflush(stdout);
	szerokosc++;
	}
while(wysokosc < wysokoscparametr)
	{
	printf("#");
	printf("\033[1B\033[1D");
	usleep(SZYBKOSCLADOWANIAPOZIOMUDLAWENSZABYDLAKA);
	fflush(stdout);
	wysokosc++;
	}
wysokosc=0;
szerokosc=0;
while(szerokosc < szerokoscparametr)
	{
	printf("#");
	printf("\033[1D\033[1D\033[1D");
	usleep(SZYBKOSCLADOWANIAPOZIOMUDLAWENSZABYDLAKA);
	fflush(stdout);
	szerokosc++;
	}
while(wysokosc < wysokoscparametr)
	{
	printf("#");
	printf("\033[1A\033[1D");
	usleep(SZYBKOSCLADOWANIAPOZIOMUDLAWENSZABYDLAKA);
	fflush(stdout);
	wysokosc++;
	}
int istare=0;
for(int i=0;i<ILOSCPRZESZKODDLAWENSZABYDLAKA;i++)
	{
	istare=i;
	x=(rand()%(szerokoscparametr-1))+2;
	y=(rand()%(wysokoscparametr))+1;
	y*=2;
	printf("\033[41m");
	printf("\033[%i;%ifO",x,y);
	printf("\033[0m");
	fflush(stdout);
	usleep(SZYBKOSCLADOWANIAPOZIOMUDLAWENSZABYDLAKA*5);
	for(int j=0;j<i;j++)
		{
		if ((*strukturka).przeszkodyx[j]==x && (*strukturka).przeszkodyy[j]==y)
			{
			i--;
			}
		}
	(*strukturka).przeszkodyx[i]=x;
	(*strukturka).przeszkodyy[i]=y;

	}
}

int getchare(void)
        {
            int ch;
            ch = getchar();
            return ch;
        }

int nowagra(zmienne* struktura)
{
for(int i=(*(zmienne*)struktura).wonszkoniec-1;i>=(*(zmienne*)struktura).wonszpoczatek-1;i--)
		{
		printf("\033[%i;%if%i",(*(zmienne*)struktura).wonszx[i],(*(zmienne*)struktura).wonszy[i]*2,(*(zmienne*)struktura).wonszkoniec-i);
		fflush(stdout);
		usleep(80000);
		if(((*(zmienne*)struktura).wonszkoniec-i)%10!=0 && i!=(*(zmienne*)struktura).wonszpoczatek-1) printf("\033[%i;%ifx ",(*(zmienne*)struktura).wonszx[i],(*(zmienne*)struktura).wonszy[i]*2);
		}
fflush(stdout);
sleep(1);
system("clear");
(*struktura).wonszkoniec=5;
(*struktura).wonszpoczatek=0;
(*struktura).jedzonkokoniec=0;
(*struktura).jedzonkopoczatek=0;
(*struktura).wonszy[0]=(*struktura).wys/2;
(*struktura).wonszx[0]=(*struktura).szer/2;
(*struktura).wonszy[1]=(*struktura).wys/2;
(*struktura).wonszx[1]=(*struktura).szer/2;
(*struktura).wonszy[2]=(*struktura).wys/2;
(*struktura).wonszx[2]=(*struktura).szer/2;
(*struktura).wonszy[3]=(*struktura).wys/2;
(*struktura).wonszx[3]=(*struktura).szer/2;
(*struktura).wonszy[4]=(*struktura).wys/2;
(*struktura).wonszx[4]=(*struktura).szer/2;
plansza((*struktura).wys,(*struktura).szer,struktura);
(*struktura).kierunek=0;
}
void *wateksterowanie(void *struktura)
{
int licznik=0;
int x;
int y;
int licznikstare;
while(1)
	{
	if((*(zmienne*)struktura).kierunek==1)
		{
		(*(zmienne*)struktura).wonszx[(*(zmienne*)struktura).wonszkoniec] = (*(zmienne*)struktura).wonszx[(*(zmienne*)struktura).wonszkoniec-1] +1;
		(*(zmienne*)struktura).wonszy[(*(zmienne*)struktura).wonszkoniec] = (*(zmienne*)struktura).wonszy[(*(zmienne*)struktura).wonszkoniec-1];
		}
	if((*(zmienne*)struktura).kierunek==0)
		{
		(*(zmienne*)struktura).wonszx[(*(zmienne*)struktura).wonszkoniec] = (*(zmienne*)struktura).wonszx[(*(zmienne*)struktura).wonszkoniec-1] -1;
		(*(zmienne*)struktura).wonszy[(*(zmienne*)struktura).wonszkoniec] = (*(zmienne*)struktura).wonszy[(*(zmienne*)struktura).wonszkoniec-1];
		}
	if((*(zmienne*)struktura).kierunek==2)
		{
		(*(zmienne*)struktura).wonszx[(*(zmienne*)struktura).wonszkoniec] = (*(zmienne*)struktura).wonszx[(*(zmienne*)struktura).wonszkoniec-1];
		(*(zmienne*)struktura).wonszy[(*(zmienne*)struktura).wonszkoniec] = (*(zmienne*)struktura).wonszy[(*(zmienne*)struktura).wonszkoniec-1] -1;
		}
	if((*(zmienne*)struktura).kierunek==3)
		{
		(*(zmienne*)struktura).wonszx[(*(zmienne*)struktura).wonszkoniec] = (*(zmienne*)struktura).wonszx[(*(zmienne*)struktura).wonszkoniec-1];
		(*(zmienne*)struktura).wonszy[(*(zmienne*)struktura).wonszkoniec] = (*(zmienne*)struktura).wonszy[(*(zmienne*)struktura).wonszkoniec-1] +1;
		}
	printf("\033[1;42m");
	for(int i=(*(zmienne*)struktura).wonszpoczatek;i<(*(zmienne*)struktura).wonszkoniec;i++)
		{
		printf("\033[%i;%ifX",(*(zmienne*)struktura).wonszx[i],(*(zmienne*)struktura).wonszy[i]*2);
		}
	printf("\033[0m");
	for(int i=(*(zmienne*)struktura).wonszpoczatek;i<(*(zmienne*)struktura).wonszkoniec;i++)
		{
		if (	  (*(zmienne*)struktura).wonszx[(*(zmienne*)struktura).wonszkoniec] == (*(zmienne*)struktura).wonszx[i]
			&&(*(zmienne*)struktura).wonszy[(*(zmienne*)struktura).wonszkoniec] == (*(zmienne*)struktura).wonszy[i]
			&&((*(zmienne*)struktura).wonszkoniec-(*(zmienne*)struktura).wonszpoczatek)>4)
			{
			fflush(stdout);
			nowagra((zmienne*)struktura);
			}
		}
	for(int j=0;j<ILOSCPRZESZKODDLAWENSZABYDLAKA;j++)
		{
		if ((*(zmienne*)struktura).przeszkodyx[j]==(*(zmienne*)struktura).wonszx[(*(zmienne*)struktura).wonszkoniec]
			 && (*(zmienne*)struktura).przeszkodyy[j]==(*(zmienne*)struktura).wonszy[(*(zmienne*)struktura).wonszkoniec]*2)
			{
			fflush(stdout);
			nowagra((zmienne*)struktura);
			}
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(int j=(*(zmienne*)struktura).jedzonkopoczatek;j<(*(zmienne*)struktura).jedzonkokoniec;j++)
		{
		if ((*(zmienne*)struktura).jedzonkox[j]==(*(zmienne*)struktura).wonszx[(*(zmienne*)struktura).wonszkoniec]
			 && (*(zmienne*)struktura).jedzonkoy[j]==(*(zmienne*)struktura).wonszy[(*(zmienne*)struktura).wonszkoniec]*2)
			{
			fflush(stdout);
			(*(zmienne*)struktura).wonszpoczatek--;
			}
		}
	if (	  (*(zmienne*)struktura).wonszx[(*(zmienne*)struktura).wonszkoniec] < 2
		||(*(zmienne*)struktura).wonszx[(*(zmienne*)struktura).wonszkoniec] > (*(zmienne*)struktura).szer
		||(*(zmienne*)struktura).wonszy[(*(zmienne*)struktura).wonszkoniec] < 1
		||(*(zmienne*)struktura).wonszy[(*(zmienne*)struktura).wonszkoniec] > (*(zmienne*)struktura).wys)
		{
		fflush(stdout);
		nowagra((zmienne*)struktura);
		}

	if(licznik>=CZASMIEDZYOWOCKAMIDLAWENSZABYDLAKA)
		{
		licznikstare=0;
		x=(rand()%((*(zmienne*)struktura).wys-1))+2;
		y=(rand()%((*(zmienne*)struktura).szer))+1;
		y*=2;
		for(int j=0;j<ILOSCPRZESZKODDLAWENSZABYDLAKA;j++)
			{
			if ((*(zmienne*)struktura).przeszkodyx[j]==x && (*(zmienne*)struktura).przeszkodyy[j]==y)
				{
				licznik--;
				licznikstare=1;
				}
			}
		for(int j=(*(zmienne*)struktura).jedzonkopoczatek;j<(*(zmienne*)struktura).jedzonkokoniec;j++)
			{
			if ((*(zmienne*)struktura).jedzonkox[j]==x && (*(zmienne*)struktura).jedzonkoy[j]==y)
				{
				licznik--;
				licznikstare=1;
				}
			}
		for(int j=(*(zmienne*)struktura).wonszpoczatek;j<(*(zmienne*)struktura).wonszkoniec;j++)
			{
			if ((*(zmienne*)struktura).wonszx[j]==x && (*(zmienne*)struktura).wonszy[j]==y)
				{
				licznik--;
				licznikstare=1;
				}
			}
		if (licznikstare==0)
			{
			printf("\033[31;46m");
			printf("\033[%i;%ifO",x,y);
			printf("\033[0m");
			(*(zmienne*)struktura).jedzonkox[(*(zmienne*)struktura).jedzonkokoniec]=x;
			(*(zmienne*)struktura).jedzonkoy[(*(zmienne*)struktura).jedzonkokoniec]=y;
			(*(zmienne*)struktura).jedzonkokoniec++;
			licznik=0;
			}
		}

	printf("\033[%i;%if ",(*(zmienne*)struktura).wonszx[(*(zmienne*)struktura).wonszpoczatek-1],(*(zmienne*)struktura).wonszy[(*(zmienne*)struktura).wonszpoczatek-1]*2);
	fflush(stdout);
	(*(zmienne*)struktura).wonszkoniec++;
	(*(zmienne*)struktura).wonszpoczatek++;
	usleep(80000);
	fflush(stdout);
	licznik++;
	}

return NULL;
}


///////////////////////////////////////////////////MAIN////////////////////
int main(int argc, char** argv)
{
zmienne naszezmienne;
if (argc!=3)
	{
	printf ("./program <szerokosc> <wysokosc>");
	exit(0);
	}

system("clear");
printf("\033[1;1f");
naszezmienne.wonszkoniec=5;
naszezmienne.wonszpoczatek=0;
sleep(1);
naszezmienne.wys=atoi(argv[1]);
naszezmienne.szer=atoi(argv[2]);
nowagra(&naszezmienne);
naszezmienne.kierunek=0; // 0=gora 1=dol 2=lewo 3=prawo
pthread_create(&naszezmienne.thread_id, NULL, wateksterowanie, (void*)&naszezmienne);
char keybuttonpressed;
while(1)
	{
	/*if (naszezmienne.czyplansza==true)
		{
		printf("\033[s");
		printf("\033[;f");
		plansza(atoi(argv[1]),atoi(argv[2]));
		printf("\033[u");
		naszezmienne.czyplansza=false;
		}*/
	//keybuttonpressed=getch();
	keybuttonpressed = (char)getchare();
	if (keybuttonpressed == 'w')
		{
		naszezmienne.kierunek = 0;
		keybuttonpressed = '.';
		fflush(stdout);
		}
	if (keybuttonpressed == 's')
		{
		naszezmienne.kierunek = 1;
		keybuttonpressed = '.';
		fflush(stdout);
		}
	if (keybuttonpressed == 'a')
		{
		naszezmienne.kierunek = 2;
		keybuttonpressed = '.';
		fflush(stdout);
		}
	if (keybuttonpressed == 'd')
		{
		naszezmienne.kierunek = 3;
		keybuttonpressed = '.';
		fflush(stdout);
		}
	if (keybuttonpressed == 'q')
		{
		naszezmienne.wonszpoczatek--;
		keybuttonpressed = '.';
		fflush(stdout);
		}
	}



fflush(stdout);
sleep(2);
}
