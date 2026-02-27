#include <stdio.h>
#include <stdlib.h>

typedef struct cellule {
    int valeur;
    struct cellule* suivant;
} Cellule;

typedef struct {
    Cellule* head;
} Liste;

typedef struct CelluleD {
    int val;
    struct CelluleD *suivant;
    struct CelluleD *precedent;
} CelluleD;

typedef struct {
    CelluleD *head;
    CelluleD *tail;
} ListeD;


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
    for (Cellule *c =  l->head; c!=NULL; c = c->suivant) {
        if (c->valeur == element) {
            return 1;
        }
    }
    return 0;
}

//fonction pour supprimer un élément de la liste simplement chainée

int element_remove (Liste *l, int element){
    if (l->head != NULL && l->head->valeur == element) {
    Cellule *a = l->head;      // Je sauvegarde l'adresse de l'élément à supprimer (ici la tête)
    l->head = l->head->suivant; 
    free(a);                  
    return 1;
    }
    for (Cellule *c = l->head; c != NULL && c->suivant != NULL; ) {
        if (c->suivant->valeur == element) {
            Cellule *a = c->suivant;       
            c->suivant = c->suivant->suivant;
            free(a);                       
            return 1;
        } 
        else {
            c = c->suivant; 

        }
    }
}

//Maintenant, je vais implémenter les fonctions pour la liste doublement chaînée
//Les opérations à changé sont lenght, clear, cons, append et remove (On rajoutera un D pour les nouvelles versions)
int clearD(ListeD *l) {
    CelluleD *c = l->head;
    while (c != NULL) {
        CelluleD *temp = c;
        c = c->suivant;
        free(temp);
    }
    l->head = NULL;
    l->tail = NULL;
    return 1;
}
int lengthD(ListeD l) {
    int taille = 0;
    for (CelluleD* c = l.head; c != NULL; c = c->suivant) {
        taille++;
    }
    return taille;
}

void consD(ListeD *l, int element) {
    CelluleD *new = malloc(sizeof(CelluleD));
    new->val=element;
    new->suivant = l->head;
    new->precedent = NULL;

    if (l->head != NULL) {
        l->head->precedent = new;
    } else {
        l->tail = new;
    }
    l->head = new;
}

void appendD(ListeD *l, int element){
    CelluleD *new =malloc(sizeof (CelluleD));
    new->val = element;
    new->precedent=l->tail;
    new -> suivant = NULL;
    if (l->tail!= NULL){
        l->tail->suivant = new;
    }
    else {
        l->head = new;
    }
    l->tail = new;
}

void element_removeD(ListeD *l, int element){
    CelluleD *c;
    for (c = l->head; c != NULL; c = c->suivant) {
        if (c->val == element) {
            if (c->precedent != NULL) {
                c->precedent->suivant = c->suivant;
            } else {
                l->head = c->suivant;
            }
            if (c->suivant != NULL) {
                c->suivant->precedent = c->precedent;
            } else {
                l->tail = c->precedent;
            }
            free(c);
            return;
        }
    }
}

void printBackwards(ListeD l) {
    for (CelluleD *c = l.tail; c != NULL; c = c->precedent) {
        printf("%d ", c->val);
    }
    printf("\n");
}

void insertSorted(ListeD *l, int element){
    CelluleD *new = malloc(sizeof(CelluleD));
    new->val = element;
    new->suivant = NULL;
    new->precedent = NULL;
    if (l->head == NULL) {
        l->head = new;
        l->tail = new;
        return;
    }
    for (CelluleD *c = l->head; c != NULL; c = c->suivant) {
        if (c->val >= element) {
            new->suivant = c;
            new->precedent = c->precedent;
            if (c->precedent != NULL) {
                c->precedent->suivant = new;
            } else {
                l->head = new;
            }
            c->precedent = new;
            return;
        }
    }
    new->precedent = l->tail;
    l->tail->suivant = new;
    l->tail = new;
}

void merge(ListeD *l1, ListeD *l2, ListeD *result) {
    CelluleD *c1 = l1->head;
    CelluleD *c2 = l2->head;
    while (c1 != NULL) {
        insertSorted(result, c1->val);
        c1 = c1->suivant;
    }
    while (c2 != NULL) {
        insertSorted(result, c2->val);
        c2 = c2->suivant;
    }
}
void reverse(ListeD *l) {
    CelluleD *c = l->head;
    CelluleD *temporaire = NULL;
    while (c != NULL) {
        temporaire = c->precedent;
        c->precedent = c->suivant;
        c->suivant = temporaire;
        c = c->precedent;
    }
    if (temporaire != NULL) {
        l->head = temporaire->precedent;
    }
}

