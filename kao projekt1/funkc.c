#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "header.h"

static int brojPica = 0;
//funckije za zauzimanje memorije, za pisanje i ucitavanje datoteke
void kreiranjeDatoteke(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	// ak ne postoji stvaramo novu datoteku sa wb, ako postoji samo zatvaramo
	if (fp == NULL) {
		fp = fopen(ime, "wb");

		fwrite(&brojPica, sizeof(int), 1, fp);

		fclose(fp);
	}
	else {
		fclose(fp);
	}

}

void dodajPice(const char* const ime) {

	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Dodavanje pica u datoteku pica.bin");
		exit(EXIT_FAILURE);
	}

	//citamo prvi red datoteke i zapisujemo broj clanova u varijablu brojPica
	fread(&brojPica, sizeof(int), 1, fp);
	printf("Broj pica: %d\n\n", brojPica);

	PICE temp = { 0 };
	temp.id = brojPica + 1;
	getchar();

	printf("Unesite naziv pica: ");
	scanf("%24[^\n]", temp.naziv);
	getchar();

	printf("Unesite cijenu pica: ");
	scanf("%f", &temp.cijena);


	//pomicemo se na kraj datoteke i zapisujemo novog clana tamo
	fseek(fp, sizeof(PICE) * brojPica, SEEK_CUR);
	fwrite(&temp, sizeof(PICE), 1, fp);
	printf("novo pice dodano.\n\n");

	// povratak na pocetak datoteke
	rewind(fp);
	brojPica++;

	// zapis novog broja clanova
	fwrite(&brojPica, sizeof(int), 1, fp);

	fclose(fp);
}

void* ucitajPica(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	if (fp == NULL) {
		perror("Ucitavanje pica iz pica.bin");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(&brojPica, sizeof(int), 1, fp);
	printf("Broj clanova: %d\n", brojPica);

	PICE* poljePica = (PICE*)calloc(brojPica, sizeof(PICE));

	if (poljePica == NULL) {
		perror("Zauzimanje memorije za pica");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(poljePica, sizeof(PICE), brojPica, fp);

	printf("Svi clanovi uspjesno ucitani.\n\n");

	return poljePica;
}

void ispisiSve(const PICE* polje) {

	if (brojPica == 0) {
		printf("Polje pica prazno\n");
		return;
	}

	int i;

	for (i = 0; i < brojPica; i++) {
		printf("Puska broj %d\nID: %d\nnaziv: %s\ncijena: %.2f\n\n",
			i + 1,
			(polje + i)->id,
			(polje + i)->naziv,
			(polje + i)->cijena);

	}
}

void* pretraziPica(PICE* const polje) {

	if (brojPica == 0) {
		printf("Polje pica prazno\n");
		return;
	}

	int i;

	int trazeniId;

	printf("Unesite ID pica koju trazite: \n");
	scanf("%d", &trazeniId);

	// ako nademo clana vracamo cijeli element polja s trazenim id-em
	for (i = 0; i < brojPica; i++) {

		if (trazeniId == (polje + i)->id) {
			printf("pica pronadeno.\n");

			return (polje + i);
		}
	}

	// vracamo NULL u slucaju da ne nademo nijednu pusku s tim id
	return NULL;
}

void zamjena(PICE* const veci, PICE* const manji) {
	PICE temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void* sortirajPoCijeni(const PICE* polje) {

	int min = -1;

	for (int i = 0; i < brojPica - 1; i++) {

		min = i;
		for (int j = i + 1; j < brojPica; j++) {

			if ((polje + j)->cijena < (polje + min)->cijena) {
				min = j;
			}
		}

		zamjena((polje + i), (polje + min));
	}

	return polje;
}

void ispisiSortirano(const PICE* polje) {

	if (brojPica == 0) {
		printf("Polje pica prazno\n");
		return;
	}

	int i;

	polje = sortirajPoCijeni(polje);

	for (i = 0; i < brojPica; i++) {
		printf("pice broj %d\nID: %d\nnaziv: %s\cijena: %.2f\n\n",
			i + 1,
			(polje + i)->id,
			(polje + i)->naziv,
			(polje + i)->cijena);
	}
}

void azurirajPice(PICE* polje, const char* const dat) {

	if (brojPica == 0) {
		printf("Polje pusaka prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Azuriranje pica");
		exit(EXIT_FAILURE);
	}

	int trazeniId;

	printf("Unesite ID pica koju zelite azurirati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojPica) {
			printf("pice s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojPica);

	PICE temp = { 0 };

	temp.id = trazeniId;

	getchar();
	printf("Unesite ime pica (trenutno: %s): ", (polje + trazeniId - 1)->naziv);
	scanf("%24[^\n]", temp.naziv);
	getchar();

	printf("Unesite cijenu pica (trenutno: %d mm): ", (polje + trazeniId - 1)->cijena);
	scanf("%d", &temp.cijena);


	fseek(fp, sizeof(int), SEEK_SET);
	fseek(fp, sizeof(PICE) * (trazeniId - 1), SEEK_CUR);
	fwrite(&temp, sizeof(PICE), 1, fp);

	printf("pice uspjesno azurirana\n");

	fclose(fp);
}

void brisanjePica(PICE* const polje, const char* const dat) {

	if (brojPica == 0) {
		printf("Polje pica prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Brisanje pica");
		exit(EXIT_FAILURE);
	}

	fseek(fp, sizeof(int), SEEK_CUR);

	int i, trazeniId;

	printf("Unesite ID pica kojeg zelite obrisati: ");

	do {
		scanf("%d", &trazeniId);
		if (trazeniId < 1 || trazeniId > brojPica) {
			printf("pice s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojPica);

	PICE* pomocnoPolje = (PICE*)calloc(brojPica - 1, sizeof(PICE));

	int counter = 0;

	for (i = 0; i < brojPica; i++) {

		if (trazeniId != (polje + i)->id) {
			*(pomocnoPolje + counter) = *(polje + i);

			if ((pomocnoPolje + counter)->id > trazeniId) {
				(pomocnoPolje + counter)->id -= 1;
			}

			fwrite((pomocnoPolje + counter), sizeof(PICE), 1, fp);
			counter++;
		}
	}

	free(pomocnoPolje);
	pomocnoPolje = NULL;

	rewind(fp);

	fwrite(&counter, sizeof(int), 1, fp);
	fclose(fp);

	printf("pice je uspjesno obrisana\n");
}