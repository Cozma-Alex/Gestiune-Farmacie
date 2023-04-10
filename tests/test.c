#include <assert.h>
#include "test.h"

void run_all_tests(){
    test_creeaza_distruge_medicament();
    test_medicament_invalid();
    test_copie_medicament();
    test_creare_lista();
    test_copie_lista();
    test_adauga_medicament();
    test_actualizare_medicament();
    test_stergere_medicament();
    test_filtrare_stoc();
    test_filtrare_nume();
    test_filtrare_concentratie();
    test_sortare();
    test_undo();
}

void test_creeaza_distruge_medicament() {
    char* nume = malloc(30* sizeof(char));
    strcpy(nume, "Paracetamol");
    Medicament *med = creeaza_medicament(1, nume, 4,34);
    assert(med->id == 1);
    assert(strcmp(nume,"Paracetamol") == 0);
    assert(med->cantitate == 4);
    assert(med->concentratie == 34);
    free(nume);
    destroy_medicament(med);
}

void test_medicament_invalid(){
    char* nume = malloc(30* sizeof(char));
    strcpy(nume,"Paracetamol");

    Medicament *med_id_invalid = creeaza_medicament(-1,nume,4,34);
    assert(validate(med_id_invalid) == 1);

    Medicament *med_cantitate_invalida = creeaza_medicament(1,nume,-4,34);
    assert(validate(med_cantitate_invalida) == 2);

    Medicament *med_concentratie_invalida = creeaza_medicament(1,nume,4,-34);
    assert(validate(med_concentratie_invalida) == 3);

    Medicament *med_valid = creeaza_medicament(1,nume,4,34);
    assert(validate(med_valid) == 0);

    destroy_medicament(med_concentratie_invalida);
    destroy_medicament(med_cantitate_invalida);
    destroy_medicament(med_id_invalid);
    destroy_medicament(med_valid);
    free(nume);
}

void test_copie_medicament(){
    char* nume = malloc(30* sizeof(char));
    strcpy(nume,"Paracetamol");

    Medicament *med = creeaza_medicament(1,nume,4,34);
    Medicament *copie_med = copy_medicament(med);

    assert(med->id == copie_med->id);
    assert(strcmp(med->nume,copie_med->nume) == 0);
    assert(med->concentratie == copie_med->concentratie);
    assert(med->cantitate == copie_med->cantitate);

    destroy_medicament(copie_med);
    destroy_medicament(med);
    free(nume);
}

void test_creare_lista(){
    Lista_medicamente *l = create_empty((Destroyfct) destroy_medicament);
    assert(nr_medicamente_repo(l) == 0);
    destroy(l);
}

void test_copie_lista(){
    Farmacie farmacie = create_farmacie();
    Lista_medicamente *l_copie;
    char* nume = malloc(30* sizeof(char ));
    strcpy(nume,"Paracetamol");

    adauga_medicament_service(&farmacie,1,nume,12,3);
    l_copie = get_all_service(&farmacie);
    assert(nr_medicamente_repo(l_copie) == 1);
    Medicament *copie_med = get(l_copie,0);
    assert(1 == copie_med->id);
    assert(strcmp(nume,copie_med->nume) == 0);
    assert(3 == copie_med->concentratie);
    assert(12 == copie_med->cantitate);
    destroy_farmacie(&farmacie);
    destroy(l_copie);
    free(nume);
}

void test_adauga_medicament(){
    Farmacie farmacie = create_farmacie();
    char *nume1,*nume2;
    nume1 = (char *) malloc(30 * sizeof(char));
    nume2 = (char *) malloc(30 * sizeof(char));
    strcpy(nume2, "Parasinus");
    strcpy(nume1, "Paracetamol");
    assert(adauga_medicament_service(&farmacie,1,nume1,12,5) == 0);
    assert(adauga_medicament_service(&farmacie,1,nume1,4,7) == 0);
    assert(adauga_medicament_service(&farmacie, -1, nume1, 4, 6) == 1);
    adauga_medicament_service(&farmacie,2,nume2,5,7);
    destroy_farmacie(&farmacie);
    free(nume1);
    free(nume2);
}

void test_actualizare_medicament(){
    Farmacie farmacie = create_farmacie();
    char *nume1;
    nume1 = (char *) malloc(30 * sizeof(char));
    strcpy(nume1, "Paracetamol");
    adauga_medicament_service(&farmacie,1,nume1,12,5);
    assert(actualizeaza_medicament_service(&farmacie,1,nume1,7,8) == 0);
    assert(actualizeaza_medicament_service(&farmacie,2,nume1,4,6) == -1);
    assert(actualizeaza_medicament_service(&farmacie,-1,nume1,5,7) == 1);
    Medicament *med = get(farmacie.toate_medicamentele,0);
    assert(med->cantitate == 7);
    assert(med->concentratie == 8);
    assert(med->id == 1);
    assert(strcmp(med->nume, nume1) == 0);
    destroy_farmacie(&farmacie);
    free(nume1);
}

