#include <stdio.h>
#include <stdlib.h>

typedef struct Cellule {
    int val;
    struct Cellule *suivant;
} Cellule;

typedef struct {
    Cellule *sommet; // Pointeur vers le haut de la
} Pile;

Pile creerPile() {
    Pile p = {NULL};
    return p;
}
void afficher(Pile *p){
    Cellule *c = p->sommet;
    while (c!=NULL){
        printf("%d",c->val);
        c=c->suivant;
    }
}
void empiler(Pile *p, int element){
    Cellule *new = malloc(sizeof(Cellule));
    new->val = element;
    new->suivant = p->sommet;
    p->sommet = new;
}

int depiler (Pile *p){
    if (p->sommet ==NULL){
        exit(1);
    }
    Cellule *sommet = p->sommet;
    int val = sommet->val;
    p->sommet = sommet->suivant;
    free(sommet);
    return val;
}

int estPileVide(Pile *p){
    return p->sommet == NULL;
}

int sommet(Pile *p){
    return p->sommet->val;
}

void clearPile(Pile *p){
    Cellule *c = p->sommet;
    while (c!=NULL){
        depiler(p);
    }
}

int main() {
int exo = -1;
Pile p = creerPile();
do{
    printf("----TD4----\n");
    printf("Exercice 1, Question 1\n");
    printf("Exercice 1, Question 2\n");
    printf("Exercice 2\n");
    printf("Exercice 3\n");
    printf("Choisissez un exercice à tester (0 pour quitter): ");
    scanf("%d", &exo);

    switch (exo){
        case 1:
            afficher(&p);
            printf("\n");

            empiler(&p, 5);
            empiler(&p, 10);
            empiler(&p, 15);

            afficher(&p);
            printf("\n");

            printf("On retire sommet : %d\n",depiler(&p));
            printf("Nouveau sommet : %d\n",sommet(&p));

            afficher(&p);
            printf("\n");

            while (!estPileVide(&p)) {
                printf("%d \n", depiler(&p));
            }

            clearPile(&p);
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            printf("Choix invalide, veuillez réessayer.\n");
    }
   } while (exo != 0);
return 0;
}

