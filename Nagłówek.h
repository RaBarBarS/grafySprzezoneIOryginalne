#pragma once
#include "stdafx.h"

struct list;

class Graf {
	int numberLine = 0;		  //w konstruktorze
	int iloscWierzcholkow = 0;//iloœæ wierzcho³ków w sprzezonym, czli krawedzi w oryginalnym, potrzebne do zapisu do pliku
	int wierzcholkowIlosc = 0;//ilosc wierzcholkow w oryginalnym		
	bool eof = false;		  //w konstruktorze
	bool liniowy = 0;
	bool sprzezony = 0;
	bool sprzezenie();
	bool liniowosc();
	void transformacja();
	int**vertexArray;		//macierz sasiedztwa grafu wczytanego z pliku
public:
	Graf(int numer);		//konstruktor
	int**oryginalny;		//tablica krawedzi grafu oryginalnego
	int ilKrawedzi = 0;		//w konstruktorze	
//GETTERY
	int lineNumber();
	int iloscWierzch();
	int iloscKrawedzi();
	bool isEOF();
	bool isLiniowy();
	bool isSprzezony();
};

struct list {
	Graf*object;
	struct list*next;
};


void read();
void write(list*head);
void wynik();
int naprawTablice(int*oryginalny[], int ilosc);
