#ifndef LABUL_2_REPO_H
#define LABUL_2_REPO_H
#include "../Domain/domain.h"
#include <stdlib.h>
#include <string.h>

typedef void* TipdeElement;

typedef void(*Destroyfct) (TipdeElement);

typedef TipdeElement(*Copyfct) (TipdeElement);

typedef struct Lista_medicamente{
    TipdeElement* elemente;
    int nr_medicamente;
    int cap;
    Destroyfct dfnc;
}Lista_medicamente;

/**
 * creeaza lista de medicamente, setand numarul de medicamente la 0, limita la 2, si aloca memorie initial pentru 2 elemente
 */
Lista_medicamente* create_empty(Destroyfct fc);

/**
 * distruge lista, dealocand memoria alocata elementelor listei
 * @param ls - lista de medicamente
 */
void destroy(Lista_medicamente* ls);

/**
 * se asigura ca memoria alocata listei de medicamente este suficienta si aloca mai multa in cazul in care mai este nevoie
 * @param ls - lista de medicamente
 */
void ensure_capacity(Lista_medicamente* ls);

/**
 * adauga un medicament primit ca si parametru in lista de medicamente daca acesta nu exista, sau modifica in medicamentul
 * existent cantitatea cu cea a medicamentului primit
 * @param ls - lista de medicamente
 * @param medicament - instanta a structurii de medicament care trebuie adaugata in aplicatie
 */
void adauga_medicament_repo(Lista_medicamente* ls, TipdeElement medicament);

/**
 * actualizeaza numele si/sau concentratia medicamentului primit ca parametru
 * @param ls - lista de medicamente
 * @param medicament - medicamentul cu numele si/sau concentratia noua ce trebuie modificata
 * @return 0 daca operatiunea a fost realizata cu succes sau -1 daca nu exista un medicament cu idul respectiv care
 * sa poata fi modificat
 */
int actualizeaza_medicament_repo(Lista_medicamente* ls, TipdeElement medicament);

/**
 * sterge un medicament din lista de medicamente dupa id-ul primit ca si parametru
 * @param ls - lista de medicamente
 * @param id - idul medicamentului care trebuie sters - int
 * @return 0 daca operatiunea a fost realizata cu succes sau -1 daca nu exista un medicament cu idul respectiv care
 * sa poata fi sters
 */
int stergere_medicament_repo(Lista_medicamente* ls, int id);

/**
 * cauta medicamentul cu idul primit ca parametru in lista de medicamente
 * @param ls - lista de medicamente
 * @param id - idul medicamentului cautat - int
 * @return pozitia in vector a elementului cu idul dat sau -1 daca nu este medicament cu idul respectiv - integer
 */
int cauta_medicament_repo(Lista_medicamente* ls, int id);

/**
 * returneaza numarul de medicamente salvate in lista de medicamente primita ca si parametru
 * @param ls - lista de medicamente
 * @return int - numarul de medicamente din lista de medicamente
 */
int nr_medicamente_repo(Lista_medicamente* ls);

/**
 * returneaza medicamentul de pe pozitia data din lista de medicamente
 * @param ls - lista de medicamente
 * @param poz - pozitia din lista de medicamente
 * @return instanta a structurii de medicament - medicamentul de pe pozitia poz din lista de medicamente
 */
TipdeElement get(Lista_medicamente* ls, int poz);

/**
 * modifica elementul din lista de medicamente de pe pozitia primita cu medicamentul primit ca si parametru si returneaza
 * elementul care a fost inlocuit
 * @param ls - lista de medicamente
 * @param poz - pozitia la care va fi modificat elementul
 * @param medicament - medicamentul care trebuie pus pe pozitia data
 * @return instanta a structurii de medicament - medicamentul care a fost inlocuit
 */
TipdeElement set(Lista_medicamente * ls, int poz, TipdeElement medicament);

/**
 * creeaza o copie la listei de medicamente, independenta de cea initiala si o returneaza
 * @param ls - lista de medicamente
 * @return o lista de medicamente independenta de cea salvata in aplicatie
 */
Lista_medicamente* copyList(Lista_medicamente* ls, Copyfct cf);

/// returneaza ultima instanta din lista de undo
/// \param lista - lista de medicamente
/// \return ultimul element din lista de undo de tip TipdeElement
TipdeElement removeLast(Lista_medicamente* lista);

#endif
