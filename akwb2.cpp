// akwb2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "Nagłówek.h"
#include <Windows.h>
#include <string>
#include <iomanip>


using namespace std;


int width;	//do wyśrodkowania tekstu na początku programu
int height;//same as above


int bufferinfo()
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	width = csbiInfo.dwSize.X;
	height = csbiInfo.dwSize.Y;

	return 0;
}


int main()
{

	bufferinfo();
	string zmienna = "<GRAFY SPRZEZONE>";
	cout << setw(((zmienna.length()) + width) / 2) << zmienna;
	//Sleep(5000);
	system("cls");

	zmienna = "DAJ MI CHWILE, MYSLE...";
	cout << setw(((zmienna.length()) + width) / 2) << zmienna;
	cout << endl;

	read();
	system("cls");
	wynik();

	cout << endl << "THANKS FOR WATCHING" << endl;

	system("Pause");
	return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
