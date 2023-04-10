#ifndef LABUL_2_SERVICE_H
#define LABUL_2_SERVICE_H
#include "../Domain/domain.h"
#include "../Repo/repo.h"
#include <string.h>

typedef struct {
    Lista_medicamente* toate_medicamentele;
    Lista_medicamente* undo_list;
}Farmacie;

/**
 * creeaza o instanta a listei de medicamente in interiorul structurii de farmacie
 * @return o structura de tip farmacie ce contine o lista de medicamente
 */
Farmacie create_farmacie();

/**
 * distruge instanta de farmacie, apeland functia de distrugere a listei de medicamente
 * @param farmacie - o instanta a structurii de farmacie ce contine o lista ce trebuie distrusa
 */
void destroy_farmacie(Farmacie* farmacie);

/**
 * coordoneaza operatia de adaugare medicament
 * @param farmacie - o instanta a structurii de farmacie
 * @param id - idul medicamentului ce trebuie adaugat - int
 * @param nume - numele medicamentului ce trebuie adaugat - pointer catre un sir de caractere alocat dinamic
 * @param cantitate - cantitatea medicamentului ce trebuie adaugat - int
 * @param concentratie - concentratia medicamentului ce trebuie adaugat - int
 * @return 0 daca medicamentul a fost adaugat cu succes sau un cod de eroare daca datele primite pentru medicament sunt invalide
 */
int adauga_medicament_service(Farmacie* farmacie, int id, char* nume, int cantitate, int concentratie);

/**
 * coordoneaza operatia de actualizare a unui medicament
 * @param farmacie - o instanta a structurii de farmacie
 * @param id - idul medicamentului ce trebuie actualizat - int
 * @param nume - numele medicamentului ce trebuie actualizat - poate fi nou sau nu - pointer catre un sir de caractere alocat dinamic
 * @param cantitate - cantitatea medicamentului ce trebuie actualizata - poate fi noua sau nu - int
 * @param concentratie - concentratia medicamentului ce trebuie actualizat - poate fi noua sau nu - int
 * @return 0 daca medicamentul a fost actualizat cu succes sau -1 daca nu exista un medicament cu idul cautat
 */
int actualizeaza_medicament_service(Farmacie* farmacie, int id, char* nume, int cantitate, int concentratie);

/**
 * coordoneaza operatia de stergere a unui medicament
 * @param farmacie - o instanta a structurii de farmacie
 * @param id - idul medicamentului cautat pentru a fii sters
 * @return 0 daca operatia de stergere a fost realizata cu succes sau -1 daca nu exista un medicament cu idul cautat
 */
int stergere_medicament_service(Farmacie* farmacie, int id);

/**
 * returneaza o copie a listei de medicamente ce contine toate medicamentele salvate in lista din instanta de farmacie
 * @param farmacie - o instanta a structurii de farmacie ce contine lista cu medicamente
 * @return o lista de medicamente
 */
Lista_medicamente* get_all_service(Farmacie* farmacie);

/**
 * functia ce relizeaza compararea a 2 medicamente in functie de nume si cantitate, returnand rezultatul comparatiei
 * @param m1 - primul medicament
 * @param m2 - al doilea medicament
 * @return 1 daca numele primului medicament este mai mare, -1 daca numele e mai mic sau in cazul in care numele este identic,
 * returneaza 1 daca cantitatea primului medicament este mai mare decat a celui de al doilea medicament, 0 altfel
 */
int cmp_nume_cantitate(Medicament* m1, Medicament* m2);

/**
 * returneaza o lista de medicamente sortata in ordine crescatoar/descrescatoare dupa nume si cantitate
 * @param farmacie - o instanta a structurii de farmacie ce contine lista cu medicamente
 * @param tip_sortare - int - are valoarea 1 pentru sortare crescatoare si 2 pentru descrescatoare
 * @return o lista de medicamente sortata
 */
Lista_medicamente* sortare_nume_cantitate_service(Farmacie* farmacie, int tip_sortare);

/**
 * filtreaza lista primita ca si parametru eliminand medicamentele ce sunt in cantitate mai mare decat cantitatea primita
 * @param ls - lista de medicamente
 * @param cantitate - int - cantitatea folosita pentru filtrare
 */
void filtrare_cantitate(Lista_medicamente* ls, int cantitate);

/**
 * returneaza o lista de medicamente filtrata ce contine doar medicamentele cu cantitate mai mica decat o cantitate data
 * @param farmacie - o instanta a structurii de farmacie ce contine lista cu medicamente
 * @param cantitate - int - cantitatea folosita pentru filtrare
 * @return o lista de medicamente dupa aplicarea filtrului
 */
Lista_medicamente* filtrare_medicament_stoc_mai_mic(Farmacie* farmacie, int cantitate);

/**
 * filtreaza lista primita ca si parametru eliminand medicamentele a caror nume nu incepe cu caracterul dat
 * @param ls - lista de medicamente
 * @param caracter - caracterul cu care trebuie sa inceapa numele medicamentelor
 */
void filtrare_nume(Lista_medicamente* ls, char caracter);

/**
 * returneaza o lista de medicamente filtrate ce contine doar medicamentele a caror nume incepe cu caracterul dat
 * @param farmacie - o instanta a structurii de farmacie ce contine lista cu medicamente
 * @param caracter - caracterul folosit pentru filtrare
 * @return o lista de medicamente dupa aplicarea filtrului
 */
Lista_medicamente* filtrare_medicament_nume_cu_un_caracter(Farmacie *farmacie, char caracter);

/// aduce lista cu medicamente la starea de dinainte de ultima operatie
/// \param farmacie - o instanta a structurii de farmacie ce contine lista cu medicamente
/// \return 0 - daca nu mai exista operatii de undo
///         1 - daca s-a facut o operatie de undo
int undo(Farmacie* farmacie);

/// returneaza o lista de medicamente filtrate ce contine doar medicamentele cu concentratia egala
/// \param farmacie - o instanta a structurii de farmacie ce contine lista cu medicamente
/// \param concentratie - concentratia folosita pentru filtrare
/// \return o lista de medicamente dupa aplicarea filtrului
Lista_medicamente* filtrare_medicament_dupa_concentratie(Farmacie* farmacie, int concentratie);

#endif
