#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "datatype.h"
#include "header.h"

static int brojClanova = 0;

int izbornik(const char* const ime) {

	printf("\t\t----------------------------------------\n\n");
	printf("\t\tOdaberite opciju: \n\n");
	printf("\t\t\n\n");

	printf("\t\tOpcija 1: Dodavanje pica!\n");
	printf("\t\tOpcija 2: Ispisi podatke o svim picima!\n");
	printf("\t\tOpcija 3: Sortiraj po cijeni!\n");
	printf("\t\tOpcija 4: Pretrazivanje pica po ID-u!\n");
	printf("\t\tOpcija 5: Azuriraj pice!\n");
	printf("\t\tOpcija 6: Obrisi pice!\n");

	printf("\t\t----------------------------------------\n\n");

	int odgovor = 0;

	static PICE* poljePica = NULL;
	static PICE* pronadenoPice = NULL;

	scanf("%d", &odgovor);

	switch (odgovor) {
	case 1:
		dodajPice(ime);
		break;
	case 2:
		if (poljePica != NULL) {
			free(poljePica);
			poljePica = NULL;
		}

		poljePica = (PICE*)ucitajPica(ime);

		ispisiSve(poljePica);
		break;
	case 3:
		if (poljePica != NULL) {
			free(poljePica);
			poljePica = NULL;
		}

		poljePica = (PICE*)ucitajPica(ime);

		ispisiSortirano(poljePica);
		break;
	case 4:
		if (poljePica != NULL) {
			free(poljePica);
			poljePica = NULL;
		}

		poljePica = (PICE*)ucitajPica(ime);

		pronadenoPice = (PICE*)pretraziPica(poljePica);

		if (pronadenoPice != NULL) {
			printf("ID: %d\n", pronadenoPice->id);
			printf("naziv: %s\n", pronadenoPice->naziv);
			printf("cijena: %.2f\n", pronadenoPice->cijena);
		}
		else {
			printf("Ne postoji pice s tim ID-em.\n");
		}

		break;
	case 5:
		if (poljePica != NULL) {
			free(poljePica);
			poljePica = NULL;
		}

		poljePica = (PICE*)ucitajPica(ime);

		azurirajPice(poljePica, ime);
		break;
	case 6:
		if (poljePica != NULL) {
			free(poljePica);
			poljePica = NULL;
		}

		poljePica = (PICE*)ucitajPica(ime);

		brisanjePica(poljePica, ime);
		break;
	default:
		free(poljePica);
		poljePica = NULL;
		odgovor = 0;
	}

	return odgovor;
}