#include <iostream>
#include<cmath>
#include<string>
using namespace std;

class Animal {
    private:
        string nom;
        
    public:
        int taille;
        virtual void crier(){
            cout << "l'animal crie!" <<endl;
        };
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
        virtual bool peutManger (){
            return false;

        }
};

class Carnivore : public Animal {
    public :
        virtual bool peutManger (Animal &a){
            if (a.taille > this->taille){
                return false;
            }
            else {
                return true;
            }
        }
};

class Lapin : public Herbivore {
    public : 
        int taille = 30;
};

class Lion : public Carnivore {
    public : 
        int taille = 200;
};

class Renard : public Carnivore {
    public : 
        int taille = 70;
};

class Elephant (int taille): public Herbivore {
    private :
        int taille;
    public : 
        int taille = taille;
};

int main(){
    Chien Medor;
    Chat Felix;
    Medor.crier();
    Felix.crier();
    Animal *ptr;
    ptr = &Felix;
    ptr->crier();
    //L'appel avec le pointeur affiche bien "Miaou!"
    //Exercice 2 : cannot declare variable 'a' to be of abstract type 'Animal' . C'est normal, on ne peut pas instancier une classe abstraite.
    return 0;
}
