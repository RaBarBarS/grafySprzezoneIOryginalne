#include "pch.h"
#include "Nag³ówek.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
int nrLinii = 0;
bool endOFile = false;
list*head = NULL;
list*tail = NULL;


Graf::Graf(int number) {
	int actualNumber = 0, v1, v2, found;
	string line, help;
	fstream file;
	file.open("plik.txt", ios::in);
	if (file.good() == false) cout << "Nie mozna otworzyc pliku!";
	else {
		while (actualNumber < number) {
			getline(file, line);
			actualNumber++;
		}

		getline(file, line);
		iloscWierzcholkow = atoi(line.c_str());
		actualNumber++;

		vertexArray = new int*[iloscWierzcholkow];
		for (int i = 0; i < iloscWierzcholkow; i++) {
			vertexArray[i] = new int[iloscWierzcholkow];
		}
		for (int i = 0; i < iloscWierzcholkow; i++) {
			for (int j = 0; j < iloscWierzcholkow; j++) {
				vertexArray[i][j] = 0;
			}
		}

		while (getline(file, line))
		{
			actualNumber++;
			if (line == "")		break;
			else {
				found = line.find(" ");
				help.insert(0, line, 0, found);
				v1 = atoi(help.c_str());
				help.clear();
				help.insert(0, line, found + 1, 6);
				v2 = atoi(help.c_str());
				help.clear();

				vertexArray[v1 - 1][v2 - 1] += 1;
				ilKrawedzi++;
			}
		}
		if (line == "") {
			numberLine = actualNumber;
		}
		if (!getline(file, line)) {
			eof = true;
		}
	}

	sprzezony = sprzezenie();

	if (sprzezony == 1) {
		liniowy = liniowosc();
		transformacja();
	}
	file.close();
}

bool Graf::sprzezenie() {
	int i = 0, j = 0, wspNast = 0, rozNast = 0;
	for (i; i < iloscWierzcholkow; i++) {
		j = i;
		for (j; j < iloscWierzcholkow; j++) {	//czy 1-graf
			if (vertexArray[i][j] > 1 || vertexArray[j][i] > 1)	return 0;
		}
	}
	for (i = 0; i < iloscWierzcholkow - 1; i++) {
		for (int k = i + 1; k < iloscWierzcholkow; k++) {
			for (j = 0; j < iloscWierzcholkow; j++) {	//warunek o nastepnikach
				//if (j == k || i == j)	continue;
				if (vertexArray[i][j] == 1 && vertexArray[k][j] == 1)	wspNast = 1;	//jeœli choæ jeden wspó³ny nastêpnik
				if (vertexArray[i][j] != vertexArray[k][j])		rozNast = 1;			//jeœli choæ jeden roz³¹czny nastêpnik
			}
			if (wspNast == 1 && rozNast == 1)	return 0;
			wspNast = 0;	rozNast = 0;
		}
	}
	return 1;
}

bool Graf::liniowosc() {
	for (int i = 0; i < iloscWierzcholkow - 1; i++) {
		for (int k = i + 1; k < iloscWierzcholkow; k++) {
			for (int j = 0; j < iloscWierzcholkow; j++) {
				if (vertexArray[i][j] == 1 && vertexArray[k][j] == 1) {
					for (int m = 0; m < iloscWierzcholkow; m++) {
						if (vertexArray[m][i] && vertexArray[m][k])	return 0;	//jeœli s¹ wspólne nastêpniki to nie mo¿e byæ wspólnych poprzedników
					}
				}
			}
		}
	}
	return 1;
}

void Graf::transformacja() {
	int pomoc = 0;
	oryginalny = new int*[iloscWierzcholkow];
	for (int i = 0; i < iloscWierzcholkow; i++) {
		oryginalny[i] = new int[2];
		for (int j = 0; j < 2; j++) {	//tworzenie tablicy pomocniczej; zawiera krawedzie oryginalnego
			oryginalny[i][j] = pomoc;
			pomoc++;
		}
	}

	for (int i = 0; i < iloscWierzcholkow; i++) {	//zapis zale¿noœæi pomiedzy krawedziami w oryginalnym
		for (int j = 0; j < iloscWierzcholkow; j++) {
			if (vertexArray[i][j] == 1) {
				for (int k = 0; k <= i; k++) {
					if (vertexArray[k][i] == 1) {
						//oryginalny[i][0] = oryginalny[k][1];
						if (oryginalny[i][1] > oryginalny[j][0])	oryginalny[i][1] = oryginalny[j][0];
						else oryginalny[j][0] = oryginalny[i][1];
					}
				}
				if (oryginalny[i][1] > oryginalny[j][0])	oryginalny[i][1] = oryginalny[j][0];
				else oryginalny[j][0] = oryginalny[i][1];
			}
		}
	}
	wierzcholkowIlosc = naprawTablice(oryginalny, iloscWierzcholkow);
}

