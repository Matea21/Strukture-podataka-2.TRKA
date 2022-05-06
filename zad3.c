#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX 1024

typedef struct _osoba {
	char ime[MAX];
	char prezime[MAX];
	int godinaRodenja;
	struct _osoba*next;
}Osoba;

int Menu(Osoba*Head);
Osoba* UnosPodataka(void);
int DodatiElementNaPocetak(Osoba *El, Osoba*Head);
int IspisElemenata(Osoba*Head);
int DosatiElementNaKraj(Osoba*El, Osoba*Head);
Osoba* PronadiElementPoPrezimenu(Osoba*Head, char*prezime);
int IzbrisiElement(Osoba*El, Osoba*Head);
int DodajElementIza(Osoba* noviEl, Osoba*El);
int DodajElementIspred(Osoba*Head, Osoba*El);
Osoba*PronadiPrethodniElement(Osoba*Head, Osoba*El);
Osoba* PronadiZadnjiElement(Osoba*Head);
int SpremiListuUDatoteku(Osoba*Head, char*datoteka);
int UcitajListuIzDatoteke(Osoba*Head, char*datoteka);

int main() {

	Osoba*Head = (Osoba*)malloc(sizeof(Osoba));
	Head->next = NULL;
	int status = 0;
	Osoba*El = (Osoba*)malloc(sizeof(Osoba));

	do {
		status =Menu(Head);
	} while (!status);

	return 0;
}
int Menu(Osoba*Head) {
	int c = 0;
	int status = 0;
	char prezime[MAX];
	char datoteka[MAX];
	Osoba*El = (Osoba*)malloc(sizeof(Osoba));

	printf("Odaberite zeljenu opciju: \n");
	printf("1.Dodati element na početak liste\n");
	printf("2.Ispisati listu\n");
	printf("3.Dodati element na kraj liste\n");
	printf("4.Pronadi osobu po prezimenu\n");
	printf("5.Izbrisi element\n");
	printf("6.Dodaj element iza nekog elementa\n");
	printf("7.Dodaj element ispred nekog elementa\n");
	printf("8.Spremi listu u datoteku\n");
	printf("9.Ucitaj listu iz datoteke\n");
	scanf("%d", &c);

	do {
		status = c;
	} while (!status);

	switch (c) {
	case(1):
		DodatiElementNaPocetak(UnosPodataka(), Head);
		break;
	case(2):
		IspisElemenata(Head);
		break;
	case(3):
		DosatiElementNaKraj(UnosPodataka(), Head);
		break;
	case(4):
		printf("Upisite prezime elementa kojeg zelite pronaci:");
		scanf("%s", prezime);
		El = PronadiElementPoPrezimenu(Head, prezime);
		printf("%s	%s	%d", El->ime, El->prezime, El->godinaRodenja);
		break;
	case(5):
		printf("Upisite prezime elementa kojeg zelite izbrisati:");
		scanf("%s", prezime);
		IzbrisiElement(PronadiElementPoPrezimenu(Head, prezime), Head);
		break;
	case(6):
		printf("Upisite prezime elementa iza kojeg zelite dodati novi element:");
		scanf("%s", prezime);
		El = PronadiElementPoPrezimenu(Head, prezime);
		DodajElementIza(UnosPodataka(), El);
		break;
	case(7):
		printf("Upisite prezime elementa ispred kojeg zelite dodati novi element:");
		scanf("%s", prezime);
		DodajElementIspred(Head,PronadiElementPoPrezimenu(Head,prezime));
		break;
	case(8):
		printf("Upisite ime daoteke:");
		scanf("%s", datoteka);
		SpremiListuUDatoteku(Head, datoteka);
		break;
	case(9):
		printf("Upisite ime datoteke:");
		scanf("%s", datoteka);
		UcitajListuIzDatoteke(Head, datoteka);
		break;
	default:
		printf("Krivi unos");

	case (0):
		return 1;
	}
}

Osoba* UnosPodataka(void) {
	Osoba*El = (Osoba*)malloc(sizeof(Osoba*));

	printf("Unesite ime,prezime i godinu rodenja:\n");
	scanf("%s %s %d", El->ime, El->prezime, &(El->godinaRodenja));

	return El;
}

int DodatiElementNaPocetak(Osoba *El, Osoba*Head) {
	El->next = Head->next;
	Head->next = El;

	return 0;
}
int IspisElemenata(Osoba*Head) {
	Osoba*P = Head->next;

	while (P != NULL) {
		printf("Ime:%s	Prezime:%s	Godina rodenja:%d\t\n", P->ime, P->prezime, P->godinaRodenja);
		P=P->next;
	}

	return 0;
}
int DosatiElementNaKraj(Osoba*El, Osoba*Head) {

	Osoba *P = Head;

	while (P->next != NULL)
		P = P->next;

	P->next = El;
	El->next = NULL;

	return 0;
}
Osoba* PronadiElementPoPrezimenu(Osoba*Head, char*prezime) {

	Osoba*P = Head->next;

	while (P != NULL && strcmp(P->prezime,prezime))
		P = P->next;

	return P;
}
int IzbrisiElement(Osoba*El, Osoba*Head) {
	Osoba*P = Head;

	while (P!= NULL && P->next!= El)
		P = P->next;

	if (P == NULL)
		return -1;
	else
	{
		P->next = El->next;
		free(El);
	}

	return 0;
}
int DodajElementIza(Osoba* noviEl, Osoba*El) {

	noviEl->next = El->next;
	El->next = noviEl;

	return 0;
}
int DodajElementIspred(Osoba*Head, Osoba*El) {

	Osoba*noviEl = (Osoba*)malloc(sizeof(Osoba));
	Osoba*P = Head;

	while (P != NULL && P->next != El)
		P = P->next;

	DodajElementIza(UnosPodataka(), P);

	return 0;
}
Osoba*PronadiPrethodniElement(Osoba*Head, Osoba*El) {
	Osoba*P = Head;

	while (P != NULL && P->next != El)
		P = P->next;

	return P;
}
Osoba* PronadiZadnjiElement(Osoba*Head) {

	return PronadiPrethodniElement(Head, NULL);
}
int SpremiListuUDatoteku(Osoba*Head, char*datoteka) {
	FILE* fp = NULL;
	Osoba*P = Head->next;

	fp = fopen(datoteka, "w");
	if (fp == NULL)
		return -1;

	fprintf(fp, "IME		PREZIME		GODINA ROĐENJA\n");

	while (P != NULL) {
		fprintf(fp, "%s		%s		%d\n", P->ime, P->prezime, P->godinaRodenja);
		P = P->next;
	}

	fclose(fp);

	return 0;
}
int UcitajListuIzDatoteke(Osoba*Head, char*datoteka) {
	FILE*fp = NULL;
	int brojOsoba = 0;
	char buffer[MAX] = { 0 };
	Osoba*noviEl = (Osoba*)malloc(sizeof(Osoba));
	Osoba*P = PronadiZadnjiElement(Head);

	fp = fopen(datoteka, "r");

	if (fp == NULL)
		return-1;

	while (getc(fp) != '\n')
		continue;

	while (fgets(buffer, MAX, fp))
		brojOsoba++;
	rewind(fp);

	while (getc(fp) != '\n')
		continue;

	for (int i = 0; i < brojOsoba; i++) {
		noviEl->next = NULL;
		P->next = noviEl;
		P = P->next;

		fscanf(fp, "%s %s %d", noviEl->ime, noviEl->prezime, &(noviEl->godinaRodenja));
	}

	fclose(fp);

	return 0;
}
