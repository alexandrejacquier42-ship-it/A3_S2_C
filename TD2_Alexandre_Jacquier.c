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
    printf("\n");
}

int main() {
    int nb_etudiants = 0;
    Etudiant *promotion = NULL;
    int choix;

    do {
        printf("\n--- MENU DE GESTION IPSA ---\n");
        printf("1. Initialiser et saisir la promotion\n");
        printf("2. Afficher tous les etudiants\n");
        printf("3. Afficher le majorant d'une matiere\n");
        printf("4. Mettre a jour un dossier (note)\n");
        printf("5. Supprimer un etudiant\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez le nombre d'etudiants: ");
                scanf("%d", &nb_etudiants);
                promotion = (Etudiant*) malloc(nb_etudiants * sizeof(Etudiant));
                for (int i = 0; i < nb_etudiants; i++) {
                    printf("Nom etudiant %d: ", i + 1);
                    scanf("%s", promotion[i].nom);
                    printf("Prenom etudiant %d: ", i + 1);
                    scanf("%s", promotion[i].prenom);
                    printf("Numero etudiant %d: ", i + 1);
                    scanf("%d", &promotion[i].num_etudiant);
                    
                    printf("Entrez les notes de math pour %s: ", promotion[i].nom);
                    for (int j = 0; j < 3; j++) scanf("%f", &promotion[i].bulletin.math[j]);
                    
                    printf("Entrez les notes de physique pour %s: ", promotion[i].nom);
                    for (int j = 0; j < 3; j++) scanf("%f", &promotion[i].bulletin.physique[j]);
                    
                    printf("Entrez les notes d'informatique pour %s: ", promotion[i].nom);
                    for (int j = 0; j < 3; j++) scanf("%f", &promotion[i].bulletin.informatique[j]);
                    
                    traiterNotes(&promotion[i]);
                    
                }
                printf("Promotion initialisée avec succès.\n");
                for (int i = 0; i < nb_etudiants; i++) afficherResulats(&promotion[i]);
                break;

            case 2:
                if (promotion == NULL) {
                    printf("Erreur: Promotion vide.\n");
                } else {
                    for (int i = 0; i < nb_etudiants; i++) {
                        afficherResulats(&promotion[i]);
                    }
                }
                break;

            case 3:
                if (promotion == NULL) break;
                printf("Matiere (math, physique, informatique): ");
                char matiere[20];
                scanf("%s", matiere);
                int majorant_index = 0;
                float max_note = -1.0;

                for (int i = 0; i < nb_etudiants; i++) {
                    float moy;
                    if (strcmp(matiere, "math") == 0) moy = calculerMoyenneTableau(promotion[i].bulletin.math, 3);
                    else if (strcmp(matiere, "physique") == 0) moy = calculerMoyenneTableau(promotion[i].bulletin.physique, 3);
                    else moy = calculerMoyenneTableau(promotion[i].bulletin.informatique, 3);

                    if (moy > max_note) {
                        max_note = moy;
                        majorant_index = i;
                    }
                }
                printf("Majorant %s : %s %s (Moyenne: %.2f)\n", matiere, promotion[majorant_index].nom, promotion[majorant_index].prenom, max_note);
                break;

            case 4:
                if (promotion == NULL) break;
                printf("Nom de l'etudiant: ");
                char nom_rech[20];
                scanf("%s", nom_rech);
                int idx = -1;
                for (int i = 0; i < nb_etudiants; i++) {
                    if (strcmp(promotion[i].nom, nom_rech) == 0) { idx = i; break; }
                }
                if (idx != -1) {
                    printf("Matiere a modifier: ");
                    char m_mod[20]; scanf("%s", m_mod);
                    printf("Ancienne note: ");
                    float ancienne_note, nouvelle_note; scanf("%f", &ancienne_note);
                    printf("Nouvelle note: ");
                    scanf("%f", &nouvelle_note);

                    float *tab_notes;
                    if (strcmp(m_mod, "math") == 0) tab_notes = promotion[idx].bulletin.math;
                    else if (strcmp(m_mod, "physique") == 0) tab_notes = promotion[idx].bulletin.physique;
                    else tab_notes = promotion[idx].bulletin.informatique;

                    for (int j = 0; j < 3; j++) {
                        if (tab_notes[j] == ancienne_note) {
                            tab_notes[j] = nouvelle_note;
                            traiterNotes(&promotion[idx]);
                            break;
                        }
                    }
                }
                break;

            case 5:
                if (promotion == NULL) break;
                printf("Nom et Prenom a supprimer: ");
                char n_sup[20], p_sup[20];
                scanf("%s %s", n_sup, p_sup);
                for (int i = 0; i < nb_etudiants; i++) {
                    if (strcmp(promotion[i].nom, n_sup) == 0 && strcmp(promotion[i].prenom, p_sup) == 0) {
                        for (int j = i; j < nb_etudiants - 1; j++) promotion[j] = promotion[j + 1];
                        nb_etudiants--;
                        promotion = (Etudiant*) realloc(promotion, nb_etudiants * sizeof(Etudiant));
                        break;
                    }
                }
                break;

            case 0:
                if (promotion != NULL) free(promotion);
                printf("Mémoire libérée.\n");
                break;

            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    return 0;
}