int Graf::lineNumber() {
	return numberLine;
}

int Graf::iloscWierzch() {
	return wierzcholkowIlosc;
}

int Graf::iloscKrawedzi() {
	return iloscWierzcholkow;
}

bool Graf::isEOF() {
	return eof;
}

bool Graf::isLiniowy() {
	return liniowy;
}

bool Graf::isSprzezony() {
	return sprzezony;
}


void read() {
	list*current = new list;
	while (endOFile == false) {
		//		Graf*obj = new Graf(nrLinii);
		if (head == NULL) {
			Graf*obj = new Graf(nrLinii);
			//current = head;
			current->next = tail;
			head = current;
			current->object = obj;
			nrLinii = obj->lineNumber();
			endOFile = obj->isEOF();
		}
		else {
			list*tmp = new list;
			Graf*obj = new Graf(nrLinii);
			tmp->object = obj;
			tmp->next = tail;
			current->next = tmp;
			current = tmp;
			nrLinii = obj->lineNumber();
			endOFile = obj->isEOF();
		}
	}
	write(head);
}

void write(list*head) {//zle
	int j = 0;
	if (head == NULL) {
		cout << "BRAK DANYCH DO ZAPISANIA" << endl;
	}
	else {
		string name;
		cout << "PODAJ NAZWE PLIKU DO KTOREGO ZAPISAC WYNIKI:" << endl;
		cin >> name;
		fstream plik;
		plik.open(name += ".txt", ios::out);
		while (head->next) {
			if (head->object->isSprzezony()) {
				if (j == 0) {
					plik << head->object->iloscWierzch() << endl;
					j++;
				}

				for (int i = 0; i < head->object->iloscKrawedzi(); i++) {
					plik << (head->object->oryginalny[i][0] + 1) << " " << (head->object->oryginalny[i][1] + 1) << endl;
				}

				plik << endl;
			}
			head = head->next;
			j = 0;
		}
		if (head->object->isSprzezony()) {
			if (j == 0) {
				plik << head->object->iloscWierzch() << endl;
				j++;
			}

			for (int i = 0; i < head->object->iloscKrawedzi(); i++) {
				plik << (head->object->oryginalny[i][0] + 1) << " " << (head->object->oryginalny[i][1] + 1) << endl;
			}
		}
		plik << "\n" << endl;
		plik.close();
	}
}

void wynik() {
	list*l = head;
	int nrGrafu = 1;
	if (head == NULL) {
		cout << "NIE WIDZE ZADNYCH GRAFOW..." << endl;
	}
	else {
		while (l->next) {
			cout << "GRAF NR " << nrGrafu << ":" << endl;
			if (l->object->isSprzezony())	cout << "JEST SPRZEZONY" << endl;
			else							cout << "NIE JEST SPRZEZONY" << endl;
			if (l->object->isLiniowy())		cout << "JEST LINIOWY" << endl;
			else							cout << "NIE JEST LINIOWY" << endl;
			cout << l->object->ilKrawedzi << endl;
			cout << endl;
			l = l->next;
			nrGrafu++;
		}
		cout << "GRAF NR " << nrGrafu << ":" << endl;
		if (l->object->isSprzezony())	cout << "JEST SPRZEZONY" << endl;
		else							cout << "NIE JEST SPRZEZONY" << endl;
		if (l->object->isLiniowy())		cout << "JEST LINIOWY" << endl;
		else							cout << "NIE JEST LINIOWY" << endl;
		cout << endl;
	}
}

int naprawTablice(int*oryginalny[], int ilosc) {
	int wierzcholki = 0;
	int*tabPom = new int[2 * ilosc];	//wierzcholkow w oryginalnym maksymalnie tyle co 2x w sprzezonym
	for (int i = 0; i < 2 * ilosc; i++) {
		tabPom[i] = 0;
	}
	for (int i = 0; i < ilosc; i++) {
		for (int j = 0; j < 2; j++) {
			tabPom[oryginalny[i][j]] = 1;
		}
	}
	for (int i = 0; i < 2 * ilosc; i++) {
		if (tabPom[i] == 0) {
			for (int j = i; j < 2 * ilosc; j++) {
				if (tabPom[j] == 1) {
					for (int h = 0; h < ilosc; h++) {
						for (int g = 0; g < 2; g++) {
							if (oryginalny[h][g] == j)	oryginalny[h][g] = i;
						}
					}
					tabPom[i] = 1;
					tabPom[j] = 0;
					break;
				}
			}
		}
	}

	for (int i = 0; i < (2 * ilosc - 1); i++) {
		if (tabPom[i + 1] == 0) {
			wierzcholki = i + 1;
			break;
		}
	}
	return wierzcholki;
}