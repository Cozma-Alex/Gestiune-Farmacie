#ifndef LABUL_2_UI_H
#define LABUL_2_UI_H
#include "../Business/service.h"
#include "../Domain/domain.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * citeste un id, un nume, o cantitate si o concentratie de la tastatura si afiseaza un mesaj de eroare oprind rulajul in cazul in
 * care datele introduse de utilizator sunt invalide
 * @param parametrii - matrice de cuvinte, care retine pe fiecare linie cate una dintr valorile citite de la tastatura,
 * randul 0 continand idul, randul 1 numele, randul 2 cantitatea si randul 3 concentratia
 * @return 0 in cazul in care unul dintre numerele introduse nu este numar, 1 altfel
 */
int preluare_date(char parametrii[4][50]);

/**
 * afiseaza in consola toate medicamentele din lista de medicamente primita
 * @param ls - lista de medicamente
 */
void ui_print_toate_medicamentele(Lista_medicamente* ls);

/**
 * afiseaza pe ecran toate medicamentele salvate in lista de medicamente din instanta de farmacie
 * @param farmacie - instanta a structurii de farmacie ce contine lista de medicamente ce trebuie afisata
 */
void ui_afiseaza_toate_medicamentele(Farmacie* farmacie);

/**
 * preia datele de la tastatura si apeleaza functia de adaugare medicament din service, afisand realizarea cu succes a adaugarii
 * sau semnaleaza ca datele introduse pentru un medicament sunt invalide
 * @param farmacie - instanta a structurii de farmacie ce contine lista de medicamente in care trebuie adaugat medicamentul
 */
void ui_adauga_medicament(Farmacie* farmacie);

/**
 * preia datele despre noul medicament de la tastatura si apeleaza functia de actualizare medicament din service
 * daca nu exista un medicament care sa poata fii modificat pentru datele introduse, se afiseaza un mesaj de eroare,
 * sau in cazul in care datele introduse pentru medicament sunt invalide
 * @param farmacie - instanta a structurii de farmacie ce contine lista de medicamente si medicamentul care ar trebui modificat
 */
void ui_actualizare_medicament(Farmacie* farmacie);

/**
 * preia id-ul elementului de la tastatura pentru care se doreste stergerea si apeleaza functia de stergere medicament din service
 * in cazul in care nu exista un medicament cu id-ul introdus, programul afiseaza ca nu a putut realiza aceasta operatie
 * @param farmacie - instanta a structurii de farmacie ce contine lista de medicamente si medicamentul care ar trebui sters
 */
void ui_stergere_medicament(Farmacie* farmacie);

/**
 * cere de la utilizator tipul de sortare, crescator sau descrescator, si afiseaza pe ecran lista de medicamente sortata dupa
 * nume si cantitate in ordinea ceruta
 * @param farmacie - instanta a structurii de farmacie ce contine lista de medicamente ce trebuie sortata
 */
void ui_sorteaza_nume_cantitate(Farmacie* farmacie);

/**
 * cere de la utilizator cantitatea dupa care sa se realizeze filtrarea si afiseaza pe ecran lista de medicamente dupa filtrare
 * @param farmacie - instanta a structurii de farmacie ce contine lista de medicamente asupra careia se va aplica filtrul
 */
void ui_filtrare_medicament_stoc_mai_mic(Farmacie* farmacie);

/**
 * cere de la utilizator caracterul cu care trebuie sa inceapa numele medicamentelor pentru a realiza filtrarea si afiseaza
 * pe ecran lista de medicamente dupa filtrare
 * @param farmacie - instanta a structurii de farmacie ce contine lista de medicamente asupra careia se va aplica filtrul
 */
void ui_filtrare_medicament_nume_cu_un_caracter(Farmacie* farmacie);

/**
 * se ocupa de rularea consolei si prealuarea comenzilor de la tastatura
 */
void run_UI();

#endif