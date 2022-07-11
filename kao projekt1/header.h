#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "datatype.h"

int izbornik(const char* const);
void kreiranjeDatoteke(const char* const);
void dodajPice(const char* const);
void* ucitajPica(const char* const);
void ispisiSve(const PICE*);
void ispisiSortirano(const PICE*);
void* pretraziPica(PICE* const);
void azurirajPice(PICE*, const char* const);
void brisanjePica(PICE* const, const char* const);
void* sortirajPoCijeni(const PICE* polje);

#endif