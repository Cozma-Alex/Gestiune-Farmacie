#include "ui.h"

int preluare_date(char parametrii[4][50]) {
    char nume[50], id[12], cantitate[12], concentratie[12];
    printf("Id:");
    scanf("%s", id);
    if (atoi(id) == 0) {
        printf("ID invalid!\n");
        return 0;
    }

    printf("Nume:");
    scanf("%s", nume);

    printf("Cantitate:");
    scanf("%s", cantitate);
    if (atoi(cantitate) == 0) {
        printf("Cantitate invalida!\n");
        return 0;
    }

    printf("Concentratie:");
    scanf("%s", concentratie);
    if (atoi(concentratie) == 0) {
        printf("Concentratie invalida!\n");
        return 0;
    }
    strcpy(parametrii[0], id);
    strcpy(parametrii[1], nume);
    strcpy(parametrii[2], cantitate);
    strcpy(parametrii[3], concentratie);
    return 1;
}

void ui_print_toate_medicamentele(Lista_medicamente* ls){
    printf("Medicamente:\n");
    int n = nr_medicamente_repo(ls);
    for (int i = 0; i < n; ++i) {
        Medicament* med = get(ls,i);
        printf("Id:%d - Nume:%s - Cantitate:%d - Concentratie:%d%%\n", med->id, med->nume, med->cantitate, med->concentratie);
    }
    printf("\n");
}

void ui_afiseaza_toate_medicamentele(Farmacie* farmacie) {
    Lista_medicamente *med = get_all_service(farmacie);
    ui_print_toate_medicamentele(med);
    destroy(med);
}

void ui_adauga_medicament(Farmacie* farmacie) {
    char parametrii[4][50];
    if (preluare_date(parametrii) == 0)
        return;
    int error = adauga_medicament_service(farmacie, atoi(parametrii[0]), parametrii[1], atoi(parametrii[2]), atoi(parametrii[3]));
    if(error!=0){
        printf("Medicament invalid!\n\n");
    }
    else{
        printf("Medicament adaugat cu succes!\n\n");
    }
}

void ui_actualizare_medicament(Farmacie* farmacie) {
    char parametrii[4][50];
    if (preluare_date(parametrii) == 0)
        return;
    int error = actualizeaza_medicament_service(farmacie, atoi(parametrii[0]), parametrii[1], atoi(parametrii[2]), atoi(parametrii[3]));
    if(error == -1){ // nu exista medicament cu idul citit
        printf("Medicament inexistent!\n\n");
        return;
    }
    else if(error != 0){ // cantitate invalida
        printf("Medicament invalid!\n\n");
    }
    else{
        printf("Medicament actualizat cu succes!\n\n");
    }
}

void ui_stergere_medicament(Farmacie* farmacie) {
    char id[12];
    printf("Id:");
    scanf("%s", id);
    if (atoi(id) <= 0) {
        printf("ID invalid!\n");
        return;
    }
    if (stergere_medicament_service(farmacie, atoi(id)) == -1) {
        printf("Medicament inexistent!\n\n");
        return;
    }
    printf("Medicament sters cu succes!\n\n");
}

void ui_sorteaza_nume_cantitate(Farmacie* farmacie){
    int tip_sortare;
    printf("Alegeti tipul de sortare: 1 - crescator sau 2 - descrescator\n");
    scanf("%d", &tip_sortare);
    if(tip_sortare != 1 && tip_sortare != 2){
        printf("Mod de sortare invalid!\n");
        return;
    }
    Lista_medicamente* med = sortare_nume_cantitate_service(farmacie, tip_sortare);
    ui_print_toate_medicamentele(med);
    destroy(med);
}

void ui_filtrare_medicament_stoc_mai_mic(Farmacie* farmacie){
    int cantitate;
    printf("Introduceti cantitatea:");
    scanf("%d", &cantitate);
    Lista_medicamente* med = filtrare_medicament_stoc_mai_mic(farmacie, cantitate);
    ui_print_toate_medicamentele(med);
    destroy(med);
}

void ui_filtrare_medicament_nume_cu_un_caracter(Farmacie* farmacie){
    char caracter[20];
    printf("Introduceti caracterul:");
    scanf("%s", caracter);
    Lista_medicamente* med = filtrare_medicament_nume_cu_un_caracter(farmacie, caracter[0]);
    ui_print_toate_medicamentele(med);
    destroy(med);
}

void ui_undo(Farmacie* farmacie){
    if(undo(farmacie)==0)
        printf("Nu mai sunt undo-uri!\n");
}

void ui_filtrare_medicament_concentratie(Farmacie* farmacie){
    char concentratie[20];
    printf("Introduceti concentratia:");
    scanf("%s", concentratie);
    Lista_medicamente* med = filtrare_medicament_dupa_concentratie(farmacie, atoi(concentratie));
    ui_print_toate_medicamentele(med);
    destroy(med);
}

void run_UI() {
    Farmacie farmacie = create_farmacie();
    int run = 1;
    while (run) {
        printf("1. Adaugare medicament\n");
        printf("2. Actualizare medicament\n");
        printf("3. Stergere stoc medicament\n");
        printf("4. Vizualizare medicament stoc ordonate dupa nume si cantitate, crescator/descrescator\n");
        printf("5. Vizualizare lista de medicamente unde stocul disponibil e mai mic decat o valoare data\n"); 
        printf("6. Vizualizare lista de medicamente unde numele medicamentelor incepe cu o litera data\n");
        printf("7. Vizualizare lista de medicamente unde concentratia este mai mare decat o valoare data\n");
        printf("8. Afisare totalitatea medicamentelor\n");
        printf("9. Undo\n");
        printf("10. Exit\n");
        printf("Alegeti optiunea:");
        char op[20];
        scanf("%s", op);
        if (atoi(op) != 0) {
            int new_op = atoi(op);
            switch (new_op) {
                case 1:
                    ui_adauga_medicament(&farmacie);
                    break;

                case 2:
                    ui_actualizare_medicament(&farmacie);
                    break;

                case 3:
                    ui_stergere_medicament(&farmacie);
                    break;

                case 4:
                    ui_sorteaza_nume_cantitate(&farmacie);
                    break;

                case 5:
                    ui_filtrare_medicament_stoc_mai_mic(&farmacie);
                    break;

                case 6:
                    ui_filtrare_medicament_nume_cu_un_caracter(&farmacie);
                    break;

                case 7:
                    ui_filtrare_medicament_concentratie(&farmacie);
                    break;

                case 8:
                    ui_afiseaza_toate_medicamentele(&farmacie);
                    break;

                case 9:
                    ui_undo(&farmacie);
                    break;

                case 10:
                    run = 0;
                    break;

                default:
                    printf("\ncomanda invalida\n\n");
                    break;
            }
        } else {
            printf("\ncomanda invalida\n\n");
        }
    }
    destroy_farmacie(&farmacie);
}

