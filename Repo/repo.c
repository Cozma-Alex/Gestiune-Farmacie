#include <stdio.h>
#include "repo.h"

Lista_medicamente* create_empty(Destroyfct fc){
    Lista_medicamente* ls = malloc(sizeof(Lista_medicamente));
    ls->nr_medicamente = 0;
    ls->cap = 1;
    ls->elemente = malloc(8 * ls->cap);
    ls->dfnc = fc;
    return ls;
}

void destroy(Lista_medicamente* ls){
    for (int i = 0; i < ls->nr_medicamente; ++i) {
        ls->dfnc(ls->elemente[i]);
    }
    free(ls->elemente);
    ls->elemente = NULL;
    ls->nr_medicamente = 0;
    free(ls);
}

void ensure_capacity(Lista_medicamente * ls) {
    if (ls->nr_medicamente < ls->cap) {
        return;
    }
    int newCapacity = ls->cap + 2;
    TipdeElement * nelemente = malloc(sizeof(Medicament)*newCapacity);
    for (int i = 0; i < ls->nr_medicamente; i++) {
        nelemente[i] = ls->elemente[i];
    }
    free(ls->elemente);
    ls->elemente = nelemente;
    ls->cap = newCapacity;
}

void adauga_medicament_repo(Lista_medicamente* ls, TipdeElement medicament){
    ensure_capacity(ls);
    Medicament* med_nou;
    med_nou = (Medicament*)medicament;
    int pozitie_medicament = cauta_medicament_repo(ls, med_nou->id);
    if(pozitie_medicament == -1){
        ls->elemente[ls->nr_medicamente] = medicament;
        ls->nr_medicamente++;
    }
    else{
        Medicament* med_nou1, *med_nou2;
        med_nou1 = (Medicament*)ls->elemente[pozitie_medicament];
        med_nou2 = (Medicament*)medicament;
        med_nou1->cantitate += med_nou2->cantitate;
        destroy_medicament(medicament);
    }
}

int actualizeaza_medicament_repo(Lista_medicamente* ls, TipdeElement medicament){
    Medicament* med_nou;
    med_nou = (Medicament*) medicament;
    int pozitie_medicament = cauta_medicament_repo(ls, med_nou->id);
    if(pozitie_medicament != -1){
        destroy_medicament(ls->elemente[pozitie_medicament]);
        ls->elemente[pozitie_medicament] = medicament;
        return 0;
    }
    destroy_medicament(medicament);
    return -1;
}

int stergere_medicament_repo(Lista_medicamente* ls, int id){
    int pozitie_medicament = cauta_medicament_repo(ls, id);
    if(pozitie_medicament != -1){
        destroy_medicament(ls->elemente[pozitie_medicament]);
        for (int i = pozitie_medicament; i < ls->nr_medicamente - 1; ++i) {
            set(ls, i, ls->elemente[i+1]);
        }
        ls->nr_medicamente--;
        return 0;
    }
    return -1;
}

int cauta_medicament_repo(Lista_medicamente* ls, int id){
    for (int i = 0; i < ls->nr_medicamente; ++i) {
        Medicament* med_nou;
        med_nou = (Medicament*) ls->elemente[i];
        if(med_nou->id == id)
            return i;
    }
    return -1;
}

int nr_medicamente_repo(Lista_medicamente* ls){
    return ls->nr_medicamente;
}

TipdeElement get(Lista_medicamente* ls, int poz){
    return ls->elemente[poz];
}

TipdeElement set(Lista_medicamente* ls, int poz, TipdeElement medicament){
    TipdeElement rez= ls->elemente[poz];
    ls->elemente[poz] = medicament;
    return rez;
}

TipdeElement removeLast(Lista_medicamente* l){
    TipdeElement rez = l->elemente[l->nr_medicamente-1];
    l->nr_medicamente-=1;
    return rez;
}

Lista_medicamente* copyList(Lista_medicamente * l, Copyfct fc) {
    Lista_medicamente *rez = create_empty(l->dfnc);
    for (int i = 0; i < nr_medicamente_repo(l); i++) {
        TipdeElement med = get(l, i);
        adauga_medicament_repo(rez, fc(med));
    }
    return rez;
}
