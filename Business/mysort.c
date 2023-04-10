#include "mysort.h"

void sort(Lista_medicamente* ls, FunctieComparare cmpF, int mod_sortare){
    for (int i = 0; i < nr_medicamente_repo(ls) - 1; ++i) {
        for (int j = i + 1; j < nr_medicamente_repo(ls); ++j) {
            void* m1 = get(ls,i);
            void* m2 = get(ls, j);
            if(mod_sortare == 1) { // mod de sortare crescator
                if (cmpF(m1, m2) > 0) {
                    set(ls, i, m2);
                    set(ls, j, m1);
                }
            }else{ // mod de sortare descrescator
                if (cmpF(m1, m2) < 0) {
                    set(ls, i, m2);
                    set(ls, j, m1);
                }
            }
        }
    }
}
