#include "service.h"
#include "mysort.h"

Farmacie create_farmacie(){
    Farmacie rez;
    rez.toate_medicamentele = create_empty((Destroyfct) (destroy_medicament));
    rez.undo_list = create_empty((Destroyfct) destroy);
    return rez;
}

void destroy_farmacie(Farmacie* farmacie){
    destroy(farmacie->toate_medicamentele);
    destroy(farmacie->undo_list);
}

int adauga_medicament_service(Farmacie* farmacie, int id, char* nume, int cantitate, int concentratie){
    Medicament* med = creeaza_medicament(id, nume, cantitate, concentratie);
    int errorCode = validate(med);
    if(errorCode!=0){
        destroy_medicament(med);
        return errorCode;
    }
    Lista_medicamente* toUndo = copyList(farmacie->toate_medicamentele, (Copyfct) copy_medicament);
    adauga_medicament_repo(farmacie->toate_medicamentele, med);
    adauga_medicament_repo(farmacie->undo_list,toUndo);
    return 0;
}

int actualizeaza_medicament_service(Farmacie* farmacie, int id, char* nume, int cantitate, int concentratie){
    Medicament* med = creeaza_medicament(id, nume, cantitate, concentratie);
    int errorCode = validate(med);
    if(errorCode!=0){
        destroy_medicament(med);
        return errorCode;
    }
    Lista_medicamente* toUndo = copyList(farmacie->toate_medicamentele, (Copyfct) copy_medicament);
    adauga_medicament_repo(farmacie->undo_list,toUndo);
    return actualizeaza_medicament_repo(farmacie->toate_medicamentele, med);
}

int stergere_medicament_service(Farmacie* farmacie, int id){
    int error = stergere_medicament_repo(farmacie->toate_medicamentele, id);
    if(error == 0)
    {
        Lista_medicamente* toUndo = copyList(farmacie->toate_medicamentele, (Copyfct) copy_medicament);
        adauga_medicament_repo(farmacie->undo_list,toUndo);
    }
    return error;

}

Lista_medicamente* get_all_service(Farmacie* farmacie){
    return copyList(farmacie->toate_medicamentele, (Copyfct) copy_medicament);
}

int cmp_nume_cantitate(Medicament* m1, Medicament* m2){
    if(strcmp(m1->nume, m2->nume) == 0){
        return m1->cantitate > m2->cantitate;
    }
    return strcmp(m1->nume, m2->nume);
}

Lista_medicamente *sortare_nume_cantitate_service(Farmacie* farmacie, int tip_sortare){
    Lista_medicamente *ls = copyList(farmacie->toate_medicamentele, (Copyfct) copy_medicament);
    sort(ls,cmp_nume_cantitate, tip_sortare);
    return ls;
}

void filtrare_cantitate(Lista_medicamente* ls, int cantitate){
    int n = nr_medicamente_repo(ls);
    for (int i = 0; i < n; ++i) {
        Medicament* medicament = get(ls, i);
        if(medicament->cantitate >= cantitate){
            stergere_medicament_repo(ls, medicament->id);
            n--;
            i--;
        }
    }
}

Lista_medicamente* filtrare_medicament_stoc_mai_mic(Farmacie* farmacie, int cantitate){
    Lista_medicamente *ls = copyList(farmacie->toate_medicamentele, (Copyfct) copy_medicament);
    filtrare_cantitate(ls, cantitate);
    return ls;
}

void filtrare_nume(Lista_medicamente* ls, char caracter){
    for (int i = 0; i < nr_medicamente_repo(ls); ++i) {
        Medicament* medicament = get(ls, i);
        if(medicament->nume[0] != caracter)
        {
            stergere_medicament_repo(ls, medicament->id);
            i--;
        }
    }
}

void filtrare_concentratie(Lista_medicamente* ls, int concentratie){
    for (int i = 0; i < nr_medicamente_repo(ls); ++i) {
        Medicament* medicament = get(ls, i);
        if(medicament->concentratie != concentratie)
        {
            stergere_medicament_repo(ls, medicament->id);
            i--;
        }
    }
}

int undo(Farmacie* farmacie){
    if(nr_medicamente_repo(farmacie->undo_list)==0)
        return 0;
    else{
        Lista_medicamente* l = removeLast(farmacie->undo_list);
        destroy(farmacie->toate_medicamentele);
        farmacie->toate_medicamentele = l;
    }
    return 1;
}

Lista_medicamente* filtrare_medicament_dupa_concentratie(Farmacie* farmacie, int concentratie){
    Lista_medicamente *ls = copyList(farmacie->toate_medicamentele, (Copyfct) copy_medicament);
    filtrare_concentratie(ls, concentratie);
    return ls;
}

Lista_medicamente* filtrare_medicament_nume_cu_un_caracter(Farmacie *farmacie, char caracter){
    Lista_medicamente *ls = copyList(farmacie->toate_medicamentele, (Copyfct) copy_medicament);
    filtrare_nume(ls, caracter);
    return ls;
}