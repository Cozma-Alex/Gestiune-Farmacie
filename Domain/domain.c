#include "domain.h"

Medicament* creeaza_medicament(int id, char* nume, int cantitate, int concentratie){
    Medicament* medicament = malloc(sizeof(Medicament));
    medicament->id= id;
    medicament->cantitate = cantitate;
    medicament->concentratie = concentratie;
    medicament->nume = malloc(sizeof(char) * 30);
    strncpy(medicament->nume, nume, 30);
    return medicament;
}

Medicament* copy_medicament(Medicament *medicament){
    return creeaza_medicament(medicament->id, medicament->nume, medicament->cantitate, medicament->concentratie);
}

void destroy_medicament(Medicament *medicament){
    free(medicament->nume);
    medicament->nume = NULL;
    medicament->id = -1;
    medicament->cantitate = -1;
    medicament->concentratie = -1;
    free(medicament);
}

int validate(Medicament* medicament){
    if(medicament->id <= 0)
    {
        return 1;
    }
    if(medicament->cantitate<=0)
    {
        return 2;
    }
    if(medicament->concentratie<=0)
    {
        return 3;
    }
    return 0;
}
