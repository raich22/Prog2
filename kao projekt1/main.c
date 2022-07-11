#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(void) {

	int odgovor = 1;

	char* datoteka = "pica.bin";

	kreiranjeDatoteke(datoteka);

	while (odgovor) {
		odgovor = izbornik(datoteka);
	}

	printf("Kraj programa");

	return 0;
}