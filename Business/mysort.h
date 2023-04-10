#ifndef LAB3_MYSORT_H
#define LAB3_MYSORT_H
#include "../Domain/domain.h"
#include "../Repo//repo.h"

typedef int(*FunctieComparare)(Medicament * o1, Medicament * o2);

/**
 * sorteaza lista de medicamente primita ca parametru folosind functia de comparare a 2 medicamente primita ca si parametru
 * sort in place cu complexitate O(n*n)
 * @param ls - lista de medicamente
 * @param cmpF - functia pentru comparare a 2 medicamente
 * @param mod_sortare - int cu valoarea 1 pentru sortare crescatoare si 2 pentru descrescatoare
 */
void sort(Lista_medicamente* ls, FunctieComparare cmpF, int mod_sortare);

#endif
