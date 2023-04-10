#ifndef LABUL_2_DOMAIN_H
#define LABUL_2_DOMAIN_H
#include <string.h>
#include <stdlib.h>

typedef struct Medicament{
    int id, cantitate, concentratie;
    char *nume;
}Medicament;

/**
 * constructorul unui medicament - creeaza o instanta a structurii medicament cu datele primite si o returneaza
 * @param id - int pozitiv
 * @param nume - un pointer catre un sir de caractere alocat dinamic
 * @param cantitate - int pozitiv
 * @param concentratie - int pozitiv
 * @return o instanta a structurii de tip medicament
 */
Medicament* creeaza_medicament(int id,char* nume, int cantitate, int concentratie);

/**
 * realizeaza o copie a unui medicament si il returneaza
 * @param medicament - o instanta a structurii medicament
 * @return o instanta a structurii de tip medicament cu aceleasi date pe care le are medicamentul primit ca parametru
 */
Medicament* copy_medicament(Medicament *medicament);

/**
 * dezaloca memoria alocata pentru nume si elimina valorile celorlalte atribute ale medicamentului
 * @param medicament - o instanta a structurii medicament
 */
void destroy_medicament(Medicament *medicament);

/**
 * valideaza un medicament primit ca si parametru sa aiba un id, o cantitate si o concentratie pozitive si diferite de 0
 * @param medicament - o instanta a structurii medicament
 * @return returneaza 1 daca idul este invalid, 2 daca cantitatea este invalida, 3 daca concentratia este invalida, 0 altfel
 */
int validate(Medicament* medicament);

#endif
