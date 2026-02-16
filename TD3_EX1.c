#include <stdio.h>
#include <stdlib.h>

typedef struct cellule {
    int valeur;
    struct cellule* suivant;
} Cellule;

typedef struct {
    Cellule* head;
} Liste;



int isEmpty(Liste l) {
    return l.head == NULL;
}

int length(Liste l) {
    int taille = 0;
    for (Cellule* c = l.head; c != NULL; c = c->suivant) {
        taille++;
    }
    return taille;
}

//Créer une nouvelle cellule et l'ajouter au début de la liste

void cons(Liste *l, int element){
    Cellule *new = malloc(sizeof(Cellule));
    new->valeur = element;
    new->suivant = l->head;
    l->head = new;
}

int head(Liste l){
    if (isEmpty(l)) {
        printf("La liste est vide.\n");
        exit(1); // Terminer le programme avec un code d'erreur
    }
    return l.head->valeur;
}

void append(Liste *l, int element) {
    Cellule *new = malloc(sizeof(Cellule));
    new->valeur = element;
    new->suivant = NULL;

    if (isEmpty(*l)) {
        l->head = new;
    } else {
        Cellule *c = l->head;
        while (c->suivant != NULL) {
            c = c->suivant;
        }
        c->suivant = new;
    }
}

void clear (Liste *l) {
    Cellule *c = l->head;
    while (c != NULL) {
        Cellule *temp = c;
        c = c->suivant;
        free(temp);
    }
    l->head = NULL;
}

int search(Liste *l, int element){
    for (Cellule *c =  l.head; c!=NULL; c = c->suivant) {
        if (c->valeur == element) {
            return 1;
        }
    }
}

int remove (Liste *l, int element){
    for (Cellule *c =  l.head; c!=NULL; c = c->suivant) {
        if (c->valeur == element) {
            c = c->suivant;
        }
        else if (isEmpty(l)){
            exit(1);
        }
    }
}

int main {
    Liste l;
    l.head = NULL;

    append(&l, 1);
    append(&l, 2);
    append(&l, 3);

    printf("Taille de la liste: %d\n", length(l));
    printf("Premier element: %d\n", head(l));

    clear(&l);
    printf("Taille de la liste apres nettoyage: %d\n", length(l));

    return 0;
}