
#ifndef LAB3_TEST_H
#define LAB3_TEST_H
#include "../Business/service.h"

void run_all_tests();

void test_creeaza_distruge_medicament();
void test_medicament_invalid();
void test_copie_medicament();

void test_creare_lista();
void test_copie_lista();

void test_adauga_medicament();
void test_actualizare_medicament();
void test_stergere_medicament();

void test_filtrare_stoc();
void test_filtrare_nume();
void test_filtrare_concentratie();

void test_sortare();

void test_undo();

#endif
