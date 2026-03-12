#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

//-------Exercice 1-------

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
        printf("%d ", depiler(p));
    }
}

void annulerMouvement(Pile *p,int n){
    int i;
    if (estPileVide(p)){
        printf("Aucun mouvement à annuler.\n");
    }
    else {
        for (i = 0; i < n; i++){
            depiler(p);
        }
    }
}

//-------Exercice 2-------

typedef struct CelluleFile {
    int val;
    struct CelluleFile *suivant;
    struct CelluleFile *precedant;
} CelluleFile;

typedef struct {
    CelluleFile *head; // Sortie de la file
    CelluleFile *tail; // Entree de la file
} File;

File creerFile() {
    File f = {NULL, NULL};
    return f;
}

int estFileVide(File *f) {
    return f->head == NULL;
}

void afficherFile(File *F){
    CelluleFile *c =F->head;
    while (c!=NULL){
        printf("%d",c->val);
        c=c->suivant;
    }
    printf("\n");
}

void enfiler(File *F, int n){
    CelluleFile *new = malloc(sizeof(CelluleFile));
    //On définie notre nouvelle valeur
    new->val=n;
    new->precedant=F->tail;
    new->suivant=NULL;
    //On verifie si la liste est vide et si elle est vide on remplace la tête de file par notre nouvelle valeur
    if (F->head==NULL){
        F->head = new;
    }
    //Si la liste n'est pas vide on dit que le suivant de notre queue de file est notre nouvelle cellule
    else{
        F->tail->suivant=new;
    }
    //On redéfinie notre queue de File
    F->tail=new;
}

int defiler(File *F){
    //On regarde si la file est nulle
    if (F->head==NULL){
        exit(1);
    }
    CelluleFile *Head = F->head;
    //On sauvegarde la valeur de la tête pour la retourner à la fin
    int val=Head->val;
    //On enleve l'ancienne tête est on la remplace part la suivante
    F->head=Head->suivant;
    if (F->head != NULL) {
        // On coupe le lien vers l'ancienne cellule
        F->head->precedant = NULL;
    } else {
        //La file devient vide : on met aussi la queue à NULL
        F->tail = NULL; 
    }
    //On libère la mémoire
    free(Head);
    return val;
}

int head(File *F){
    return F->head->val;
}

void clearFile(File *F){
    CelluleFile *c=F->tail;
    while(c!=NULL){
        defiler(F);
        c=c->precedant;
    }
}

float moyenneFile(File *F){
    CelluleFile *c=F->head;
    float taille=0.0;
    float somme=0.0;
    while (c!=NULL){
        somme=somme+c->val;
        taille++;
        c=c->suivant;
    }
    return somme/taille;
}

//-------Exercice 3-------

// Définition d'une cellule de la FAP
typedef struct CelluleAlerte {
    char message[100];           // L'intitulé de l'alerte
    int priorite;                // Niveau de priorité de 1 (urgent) à 5
    struct CelluleAlerte *suivant;   
    struct CelluleAlerte *precedant; 
} CelluleAlerte;

// Définition de la structure de contrôle de la FAP
typedef struct {
    CelluleAlerte *head;  
    CelluleAlerte *tail; // Pointeur vers la dernière alerte
} FAP;

FAP creerFAP() {
    FAP f;
    f.head = NULL; 
    f.tail = NULL;
    return f;
}

void enfilerFAP (FAP *f, char *Alerte, int prio){

    //Définition de la nouvelle alerte
    CelluleAlerte *new = malloc(sizeof(CelluleAlerte));
    new->priorite=prio;
    strcpy(new->message, Alerte); 
    new->suivant = NULL;
    new->precedant = NULL;

    //Si la FAP est vide on remplace la tête et la queue par notre nouvelle alerte
    if (f->head==NULL){
        f->head=new;
        f->tail=new;
        return;
    }

    //Insertion en tête (si plus prioritaire que le premier)
    if (prio < f->head->priorite) {
        new->suivant = f->head;
        f->head->precedant = new;
        f->head = new;
        return; //
    }

    // Recherche de la position 
    CelluleAlerte *c = f->head;
    while (c->suivant != NULL && c->suivant->priorite <= prio) {
        c = c->suivant; // On avance tant que c'est plus prioritaire
    }

    // Insertion de new juste après c
    new->suivant = c->suivant;
    new->precedant = c;
    
    if (c->suivant != NULL) {
        c->suivant->precedant = new; // Lien retour du suivant
    } 
    else {
        f->tail = new; // Mise à jour de la queue si on est au bout
    }
    c->suivant = new;
}


void traiterAlerte(FAP *f){
    if (f->head==NULL){
        printf("Aucune alerte à traiter.\n");
        return;
    }
    CelluleAlerte *c = f->head;
    while (c!=NULL){
        printf("%s (Priorité : %d)\n", c->message, c->priorite);
        c = c->suivant;
    }
}


int main() {
int exo = -1;
Pile p = creerPile();
do{
    printf("----TD4----\n");
    printf("1: Exercice 1, Question 1\n");
    printf("2: Exercice 1, Question 2\n");
    printf("3: Exercice 2, Exercice 2, Initialisation de la File est test des opération\n");
    printf("4: Exercice 2, Capteur hydraulique\n");
    printf("5: Exercice 3\n");
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
            for (int i = 0; i < 3; i++) {
                empiler(&p, i);
            }

            printf("Mouvements avant annulation : ");
            afficher(&p);
            printf("\n");
    
            annulerMouvement(&p, 2);
    
            printf("Mouvements après annulation de 2 mouvements : ");
            afficher(&p);
            printf("\n");

            break;
        case 3:
            //test File
            File f = creerFile();

            enfiler(&f, 1);
            enfiler(&f, 2);
            enfiler(&f, 3);
            printf("File après enfilage de 1, 2, 3 : ");

            afficherFile(&f);
            printf("\n");

            printf("Défilage : %d\n", defiler(&f));
            printf("File après défilage : ");
            afficherFile(&f);

            printf("\n");
            break;
        case 4:
            //test capteur hydraulique
            File CapteurHydro = creerFile();
            int mesure=0;
            int tailleFile=0;
            while(mesure!=-1){
                printf("\nSaisissez une mesure positive (-1 pour arreter la saisie): \n");
                scanf("%d", &mesure);
                if (mesure<0){
                    printf("Erreur : Cette valeur est négative \n");
                    continue;
                }
                if(tailleFile<=4){
                    enfiler(&CapteurHydro, mesure);
                    tailleFile++;
                }
                else{
                    defiler(&CapteurHydro);
                    enfiler(&CapteurHydro, mesure);
                }
                printf("Les mesures sont : ");
                afficherFile(&CapteurHydro);
                printf("La moyenne des mesures est %f \n", moyenneFile(&CapteurHydro));
            }
            clearFile(&CapteurHydro);
            break;
        case 5:
            //test Exercice 3
            FAP Cockpit = creerFAP();
            enfilerFAP(&Cockpit, "B : Mise à jour météo disponible", 5);
            enfilerFAP(&Cockpit, "C : Température moteur élevée", 2);
            enfilerFAP(&Cockpit, "A : Niveau de carburant bas", 1);

            printf("Alertes à traiter : \n");
            traiterAlerte(&Cockpit);

            //Lorsque 2 alertes ont la même priorité, elles sont traitées dans l'ordre d'arrivée.

            break;
        default:
            printf("Choix invalide, veuillez réessayer.\n");
    }
   } while (exo != 0);
return 0;
}

