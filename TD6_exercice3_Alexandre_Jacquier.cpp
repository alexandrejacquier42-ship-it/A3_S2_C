#include <iostream>
#include <string>

using namespace std;

class Client {
    private: 
        string nom;
        string prenom;
        int id;
        static int compteur;
        
    public:
        Client() {
            nom = "";
            prenom = "";
            id = 0;
        }
        Client(string nom, string prenom) {
            this->nom = nom;
            this->prenom = prenom;
            this->id = compteur++;
        }
        void afficher() {
            cout << "Client: " << nom << " " << prenom << ", ID: " << id << endl;
        }
        int getId() {
            return id;
        }
};

class FileDAttente {
    private:
        Client *tab;
        int tailleCourante;
        int capacite;
        
    public:
        FileDAttente(int capacite) {
            this->capacite = capacite;
            this->tailleCourante = 0;
            tab = new Client[capacite];
        }
        ~FileDAttente() {
            delete[] tab;
        }
        void ajouter(Client &c) {
            if (tailleCourante < capacite) {
                tab[tailleCourante++] = c;
            } else {
                int nouvelle_taille = capacite * 2;
                Client *nouveau_tab = new Client[nouvelle_taille];
                for (int i = 0; i < tailleCourante; i++) {
                    nouveau_tab[i] = tab[i];
                }
                
                delete[] tab; 
                
                tab = nouveau_tab;
                capacite = nouvelle_taille;
                tab[tailleCourante++] = c;
            }
        }   
        void suivant() {
            if (tailleCourante > 0) {
                for (int i = 0; i < tailleCourante - 1; i++) {
                    tab[i] = tab[i + 1];
                }
                tailleCourante--;
            }
        }
        void passeDevant(int idRecherche) {
            for (int i = 0; i < tailleCourante; i++) {
                if (tab[i].getId() == idRecherche) {
                    if (i > 0) { 
                        Client temp = tab[i];
                        tab[i] = tab[i - 1];
                        tab[i - 1] = temp;
                    }
                    break;
                }
            }
        } 
        void afficher() {
            for (int i = 0; i < tailleCourante; i++) {
                tab[i].afficher();
            }
        }
};

int Client::compteur = 1;
    
int main() {
    FileDAttente file(2);
    Client c1("Dupont", "Jean");
    Client c2("Durand", "Marie");
    Client c3("Martin", "Paul");
    
    file.ajouter(c1);
    file.ajouter(c2);
    file.ajouter(c3); 

    cout << "Clients dans la file d'attente:" << endl;
    file.afficher();

    return 0;
}

//Je n'arrive pas a compiler le code, je ne comprend pas pourquoi.