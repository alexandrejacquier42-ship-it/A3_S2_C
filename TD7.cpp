#include <iostream>
#include<cmath>
#include<string>
using namespace std;

class Animal {
    private:
        string nom;
        int taille;
        
    public:
        Animal(string nom, int taille) {
            this->nom = nom;
            this->taille = taille;
        }
        int getTaille() {
            return taille;
        }
        string getNom() {
            return this->nom;
        }

        virtual void crier(){
            cout << "l'animal crie!" <<endl;
        };
        virtual bool peutManger (Animal &a) =0;
        

        virtual ~Animal() {
        }
};

class Chien : public Animal {
    public:
        virtual void crier() {
            cout << "Ouaf!" <<endl;
        }
};

class Chat : public Animal {
    public : 
        virtual void crier() {
            cout << "Miaou!" <<endl;
        }
};

class Herbivore : public Animal {
    public : 
        Herbivore(string nom, int taille){
            this->nom = nom;
            this->taille = taille;
        }
        virtual bool peutManger (){
            return false;

        }
};

class Carnivore : public Animal {
    public :
        Carnivore(string nom, int taille){
            this->nom = nom;
            this->taille = taille;
        }
        virtual bool peutManger (Animal &a){
            if (a.getTaille() > this->getTaille()){
                return false;
            }
            else {
                return true;
            }
        }
};

class Lapin : public Herbivore {
    public : 
        Lapin("Lapin", 30) : Herbivore("Lapin", 30) {
        }
};

class Lion : public Carnivore {
    public : 
        Lion("Lion", 150) : Carnivore("Lion", 150) {
        }
};

class Renard : public Carnivore {
    public : 
        Renard("Renard", 70) : Carnivore("Renard", 70) {
        }
};

class Elephant : public Carnivore {
    public : 
        Elephant("Elephant", 400) : Carnivore("Elephant", 400) {
        }
};



int main(){
    Chien Medor;
    Chat Felix;
    Medor.crier();
    Felix.crier();
    Animal *ptr;
    ptr = &Felix;
    ptr->crier();

    Animal* animaux[6];
    animaux[0] = new Lion();
    animaux[1] = new Lapin();
    animaux[2] = new Renard();
    animaux[3] = new Lapin();
    animaux[4] = new Elephant();
    animaux[5] = new Renard();

    bool result = true;

    while result {
        relust = false;
        for (int i = 0, i < 6; i++){
            if (animaux[i]!=nullptr&&animaux[i+1]!=nullptr){
                if (animaux[i]->peutManger(*animaux[i+1])){
                    cout << animaux[i]->getNom()<<"mange"<<animaux[i+1]->getNom()<< endl;
                    delete animaux[i+1];
                    animaux[i+1] = nullptr;
                    result = false;
                }
            }
        }
        if result {
            int j=0;
            for (int i = 0, i<6;i++){
                if animaux[i]!=nullptr{
                    animaux[j] = animaux[i];
                    if (j!=i){
                        animaux[i] = nullptr;
                    }
                    j++;
                }
            }
        }
    }
        // --- Affichage des survivants ---
    cout << "\n=== Survivants ===" << endl;
    for (int i = 0; i < nbAnimaux; i++) {
        cout << "- " << animaux[i]->getNom()
             << " (taille " << animaux[i]->getTaille() << ")" << endl;
    }

    // --- Libération de la mémoire restante ---
    // On delete chaque survivant pour éviter les fuites mémoire
    for (int i = 0; i < nbAnimaux; i++) {
        delete animaux[i];
        animaux[i] = nullptr;
    }
    return 0;
}