int main () {
    Liste l;
    l.head = NULL;

    append(&l, 1);
    append(&l, 2);
    append(&l, 3);

    printf("Taille de la liste simple: %d\n", length(l));
    printf("Premier element de la liste simple: %d\n", head(l));

    //Test search
    
    printf("Choisissez un élément à rechercher: ");
    int element;
    scanf("%d", &element);
    if (search(&l, element)) {
        printf("Element trouvé dans la liste.\n");
    } else {
        printf("Element non trouvé dans la liste.\n");
    }

    //Test remove
    
    printf("Choisissez un élément à supprimer: ");
    scanf("%d", &element);
    if (element_remove(&l, element)) {
        printf("Element supprimé de la liste.\n");
        for (Cellule *c = l.head; c != NULL; c = c->suivant) {
            printf("%d ", c->valeur);
        }
    } else {
        printf("Element non trouvé dans la liste.\n");
    }
    printf("\n");
    clear(&l);
    printf("Taille de la liste apres nettoyage: %d\n", length(l));

    //Teste liste Doublement chaînée
    
    ListeD ld;
    ld.head = NULL;
    ld.tail = NULL;
    appendD(&ld, 1);
    appendD(&ld, 2);
    appendD(&ld, 3);
    printf("La liste doublement chaînée:\n ");
    for (CelluleD *c = ld.head; c != NULL; c = c->suivant) {
        printf("%d ", c->val);
    }
    printf("\n");

    //Test consD

    printf("Choissez un élément à ajouter au début de la liste doublement chaînée: ");
    scanf("%d", &element);
    consD(&ld, element);
    printf("Liste doublement chaînée après ajout au début: ");
    for (CelluleD *c = ld.head; c != NULL; c = c->suivant) {
        printf("%d ", c->val);
    }
    printf("\n");

    //Test appendD

    printf("Choisissez un élément à ajouter à la fin de la liste doublement chaînée: ");
    scanf("%d", &element);
    appendD(&ld, element);
    printf("Liste doublement chaînée après ajout à la fin: ");
    for (CelluleD *c = ld.head; c != NULL; c = c->suivant) {
        printf("%d ", c->val);
    }
    printf("\n");

    //Test element_removeD

    printf("Choisissez un élément à supprimer de la liste doublement chaînée: ");
    scanf("%d", &element);
    element_removeD(&ld, element);
    printf("Liste doublement chaînée après suppression: ");
    for (CelluleD *c = ld.head; c != NULL; c = c->suivant) {
        printf("%d ", c->val);
    }
    printf("\n");
    //Test printBackwards
    printf("Liste doublement chaînée en ordre inverse: ");
    printBackwards(ld);

    //Test lengthD
    printf("Taille de la liste doublement chaînée avant nettoyage: %d\n", lengthD(ld));
    
    //Test clearD
    clearD(&ld);

    //Test lengthD
    printf("Taille de la liste doublement chaînée après nettoyage: %d\n", lengthD(ld));
    
    //Test insertSorted
    ListeD sorted = {NULL, NULL};
    printf("Entrez des éléments à insérer dans la liste triée: ");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &element);
        insertSorted(&sorted, element);
    }

    printf("Liste triée: ");
    for (CelluleD *c = sorted.head; c != NULL; c = c->suivant) {
        printf("%d ", c->val);
    }
    printf("\n");

    //Test merge
    
    ListeD l1 = {NULL, NULL};
    ListeD l2 = {NULL, NULL};
    ListeD result = {NULL, NULL};
    
    printf("Entrez des éléments pour la première liste triée: ");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &element);
        insertSorted(&l1, element);
    }
    printf("Entrez des éléments pour la deuxième liste triée: ");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &element);
        insertSorted(&l2, element);
    }

    merge(&l1, &l2, &result);
    printf("Liste fusionnée: ");
    for (CelluleD *c = result.head; c != NULL; c = c->suivant) {
        printf("%d ", c->val);
    }
    printf("\n");

    //Test reverse
    
    printf("Liste avant inversion: ");
    for (CelluleD *c = result.head; c != NULL; c = c->suivant) {
        printf("%d ", c->val);
    }
    printf("\n");
    reverse(&result);
    printf("Liste après inversion: ");
    for (CelluleD *c = result.head; c != NULL; c = c->suivant) {
        printf("%d ", c->val);
    }
    printf("\n");

    return 0;
}