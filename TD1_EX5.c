#include <stdio.h>
#include <stdlib.h>
 
int moyenne_pression (int *p, int N) {
    int somme = 0;
    for (int i = 0; i < N; i++) {
        somme += *(p + i);
    }
    return somme / N;
}
 
int main() {
    int N=0;
    int moyenne;
 
    printf("Entrer le nomnbre de mesures : ");
    scanf("%d", &N);
    int tab[N];
    int *p = tab;
    for (int i = 0; i < N; i++) {
        printf("Entrer la mesure %d : ", i + 1);
        scanf("%d", &tab[i]);
    }
    moyenne = moyenne_pression(p, N);
    printf("La moyenne des pressions est de : %d\n", moyenne);
    return 0;
 
}