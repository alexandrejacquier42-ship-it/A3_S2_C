#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    float math[20];
    float physique[20];
    float informatique[20];
} Bulletin;

typedef struct {
    char nom[20];
    char prenom[20];
    int num_etudiant;
    Bulletin bulletin;
    float moyenne;
} Etudiant;

float calculerMoyenneTableau(float *tab, int taille){
    float somme = 0.0;
    for (int i = 0; i < taille ; i++)
        somme += tab[i];
    return somme / taille;
}

void traiterNotes(Etudiant *e){
    float moyenne_bulletin[3];
    moyenne_bulletin[0] = calculerMoyenneTableau(e->bulletin.math, 3);
    moyenne_bulletin[1] = calculerMoyenneTableau(e->bulletin.physique, 3);
    moyenne_bulletin[2] = calculerMoyenneTableau(e->bulletin.informatique, 3);
    e->moyenne = calculerMoyenneTableau(moyenne_bulletin,3);
}

void afficherResulats(Etudiant *e){
    printf("Nom: %s\n", e->nom);
    printf("Prenom: %s\n", e->prenom);
    printf("Numero Etudiant: %d\n", e->num_etudiant);
    printf("Moyenne: %.2f\n", e->moyenne);
}

void main(){

    //initialisation de la promotion

    int nb_etudiants = 0;
    int nombre_note_math = 0;
    int nombre_note_physique = 0;
    int nombre_note_informatique = 0;
    Etudiant *promotion = NULL;
    printf("Entrez le nombre d'etudiants: ");
    scanf("%d", &nb_etudiants);
    promotion = (Etudiant*) malloc(nb_etudiants * sizeof(Etudiant));

    //Boucle de saisie des etudiants et de leurs notes

    for (int i = 0; i < nb_etudiants; i++){
        printf("Entrez le nom de l'etudiant %d:", i+1);
        scanf("%s", promotion[i].nom);
        printf("Entrez le prenom de l'etudiant %d:", i+1);
        scanf("%s", promotion[i].prenom);
        printf("Entrez le numero d'etudiant %d:", i+1);
        scanf("%d", &promotion[i].num_etudiant);
        printf("Entrez les notes de math pour l'etudiant %d:", i+1);
        for (int j = 0; j < 3; j++){
            scanf("%f", &promotion[i].bulletin.math[j]);
        }
        printf("Entrez les notes de physique pour l'etudiant %d:", i+1);
        for (int j = 0; j < 3; j++){
            scanf("%f", &promotion[i].bulletin.physique[j]);
        }
        printf("Entrez les notes d'informatique pour l'etudiant %d:", i+1);
        for (int j = 0; j < 3; j++){
            scanf("%f", &promotion[i].bulletin.informatique[j]);
        }
    }
    for (int i = 0; i < nb_etudiants; i++){
        traiterNotes(&promotion[i]);
        if (sizeof(promotion) != 0){
            afficherResulats(&promotion[i]);
        }
        else {
            printf("Aucun etudiant dans la promotion.\n");
        }
    }
    
    //Affichage du majorant de chaque matière

    printf("choisissez une matière pour afficher son majorant (math,physique ou informatique): ");
    char matiere[20];
    scanf("%s", matiere);
    if (strcmp(matiere, "math") == 0){
        float max_math = calculerMoyenneTableau(promotion[0].bulletin.math, 3);
        for (int i = 0; i < nb_etudiants; i++){
            if (calculerMoyenneTableau(promotion[i].bulletin.math, 3) > max_math)
                max_math = calculerMoyenneTableau(promotion[i].bulletin.math, 3);
        }
        printf("Le majorant de math est: %.2f\n", max_math);
    }
    else if (strcmp(matiere, "physique") == 0){
        float max_physique = calculerMoyenneTableau(promotion[0].bulletin.physique, 3);
        for (int i = 0; i < nb_etudiants; i++){
            if (calculerMoyenneTableau(promotion[i].bulletin.physique, 3) > max_physique)
                max_physique = calculerMoyenneTableau(promotion[i].bulletin.physique, 3);
        printf("Le majorant de physique est: %.2f\n", max_physique);
        }
    }
    else if (strcmp(matiere, "informatique") == 0){
        float max_informatique = calculerMoyenneTableau(promotion[0].bulletin.informatique, 3);
        for (int i = 0; i < nb_etudiants; i++){
            if (calculerMoyenneTableau(promotion[i].bulletin.informatique, 3) > max_informatique)
                max_informatique = calculerMoyenneTableau(promotion[i].bulletin.informatique, 3);
        printf("Le majorant d'informatique est: %.2f\n", max_informatique);
        }
    }
    else {
        printf("Matiere non reconnue.\n");
    }

    //Mise à jour d'un dossier

    printf("Entrez le nom de l'etudiant pour mettre à jour son dossier: ");
    char nom_etudiant[20];
    scanf("%s", nom_etudiant);  
    int index_etudiant = 0;
    for (int i = 0; i < nb_etudiants; i++){
        if (strcmp(promotion[i].nom, nom_etudiant) == 0){
            index_etudiant = i;
            break;
        }
    }

    printf("choisissez une matière pour afficher son majorant (math,physique ou informatique): ");
    char matiere_mod[20];
    scanf("%s", matiere_mod);
    printf("Entrez la note que vous voulez changer: ");
    float ancienne_note;
    scanf("%f", &ancienne_note);
    printf("Entrez la nouvelle note: ");
    float nouvelle_notes;
    scanf("%f", &nouvelle_notes);
    
    if (strcmp(matiere_mod, "math") == 0){
        for (int j = 0; j < 3; j++){
            if (promotion[index_etudiant].bulletin.math[j] == ancienne_note){
                promotion[index_etudiant].bulletin.math[j] = nouvelle_notes;
                traiterNotes(&promotion[index_etudiant]);
                break;
            }
        }
    }
    else if (strcmp(matiere_mod, "physique") == 0){
        for (int j = 0; j < 3; j++){
            if (promotion[index_etudiant].bulletin.physique[j] == ancienne_note){
                promotion[index_etudiant].bulletin.physique[j] = nouvelle_notes;
                traiterNotes(&promotion[index_etudiant]);
                break;
            }
        }
    }
    else if (strcmp(matiere_mod, "informatique") == 0){
        for (int j = 0; j < 3; j++){
            if (promotion[index_etudiant].bulletin.informatique[j] == ancienne_note){
                promotion[index_etudiant].bulletin.informatique[j] = nouvelle_notes;
                traiterNotes(&promotion[index_etudiant]);
                break;
            }
        }
    }
    else {
        printf("Matiere non reconnue.\n");
    }

    //Suppression d'un étudiant

    printf("Entrez le nom de l'etudiant pour supprimer son dossier: ");
    char nom_etudiant_sup[20];
    scanf("%s", nom_etudiant_sup);
    printf("Entrez le prenom de l'etudiant pour supprimer son dossier: ");
    char prenom_etudiant_sup[20];
    scanf("%s", prenom_etudiant_sup);
    int index_etudiant_sup = 0;
    for (int i = 0; i < nb_etudiants; i++){
        if (strcmp(promotion[i].nom, nom_etudiant_sup) == 0 && strcmp(promotion[i].prenom, prenom_etudiant_sup) == 0){
            index_etudiant_sup = i;
            break;
        }
    }
    for (int i = index_etudiant_sup; i < nb_etudiants - 1; i++){
        promotion[i] = promotion[i+1];

    }
    nb_etudiants--;
    promotion = (Etudiant*) realloc(promotion, nb_etudiants * sizeof(Etudiant));
    for (int i = 0; i < nb_etudiants; i++){
        traiterNotes(&promotion[i]);
        afficherResulats(&promotion[i]);
    }
    //Fermeture du logiciel 
    if (promotion != NULL) {
        free(promotion);    
    printf("Mémoire libérée. Fermeture du logiciel.\n");
    }

}