void test_stergere_medicament(){
    Farmacie farmacie = create_farmacie();
    char *nume1;
    nume1 = (char*) malloc(30* sizeof(char));
    strcpy(nume1, "Paracetamol");
    adauga_medicament_service(&farmacie,1,nume1,12,7);
    adauga_medicament_service(&farmacie,2,nume1,12,7);
    assert(stergere_medicament_service(&farmacie,3) == -1);
    assert(stergere_medicament_service(&farmacie,1) == 0);
    destroy_farmacie(&farmacie);
    free(nume1);
}

void test_filtrare_stoc(){
    Lista_medicamente *lista_filtrare_stoc;
    Farmacie farmacie = create_farmacie();
    char* nume = malloc(30* sizeof(char));
    strcpy(nume, "Paracetamol");
    adauga_medicament_service(&farmacie,1,nume,12,5);
    adauga_medicament_service(&farmacie,2,nume,4,7);
    lista_filtrare_stoc = filtrare_medicament_stoc_mai_mic(&farmacie,6);
    Medicament *med = get(lista_filtrare_stoc,0);
    assert(med->cantitate<=6);
    free(nume);
    destroy_farmacie(&farmacie);
    destroy(lista_filtrare_stoc);
}

void test_filtrare_nume(){
    Lista_medicamente *lista_filtrare_nume;
    Farmacie farmacie = create_farmacie();
    char* nume = malloc(30* sizeof(char));
    strcpy(nume, "Paracetamol");
    char* nume2 = malloc(30* sizeof(char));
    strcpy(nume2, "Carmol");
    adauga_medicament_service(&farmacie,1,nume,12,5);
    adauga_medicament_service(&farmacie,2,nume2,4,7);
    char caracter[20];
    strcpy(caracter,"P");
    lista_filtrare_nume = filtrare_medicament_nume_cu_un_caracter(&farmacie, caracter[0]);
    Medicament *med = get(lista_filtrare_nume,0);
    assert(nr_medicamente_repo(lista_filtrare_nume) == 1);
    assert(strcmp(med->nume,"Paracetamol") == 0);
    free(nume2);
    free(nume);
    destroy(lista_filtrare_nume);
    destroy_farmacie(&farmacie);
}

void test_filtrare_concentratie(){
    Lista_medicamente *lista_filtrare_concentratie;
    Farmacie farmacie = create_farmacie();
    char* nume = malloc(30* sizeof(char));
    strcpy(nume, "Paracetamol");
    adauga_medicament_service(&farmacie,1,nume,12,5);
    adauga_medicament_service(&farmacie,2,nume,4,7);
    lista_filtrare_concentratie = filtrare_medicament_dupa_concentratie(&farmacie,7);
    Medicament *med = get(lista_filtrare_concentratie,0);
    assert(med->concentratie == 7);
    free(nume);
    destroy_farmacie(&farmacie);
    destroy(lista_filtrare_concentratie);
}

void test_sortare(){
    Farmacie farmacie = create_farmacie();
    Lista_medicamente *l_sortat1, *l_sortat2;
    char *nume1,*nume2,*nume3;
    nume1 = (char *) malloc(30* sizeof(char ));
    nume2 = (char *) malloc(30* sizeof(char ));
    nume3 = (char *) malloc(30* sizeof(char ));
    strcpy(nume1,"Paracetamol");
    strcpy(nume2,"Carmol");
    strcpy(nume3,"Nurofen");
    adauga_medicament_service(&farmacie,1,nume1,3,6);
    adauga_medicament_service(&farmacie,2,nume1,5,7);
    adauga_medicament_service(&farmacie,3,nume2,1,8);
    adauga_medicament_service(&farmacie,4,nume3,6,90);
    l_sortat1 = sortare_nume_cantitate_service(&farmacie,1);
    Medicament *med = get(l_sortat1,0);
    assert(strcmp(med->nume,nume2) == 0);
    l_sortat2 = sortare_nume_cantitate_service(&farmacie,2);
    med = get(l_sortat2,1);
    assert(med->cantitate == 5);
    free(nume2);
    free(nume1);
    free(nume3);
    destroy(l_sortat1);
    destroy(l_sortat2);
    destroy_farmacie(&farmacie);
}

void test_undo(){
    Farmacie farmacie = create_farmacie();
    assert(undo(&farmacie) == 0);
    char *nume1, *nume2;
    nume1 = (char *) malloc(30* sizeof(char));
    nume2 = (char *) malloc(30* sizeof(char));
    strcpy(nume1,"Paracetamol");
    strcpy(nume2,"Nurofen");
    adauga_medicament_service(&farmacie,1,nume1,12,5);
    adauga_medicament_service(&farmacie,2,nume2,5,8);
    assert(undo(&farmacie) == 1);
    assert(nr_medicamente_repo(farmacie.undo_list) == 1);
    free(nume2);
    free(nume1);
    destroy_farmacie(&farmacie);
}